// Author: Brian Scully
// Copyright (c) 2016 Agponics

#ifndef __HCSR04_SENSOR_H__
#define __HCSR04_SENSOR_H__

// Very important: The Ultrasonic sensor requires 2 Arduino pins:
// one for a trigger and one for an echo. 
// This implementation assumes the two pins are consecutive with the echo first.

#include <Arduino.h>
#include <base_device.h>

#define HCSR04_DBG 0 // turn on to get detailed debug info for this module
#if HCSR04_DBG == 1
#define HCSR04_DBGMSG(msg) Serial.println(msg);
#else 
#define HCSR04_DBGMSG(msg)
#endif

// a class to represent a HC-SR04 Ultrasonic sensor
class CHcsr04Sensor : public CDevice
{
public: 
    CHcsr04Sensor() : CDevice() {}
    void   set_pin(int pin); 
    String get_status_str();
private:
    int    get_echo_pin()    {return get_pin();}
    int    get_trigger_pin() {return get_pin()+1;} 
};

#endif // __HCSR04_SENSOR_H__
