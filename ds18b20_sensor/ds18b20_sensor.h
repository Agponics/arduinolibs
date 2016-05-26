// Author: Brian Scully
// Copyright (c) 2016 Agponics

// This class wraps  DS18B20 reference code from the following locations:
// https://github.com/PaulStoffregen/OneWire
// https://github.com/milesburton/Arduino-Temperature-Control-Library
// Save the latest .h and .cpp files to the same local directory as this file. 

#ifndef __DS18B20_SENSOR_H__
#define __DS18B20_SENSOR_H__

#include <Arduino.h>
#include <base_device.h>
#include "OneWire.h"
#include "DallasTemperature.h"

#define DS18B20_DBG 0 // turn on to get detailed debug info for this module
#if DS18B20_DBG == 1
#define DS18B20_DBGMSG(msg) Serial.println(msg);
#else 
#define DS18B20_DBGMSG(msg)
#endif

// a class to represent a DS18B20 sensor
class CDs18b20Sensor : public CDevice
{
public: 
    CDs18b20Sensor() : CDevice(), m_one_wire(0) {}
    void   set_pin(int pin); 
    String get_status_str();
    String get_addrs();      // returns the addresses for all probes on the wire
private:
    static double celsius_to_fahrenheit(double c) {return (c * (9.0/5.0) + 32.0);}
    OneWire           m_one_wire;
    DallasTemperature m_dt;
};

#endif // __DS18B20_SENSOR_H__
