#include <Wire.h>
#include "DHT.h"

#define RELAY_PIN 7
#define WATER_SENSOR A0
#define WATER_THRESHOLD 200
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

bool isPumpOn = false;

void setup() {
    Wire.begin(0x09);
    Wire.onRequest(sendData);
    Serial.begin(9600);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);
    dht.begin();
}

void loop() {
    int waterRaw = analogRead(WATER_SENSOR);
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (waterRaw < WATER_THRESHOLD) {
        digitalWrite(RELAY_PIN, HIGH);
        isPumpOn = true;
    } else {
        digitalWrite(RELAY_PIN, LOW);
        isPumpOn = false;
    }


    Serial.print("Nhiệt Độ: ");
    Serial.print(t);
    Serial.print(", Độ Ẩm: ");
    Serial.print(h);
    Serial.print(", Nước: ");
    Serial.println(waterRaw);

    delay(1000);
}

void sendData() {
    int waterRaw = analogRead(WATER_SENSOR);
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    char buffer[32];
    if (isnan(h) || isnan(t)) {
        Serial.println("DHT11 error!");
        strcpy(buffer, "0.0,0.0,0,0");
    } else {
        // Thay snprintf bằng cách định dạng thủ công
        dtostrf(t, 4, 1, buffer);          // Chuyển nhiệt độ thành chuỗi (4 ký tự, 1 thập phân)
        strcat(buffer, ",");
        dtostrf(h, 4, 1, buffer + strlen(buffer)); // Chuyển độ ẩm
        strcat(buffer, ",");
        itoa(waterRaw, buffer + strlen(buffer), 10); // Chuyển waterRaw
        strcat(buffer, ",");
        itoa(isPumpOn ? 1 : 0, buffer + strlen(buffer), 10);   // Chuyển isPumpOn
    }

    Wire.write(buffer, strlen(buffer));
}