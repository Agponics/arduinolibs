// Author: Brian Scully
// Copyright (c) 2016 Agponics

#include <cmd_protocol.h>

boolean read_command(String& cmd)
{
    String line = "";

    // wait until there's data available on the serial connection
    while (Serial.available() <= 0)
    {
        delay(READ_DELAY);
    }

    // grab all available bytes from the serial connection and convert to a string:
    while (Serial.available() != 0)
    {
        line += String((char)Serial.read());
        delay(10); // without this slight delay sometimes command strings were cut off
    }

    CMD_PROTOCOL_DBGMSG((String("Received: ") + line))

    cmd = line;
    return true;
}

unsigned int parse_command(String cmd, String& switch_name, boolean& enable)
{
    CmdType op_type = INVALID;
    
    if (cmd.startsWith("get"))
    {
        op_type = GET;
    }
    else if (cmd.startsWith("set"))
    {
        // SET commands should be formatted as set:[index]:[enable (0 or 1)]
      
        int index1 = -1;   // index within the command of the first ':'
        int index2 = -1;   // index within the command of the second ':'
        String str_name;   // the desired relay to control (as a string)
        String str_enable; // whether to enable/disable the relay (as a string)
        
        do
        {
            // find first ':'
            index1 = cmd.indexOf(':');
            if (index1 == -1)
            {
                CMD_PROTOCOL_DBGMSG("SET command given with no parameters") 
                break;
            }
            
            // find second ':'
            index2 = cmd.indexOf(':', index1 + 1);
            if ((index2 <= index1 + 1) ||     // failed to find another ':', or it immediately followed the first
                (index2 >= cmd.length() - 1)) // or there was nothing after it
            {
                CMD_PROTOCOL_DBGMSG("SET command requires a 2nd parameter") 
                break;
            }
            
            // switch name is after the first ':'
            str_name = cmd.substring(index1 + 1, index2);
            //CMD_PROTOCOL_DBGMSG( (String("switch index as a string: ") + str_idx) ) 
            
            // enable/disable parameter is after the second ':'
            str_enable = cmd.substring(index2 + 1); 
            //CMD_PROTOCOL_DBGMSG( (String("enable/disable as a string: ") + str_enable) ) 
            
            
            // set output parameters
            switch_name = str_name;
            enable = (str_enable.toInt() != 0);
            
            op_type = SET;
            
        } while(0);
    }
    else
    {
        // invalid
        CMD_PROTOCOL_DBGMSG("invalid command string")
    }

    return op_type;
}

