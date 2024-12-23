#ifndef MY_WIFI_H_
#define MY_WIFI_H_
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "constant.h"

class MYWIFI{
public :
    MYWIFI();
    void connect();
};
#endif /*MY_WIFI_H_*/