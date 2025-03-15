<h1 align="center">TRANG TRẠI THÔNG MINH</h1>

<div align="center">

<p align="center">
  <img src="images/logo.png" alt="DaiNam University Logo" width="200"/>
  <img src="images/AIoTLab_logo.png" alt="AIoTLab Logo" width="170"/>
</p>

[![Made by AIoTLab](https://img.shields.io/badge/Made%20by%20AIoTLab-blue?style=for-the-badge)](https://www.facebook.com/DNUAIoTLab)
[![Fit DNU](https://img.shields.io/badge/Fit%20DNU-green?style=for-the-badge)](https://fitdnu.net/)
[![DaiNam University](https://img.shields.io/badge/DaiNam%20University-red?style=for-the-badge)](https://dainam.edu.vn)

</div>

<h3 align="center">🔬 Hệ thống nuôi lợn thông minh kết hợp AI điều khiển thiết bị</h3>

<p align="center">
  <strong>Giải pháp ứng dụng IoT và AI vào chăn nuôi hiện đại</strong>
</p>

## 🏗️ HỆ THỐNG

<p align="center">
  <img src="images/HeThong.png" alt="System Architecture" width="800"/>
</p>

Hệ thống trang trại thông minh được xây dựng với các thành phần chính:

- **ESP32 (Master)**: Nhận dữ liệu từ các Arduino UNO, gửi lên website qua Flask + WebSocket.
- **UNO1**: Hiển thị thời gian thực, hẹn giờ cho lợn ăn bằng động cơ bước và vít tải. Bật đèn tự động dựa trên cảm biến LDR.
- **UNO2**: Đo nhiệt độ, độ ẩm (DHT11), đo mực nước trong máng (Water Sensor). Tự động bơm nước khi dưới ngưỡng.
- **UNO3**: Cảm biến khí gas MQ135, cảnh báo bằng còi khi vượt ngưỡng.
- **ESP32-CAM**: Giám sát lợn qua hình ảnh trực tiếp.
- **AI (Google Speech-to-Text)**: Nhận diện giọng nói để điều khiển máy bơm, động cơ bước và đèn LED.

## ✨ TÍNH NĂNG

### 🧠 Công nghệ AI tiên tiến
- **Nhận diện giọng nói**: Chuyển đổi giọng nói thành lệnh điều khiển.
- **Xử lý ngữ cảnh**: Xác định hành động phù hợp với từng câu lệnh.

### ⚡ Kiến trúc hiệu suất cao
- **Giao tiếp I2C**: UNO gửi dữ liệu nhanh chóng về ESP32 Master.
- **Kết nối WebSocket**: ESP32 gửi dữ liệu lên website theo thời gian thực

### 📊 Giám sát toàn diện
- **Cảnh báo tự động**: Cảnh báo tự động khi hệ thống gặp rắc rối
- **Giao diện trực quan**: Hiển thị trực quan thông số tại chuồng và hình ảnh trực tiếp.

## 🔧 CÔNG NGHỆ SỬ DỤNG

<div align="center">

### Phần cứng
[![ESP32](https://img.shields.io/badge/ESP32-blue?style=for-the-badge)](https://www.espressif.com/)
[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![DHT11](https://img.shields.io/badge/DHT11-green?style=for-the-badge)]()
[![MQ135](https://img.shields.io/badge/MQ135-red?style=for-the-badge)]()
[![Stepper Motor](https://img.shields.io/badge/Stepper%20Motor-orange?style=for-the-badge)]()
[![LDR](https://img.shields.io/badge/LDR%20-yellow?style=for-the-badge)]()
[![Water Sensor](https://img.shields.io/badge/Water%20Sensor-blue?style=for-the-badge)]()
[![Relay Module](https://img.shields.io/badge/Relay%20Module-purple?style=for-the-badge)]()
[![ESP32-CAM](https://img.shields.io/badge/ESP32--CAM-ff69b4?style=for-the-badge)]()
[![I2C](https://img.shields.io/badge/I2C-green?style=for-the-badge)]()
[![RTC DS1307](https://img.shields.io/badge/RTC%20DS1307-orange?style=for-the-badge)]()


### Phần mềm
[![Flask](https://img.shields.io/badge/Flask-000000?style=for-the-badge&logo=flask&logoColor=white)](https://flask.palletsprojects.com/)
[![WebSocket](https://img.shields.io/badge/WebSocket-0078D7?style=for-the-badge)]()
[![Google Speech-to-Text](https://img.shields.io/badge/Google%20STT-yellow?style=for-the-badge)](https://cloud.google.com/speech-to-text)

</div>

## 🌍 BẢNG MẠCH

### ⭐️ UNO1

- **🛎Sơ đồ**
<img src="images/UNO1.png" alt="System Architecture" width="800"/>

- **🎲 Bảng hướng dẫn cắm dây**

| Thiết bị                | Chân trên thiết bị   | Kết nối Arduino UNO    | Ghi chú                 |
|-------------------------|----------------------|------------------------|-------------------------|
| RTC DS1302              | VCC                  | 5V                     | Cấp nguồn               |
|                         | GND                  | GND                    |                         |
|                         | RST                  | D5                     | Chân Reset              |
|                         | DAT                  | D7                     | Chân Data               |
|                         | CLK                  | D6                     | Chân Clock              |
| Động cơ bước 28BYJ-48   | VCC                  | 5V                     | Cấp nguồn               |
|                         | GND                  | GND                    |                         |
|                         | IN1                  | D8                     | Điều khiển Stepper      |
|                         | IN2                  | D10                    | Điều khiển Stepper      |
|                         | IN3                  | D9                     | Điều khiển Stepper      |
|                         | IN4                  | D11                    | Điều khiển Stepper      |
| Cảm biến ánh sáng (LDR) | VCC                  | 5V                     | Cấp nguồn               |
|                         | GND                  | GND                    |                         |
|                         | D0                   | A0                     | Đọc giá trị ánh sáng    |
| Đèn LED                 | Chân dài (+)         | D2                     | Điều khiển bật/tắt      |
|                         | Chân ngắn (-)        | GND                    |                         |


### ⭐️ UNO2

- **🛎Sơ đồ**
<img src="images/UNO2.png" alt="System Architecture" width="800"/>

- **🎲 Bảng hướng dẫn cắm dây**
     
| Thiết bị             | Chân kết nối  | Kết nối Arduino UNO  | Ghi chú                        |
|----------------------|---------------|----------------------|--------------------------------|
| Cảm biến mực nước    | + (VCC)       | 5V                   | Cấp nguồn cho cảm biến         |
|                      | - (GND)       | GND                  |                                |
|                      | S             | A0                   | Đọc giá trị mực nước           |
| Cảm biến DHT11       | VCC           | 5V                   | Cấp nguồn cho cảm biến         |
|                      | GND           | GND                  |                                |
|                      | DATA          | D4                   | Truyền dữ liệu nhiệt độ, độ ẩm |
| Rơ-le điều khiển bơm | IN            | D7                   | Điều khiển bật/tắt rơ-le       |
|                      | VCC           | 5V                   | Cấp nguồn cho rơ-le            |
|                      | GND           | GND                  |                                |
|                      | COM           | Cực dương nguồn      | Nối với nguồn bơm              |
|                      | NO            | Cực dương bơm        | Rơ-le đóng mới cấp nguồn       |
| Máy bơm nước         | Cực âm bơm    | Cực âm nguồn         | Hoàn tất mạch điện             |

### ⭐️ UNO3

- **🛎Sơ đồ**
<img src="images/UNO3.png" alt="System Architecture" width="800"/>

- **🎲 Bảng hướng dẫn cắm dây**

| Thiết bị              | Chân trên thiết bị  | Kết nối Arduino UNO | Ghi chú                       |
|-----------------------|---------------------|---------------------|-------------------------------|
| Cảm biến khí MQ-135   | VCC                 | 5V                  | Cấp nguồn                     |
|                       | GND                 | GND                 |                               |
|                       | A0                  | A0                  | Đọc giá trị khí gas           |
| Còi báo động (Buzzer) | Chân dương (+)      | D6                  | Kích hoạt còi khi vượt ngưỡng |
|                       | Chân âm (-)         | GND                 |                               |

### ⭐️ Kết nối I2C giữa Arduino UNO & ESP32

<img src="images/I2C.png" alt="System Architecture" width="800"/>

| Thiết bị                                   | Chân trên thiết bị | Kết nối ESP32  | Ghi chú               |
|--------------------------------------------|--------------------|----------------|-----------------------|
| Arduino UNO #1 (Hẹn giờ, động cơ, đèn)     | SDA (A4)           | GPIO 21 (SDA)  | I2C giao tiếp ESP32   |
|                                            | SCL (A5)           | GPIO 22 (SCL)  | I2C giao tiếp ESP32   |
| Arduino UNO #2 (Cảm biến nước & bơm)       | SDA (A4)           | GPIO 21 (SDA)  | I2C giao tiếp ESP32   |
|                                            | SCL (A5)           | GPIO 22 (SCL)  | I2C giao tiếp ESP32   |
| Arduino UNO #3 (MQ-135 & còi báo)          | SDA (A4)           | GPIO 21 (SDA)  | I2C giao tiếp ESP32   |
|                                            | SCL (A5)           | GPIO 22 (SCL)  | I2C giao tiếp ESP32   |


📌 **Ghi chú:**  
- **ESP32 là thiết bị trung tâm**, thu dữ liệu từ **3 Arduino UNO** qua **I2C** và điều khiển thiết bị qua WebSocket.  
- **ESP32-CAM gửi dữ liệu video**, đẩy lên giao diện web.  
- **Các cảm biến gửi dữ liệu về UNO**, UNO truyền dữ liệu qua ESP32 để hiển thị trên web.  
  
## 📥 CÀI ĐẶT

### 🛠️ Yêu cầu hệ thống

- 🐍 **Python** `3.8+`
- 📡 **ESP32, Arduino Uno R3 & Arduino IDE**
- 💾 **RAM** `4GB+`
- 📶 **WiFi** kết nối internet

### ⚙️ Thiết lập môi trường

1. **Cài đặt thư viện Python (app.py)**
   ```bash
   pip install flask flask-socketio opencv-python
   ```
   
2. **Nạp code vào ESP32 & Arduino**
   - Sử dụng Arduino IDE nạp code cho UNO.
   - Sử dụng Arduino IDE để nạp code cho ESP32.

3. **Cấu hình ESP32 và Flask Server (ESP32.ino)**
   ```cpp
   const char* ssid = "TenWiFi"; 
   const char* password = "MatKhau"; 
   const char* server_url = "http://localhost:5000/update";  // Địa chỉ Flask server
   ```

4. **Cấu hình CameraWebServer (CameraWebServer.ino)**
   ```cpp
   const char* ssid = "TenWiFi"; 
   const char* password = "MatKhau"; 
   ```

5. **Cấu hình ESP32-CAM (app.py)**
   ```cpp
   #define ESP32_CAM_URL "http://172.16.65.189:81/stream"
   ```

6. **Chạy Server Flask (app.py)**
   ```bash
   python app.py
   ```
   
## 🚀 SỬ DỤNG
  ĐANG UPDATE

## 📝 GIẤY PHÉP
<p align="center">
  <img src="images/Poster.png" alt="System Architecture" width="800"/>
</p>
© 2025 NHÓM 8, CNTT16-02, ĐẠI HỌC ĐẠI NAM

---

<div align="center">
