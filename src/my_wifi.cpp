#include "my_wifi.h"

MYWIFI::MYWIFI(){}

void MYWIFI::connect(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.println(String("Attempting to connect to SSID: ") + String(WIFI_SSID));

    // Wait for WiFi connection
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("WiFi connected!");
}