#include "matrix_boy_IO.h"

extern bool gyro_mode;
long xtime, ytime, btime;

void Input(bool no_timeout)
{
    keychar = 'n';

    if(Serial.available()) keychar = Serial.read();

    if(analogRead(JOYX) < joy_low_threshold)
    {
        if(xtime + left_timeout < millis() || no_timeout)
        {
            keychar = 'a';
            xtime =  millis();
        }
    }
    else if(analogRead(JOYX) > joy_high_threshold)
    {
        if(xtime + right_timeout < millis() || no_timeout)
        {
            keychar = 'd';
            xtime =  millis();
        }
    }
    else xtime = 0;

    if(analogRead(JOYY) < joy_low_threshold)
    {
        if(ytime + up_timeout < millis() || no_timeout)
        {
            keychar = 'w';
            ytime =  millis();
        }
    }
    else if(analogRead(JOYY) > joy_high_threshold)
    {
        if(ytime + down_timeout < millis() || no_timeout)
        {
            keychar = 's';
            ytime = millis();
        }
    }
    else ytime = 0;

    if(digitalRead(JOYB) == 0)
    {
        if(btime + button_timeout < millis())
        {
            for (size_t i = 0; i < exit_timeout && digitalRead(JOYB) == 0; i++)
                delay(input_update);
            
            if(digitalRead(JOYB) == 0)
            {
                keychar = 'e';
                timeout_b = restart_timeout;
            }
            else
            {
                if(pause_menu)
                {
                    matrix.drawRect(1, 4, 2, 8, pause_color);
                    matrix.drawRect(5, 4, 2, 8, pause_color);
                    matrix.show();
                    while (digitalRead(JOYB) == 1)
                        delay(input_update);
                    
                    timeout_b = button_timeout;
                }
                else
                {
                    keychar = 'o';
                    timeout_b = button_timeout;
                }
            }
        }
    }
    else btime = 0;
}