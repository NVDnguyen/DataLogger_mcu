#include "aws_iot.h"

AWSIoT::AWSIoT()
    : cert(cacert), client_crt(client_cert), key(privkey), client(net) {
}

// Init
void AWSIoT::begin() {
    NTPConnect();
    connectAWS();

}

// Connect to WiFi
status_t AWSIoT::checkWiFi() {
    // Wait for WiFi connection
    if (WiFi.status() != WL_CONNECTED) {
        //Serial.println("> AWS : WiFi not connected!");
        return ERROR;
    }
    return SUCCESS;
    
}

// Connect to NTP server to set time
void AWSIoT::NTPConnect() {
    //Serial.print("Setting time using SNTP");
    configTime(TIME_ZONE * 3600, 0, "pool.ntp.org", "time.nist.gov");
    time_t now = time(nullptr);
    while (now < 1510592825) { // January 13, 2018
        delay(500);
        //Serial.print(".");
        now = time(nullptr);
    }
    //Serial.println("done!");
}

// Connect to AWS IoT Core using MQTT
void AWSIoT::connectAWS() {
    // Set CA and client certificate for secure communication
    net.setTrustAnchors(&cert);
    net.setClientRSACert(&client_crt, &key);

    // Connect MQTT client to AWS IoT Core
    client.setServer(MQTT_HOST, 8883);

    //Serial.println("Connecting to AWS IoT");

    while (!client.connect(THINGNAME)) {
        //Serial.print(".");
        delay(1000);
    }

    if (!client.connected()) {
        //Serial.println("AWS IoT Timeout!");
        return;
    }

    Serial.println("AWS IoT Connected!");
}

void AWSIoT::loop() {
    client.loop();
}

// Publish message to AWS IoT Core
void AWSIoT::publishMessage(const char * topic,char * msg) {
    client.publish(topic, msg);
}

// Subscribe to a topic
void AWSIoT::subscribeToTopic(const char* topic, void (*_mqttcallback)(char*, uint8_t*, unsigned int)) {
    client.subscribe(topic);
    Serial.print("Subscribed to topic: ");
    Serial.println(topic);
    client.setCallback(_mqttcallback); 
}

