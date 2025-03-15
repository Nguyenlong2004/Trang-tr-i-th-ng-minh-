#include <Wire.h>

#define MQ135_PIN A0   // Cảm biến MQ-135
#define BUZZER_PIN 6   // Còi báo động
#define GAS_THRESHOLD 300  // Ngưỡng khí

void setup() {
    pinMode(MQ135_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    Wire.begin(0x0A); // Địa chỉ I2C của Uno thứ 3 (0x0A)
    Wire.onRequest(requestEvent); // Gọi hàm khi ESP32 yêu cầu dữ liệu
    Serial.begin(9600);
    Serial.println("MQ-135 Sensor Reading...");
}

void loop() {
    int gasValue = analogRead(MQ135_PIN);  // Đọc giá trị từ cảm biến
    Serial.print("Gas Value: ");
    Serial.println(gasValue);
    
    if (gasValue > GAS_THRESHOLD) {
        tone(BUZZER_PIN, 1000); // Phát âm thanh 1000Hz
        Serial.println("WARNING: High Gas Level!");
    } else {
        noTone(BUZZER_PIN); // Tắt còi
    }
    
    delay(1000); // Đợi 1 giây
}

// Hàm gửi dữ liệu qua I2C khi ESP32 yêu cầu
void requestEvent() {
    int gasValue = analogRead(MQ135_PIN);
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "Gas:%d", gasValue); // Định dạng chuỗi
    Wire.write(buffer); // Gửi dữ liệu qua I2C
}