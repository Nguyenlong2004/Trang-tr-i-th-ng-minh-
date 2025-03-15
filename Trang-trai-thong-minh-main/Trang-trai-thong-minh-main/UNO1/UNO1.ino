#include <Wire.h>
#include <Stepper.h>
#include <DS1302.h>

#define UNO1_ADDR 0x08
#define RST_PIN  5
#define DAT_PIN  7
#define CLK_PIN  6
#define cambien A0  
#define den 2  

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
DS1302 rtc(RST_PIN, DAT_PIN, CLK_PIN);

struct Alarm {
    int hour;
    int minute;
};

Alarm alarms[3] = {
    {8, 56}, 
    {12, 45}, 
    {14, 54}
};

bool dongCoDangQuay = false;  
String output = "";

void setup() {
    Serial.begin(9600);
    Wire.begin(UNO1_ADDR);
    Wire.onRequest(sendDataToESP32);
    rtc.halt(false);
    rtc.writeProtect(false);
    myStepper.setSpeed(15);
    pinMode(den, OUTPUT);
    digitalWrite(den, LOW);  
    pinMode(cambien, INPUT);
    
    Serial.println("🟢 Hệ thống sẵn sàng!");
}

void loop() {
    Time now = rtc.getTime();
    output = "Giờ hiện tại: " + String(now.hour) + ":" + String(now.min) + ":" + String(now.sec);

    for (int i = 0; i < 3; i++) {
        if (now.hour == alarms[i].hour && now.min == alarms[i].minute && now.sec == 0) {
            output += " 🔔 Đang quay";
            dongCoDangQuay = true;
            quayDongCo();
            dongCoDangQuay = false;
            output += " ✅ Hoàn thành phiên quay";
        }
    }

    capNhatCamBien();  
    Serial.println(output);
    delay(500);  
}

void quayDongCo() {
    unsigned long startTime = millis();
    while (millis() - startTime < 60000) {
        myStepper.step(-19);
        capNhatCamBien();  
    }
}

void capNhatCamBien() {
    int giatri = analogRead(cambien);
    digitalWrite(den, giatri > 500 ? HIGH : LOW);  
    output += " 🔦 Cảm biến: " + String(giatri) + " | LED: " + (giatri > 500 ? "ON" : "OFF");
}

void sendDataToESP32() {
    Time now = rtc.getTime();
    int giatri = analogRead(cambien);
    bool ledStatus = (giatri > 500);

    char buffer[32];  
    snprintf(buffer, sizeof(buffer), 
             "%02d:%02d:%02d|LDR:%d|LED:%d|M:%d", 
             now.hour, now.min, now.sec, 
             giatri, ledStatus, dongCoDangQuay);

    Serial.print("📤 Dữ liệu gửi ESP32: ");
    Serial.println(buffer);

    Wire.write(buffer);
    delay(10);
}


