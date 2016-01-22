// Author: Brian Scully
// Copyright (c) 2016 Agponics

// a class to represent a relay switch

#ifndef __RELAY_SWITCH_H__
#define __RELAY_SWITCH_H__

#include <Arduino.h>
#include <base_device.h>

class CRelay : public CDevice
{
public:
    CRelay() : m_status(false), CDevice() {};
    void    set_status(boolean sts) {m_status = sts; digitalWrite(get_pin(), sts ? HIGH : LOW);}
    boolean get_status()            {return m_status;}
    String  get_status_str()        {return CDevice::get_status_str() + (m_status ? String(":1") : String(":0"));}
private:
    boolean m_status; // whether this relay is on or off
};

#endif // __RELAY_SWITCH_H__
