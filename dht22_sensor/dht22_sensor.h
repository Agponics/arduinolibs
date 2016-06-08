// Author: Brian Scully
// Copyright (c) 2016 Agponics

// This class wraps  DHT-22 reference code from http://playground.arduino.cc/Main/DHTLib.
// Save the latest .h and .cpp files to the same local directory as this file. 

#ifndef __DHT22_SENSOR_H__
#define __DHT22_SENSOR_H__

#include <Arduino.h>
#include <base_device.h>
#include "dht.h"

#define DHT_DBG 0 // turn on to get detailed debug info for this module
#if DHT_DBG == 1
#define DHT_DBGMSG(msg) Serial.println(msg);
#else 
#define DHT_DBGMSG(msg)
#endif

// a class to represent a DHT-22 sensor
class CDht22Sensor : public CDevice
{
public: 
    CDht22Sensor() : CDevice() {}
    void   set_pin(int pin); 
    String get_status_str();
private:
    static double celsius_to_fahrenheit(double c) {return (c * (9.0/5.0) + 32.0);}
    dht m_dht;
};

#endif // __DHT22_SENSOR_H__
