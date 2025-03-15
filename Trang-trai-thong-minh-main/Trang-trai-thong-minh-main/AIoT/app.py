from flask import Flask, render_template, request, jsonify
from flask_socketio import SocketIO
import json
import cv2
from flask import Response

app = Flask(__name__)
socketio = SocketIO(app)

# Biến lưu trạng thái
sensor_data = {"uno1": "Chưa có dữ liệu", "uno2": "Chưa có dữ liệu", "uno3": "Chưa có dữ liệu"}
control_status = {"motor": 0, "pump": 0}  # 0: Tắt, 1: Bật

ESP32_CAM_URL = "http://172.16.65.189:81/stream"  # Thay bằng IP thực tế

# Thêm route xử lý video
def generate_frames():
    cap = cv2.VideoCapture(ESP32_CAM_URL)
    while True:
        success, frame = cap.read()
        if not success:
            break
        else:
            ret, buffer = cv2.imencode('.jpg', frame)
            frame = buffer.tobytes()
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/video_feed')
def video_feed():
    return Response(generate_frames(),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/update', methods=['POST'])
def update_data():
    try:
        data = request.get_json(force=True)
        
        if not data:
            print("❌ Không nhận được dữ liệu JSON!")
            return jsonify({"error": "Invalid JSON"}), 400

        print("📥 Dữ liệu nhận từ ESP32:", json.dumps(data, indent=2, ensure_ascii=False))

        global sensor_data
        sensor_data = data
        socketio.emit('sensor_update', sensor_data)  # Gửi toàn bộ dữ liệu
        return jsonify({"status": "success"})
    
    except Exception as e:
        print("❌ Lỗi xử lý JSON:", str(e))
        return jsonify({"error": str(e)}), 400

@app.route('/control', methods=['POST'])
def control():
    try:
        global control_status
        data = request.get_json(force=True)

        if 'device' not in data or 'status' not in data:
            return jsonify({"error": "Thiếu thông tin điều khiển"}), 400

        control_status[data['device']] = data['status']
        socketio.emit('control_update', control_status)

        print(f"⚙️ Thiết bị {data['device']} -> Trạng thái: {'Bật' if data['status'] else 'Tắt'}")
        return jsonify({"status": "success"})

    except Exception as e:
        print("❌ Lỗi điều khiển:", str(e))
        return jsonify({"error": str(e)}), 400

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000, debug=True)