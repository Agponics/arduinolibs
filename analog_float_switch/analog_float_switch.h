// Author: Brian Scully
// Copyright (c) 2016 Agponics

// a class to represent an analog float switch

#ifndef __ANALOG_FLOAT_SWITCH_H__
#define __ANALOG_FLOAT_SWITCH_H__

#include <Arduino.h>
#include <base_device.h>


class CAnalogFloatSwitch : public CDevice
{
public:
    CAnalogFloatSwitch() : CDevice() {}
    void   set_pin(int pin) {CDevice::set_pin(pin); pinMode(pin, INPUT);}
    String get_status_str() {return CDevice::get_status_str() + ":" + (analogRead(get_pin()) == 1023 ? "1" : "0");}
};

#endif //__ANALOG_FLOAT_SWITCH_H__