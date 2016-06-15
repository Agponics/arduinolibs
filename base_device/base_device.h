#ifndef __BASE_DEVICE_H__
#define __BASE_DEVICE_H__

#include <Arduino.h>

// Author: Brian Scully
// Copyright (c) 2016 Agponics

// a generic base class for any device/sensor connected to the arduino
class CDevice
{
public:
    CDevice() : m_pin_id(0), m_name("") {}
    void   set_pin(int pin)        {m_pin_id = pin;}
    void   set_name(String name)   {m_name = name;}
    int    get_pin()               {return m_pin_id;}
    String get_name()              {return m_name;}
    String get_status_str()        {return get_name();}
private:
    int       m_pin_id; // the Arduino pin for this device
    String    m_name;   // a unique name to refer to this device
};

#endif // __BASE_DEVICE_H__
