// Author: Brian Scully
// Copyright (c) 2016 Agponics

#include "dht22_sensor.h"

String CDht22Sensor::get_status_str()
{
    double temp = 0.0;
    double humidity = 0.0;

    int    chk = m_dht.read22(get_pin());
    String out = CDevice::get_status_str();

    switch (chk)
    {
        case DHTLIB_OK:
            out += "temp:" + String(int(celsius_to_fahrenheit(m_dht.temperature))) + "\n";
            out += CDevice::get_status_str() + "humidity:" + String(int(m_dht.humidity));
            break;
        case DHTLIB_ERROR_CHECKSUM: 
            DHT_DBGMSG("Checksum error")
            break;
        case DHTLIB_ERROR_TIMEOUT: 
            DHT_DBGMSG("Time out error") 
            break;
        default: 
            DHT_DBGMSG("Unknown error") 
            break;
    }
    return out;   
}


