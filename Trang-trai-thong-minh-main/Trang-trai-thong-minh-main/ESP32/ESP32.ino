#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define UNO1_ADDR 0x08  // Uno 1
#define UNO2_ADDR 0x09  // Uno 2
#define UNO3_ADDR 0x0A  // Uno 3 (MQ-135)

const char* ssid = "WIFI GIANG VIEN";
const char* password = "dhdn7799";
const char* server_url = "http://172.16.65.173:5000//update";  // Flask server

// Khai báo prototype
String cleanString(const char* input);

void setup() {
    Serial.begin(115200);
    Wire.begin(); // ESP32 làm master I2C
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n🟢 Đã kết nối WiFi!");
}

void loop() {
    char buffer1[32] = {0};
    char buffer2[32] = {0};
    char buffer3[32] = {0};

    // Đọc từ UNO 1
    Wire.requestFrom(UNO1_ADDR, 31);
    int i = 0;
    while (Wire.available() && i < 31) {
        buffer1[i++] = Wire.read();
    }
    buffer1[i] = '\0';
    String uno1_clean = cleanString(buffer1);

    // Đọc từ UNO 2
    Wire.requestFrom(UNO2_ADDR, 31);
    i = 0;
    while (Wire.available() && i < 31) {
        buffer2[i++] = Wire.read();
    }
    buffer2[i] = '\0';
    String uno2_clean = cleanString(buffer2);

    // Đọc từ UNO 3 (MQ-135)
    Wire.requestFrom(UNO3_ADDR, 31);
    i = 0;
    while (Wire.available() && i < 31) {
        buffer3[i++] = Wire.read();
    }
    buffer3[i] = '\0';
    String uno3_clean = cleanString(buffer3);

    // In dữ liệu đã làm sạch để kiểm tra
    Serial.print("📥 UNO 1 (Clean): ");
    Serial.println(uno1_clean);
    Serial.print("📥 UNO 2 (Clean): ");
    Serial.println(uno2_clean);
    Serial.print("📥 UNO 3 (MQ-135, Clean): ");
    Serial.println(uno3_clean);

    // Gửi dữ liệu lên Flask
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(server_url);
        http.addHeader("Content-Type", "application/json");

        String jsonPayload = "{";
        jsonPayload += "\"uno1\":\"" + uno1_clean + "\",";
        jsonPayload += "\"uno2\":\"" + uno2_clean + "\",";
        jsonPayload += "\"uno3\":\"" + uno3_clean + "\""; // Thêm dữ liệu từ Uno 3
        jsonPayload += "}";

        Serial.print("📤 JSON gửi đi: ");
        Serial.println(jsonPayload);

        int httpResponseCode = http.POST(jsonPayload);
        Serial.print("📤 HTTP Response Code: ");
        Serial.println(httpResponseCode);

        http.end();
    }

    delay(1000);
}

// Hàm làm sạch ký tự rác
String cleanString(const char* input) {
    String output = "";
    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        if (c >= 32 && c <= 126) {  // Giữ lại ký tự ASCII hợp lệ
            output += c;
        }
    }
    output.trim(); // Xóa khoảng trắng thừa
    return output;
}