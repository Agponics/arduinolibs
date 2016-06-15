// Author: Brian Scully
// Copyright (c) 2016 Agponics

#include "ds18b20_sensor.h"

void CDs18b20Sensor::set_pin(int pin) 
{
    CDevice::set_pin(pin); 

    m_one_wire = OneWire(pin); 

    m_dt.setOneWire(&m_one_wire);
    m_dt.begin();

    m_device_cnt = m_dt.getDeviceCount();
    if (m_device_cnt > MAX_PROBES)
    {
        m_device_cnt = MAX_PROBES;
    }

    for (uint8_t i = 0; i < m_device_cnt; i++)
    {
        if (!m_dt.getAddress(m_addrs[i], i))
        {
            DS18B20_DBGMSG("Failed to get address!")
        }
    }
}

String CDs18b20Sensor::get_status_str()
{
    float temp = 0.0;
    String out = "";

    // have all probes read temp
    m_dt.requestTemperatures();

    for (uint8_t i = 0; i < m_device_cnt; i++)
    {
        temp = m_dt.getTempF(m_addrs[i]);
        out += CDevice::get_status_str();
        out += "probe" + String(i) + ":temp:";
        out += String(int(temp));
        if (i < m_device_cnt - 1)
        {
            out += "\n";
        }
    }
            
    return out;   
}

String CDs18b20Sensor::get_addrs_str()
{
    uint8_t next_addr[8] = {0};
    uint8_t i = 0;

    String out = "One-wire Addresses Found:\n";
    
    while (m_dt.getAddress(next_addr, i))
    {
        out += String(i) + ":";
        for (int j = 0; j < 8; j++)
        {
            out += " 0x" + String(next_addr[j], HEX);
        }
        out += "\n";
        i++;
    }

    return out;
}


