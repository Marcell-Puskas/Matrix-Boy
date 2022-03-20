#include "matrix_boy_IO.h"

extern bool gyro_mode;
extern int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void Input(bool no_timeout)
{
    keychar = 'n';

    if(Serial.available()) keychar = Serial.read();

    if(true) {
        if(analogRead(JOYX) < joy_low_threshold)
        {
            if(timeout_x == 0 || no_timeout)
            {
                keychar = 'a';
                timeout_x =  left_timeout;
            }
        }
        else if(analogRead(JOYX) > joy_high_threshold)
        {
            if(timeout_x == 0 || no_timeout)
            {
                keychar = 'd';
                timeout_x =  right_timeout;
            }
        }
        else timeout_x = 0;

        if(analogRead(JOYY) < joy_low_threshold)
        {
            if(timeout_y == 0 || no_timeout)
            {
                keychar = 'w';
                timeout_y =  up_timeout;
            }
        }
        else if(analogRead(JOYY) > joy_high_threshold)
        {
            if(timeout_y == 0 || no_timeout)
            {
                keychar = 's';
                timeout_y = down_timeout;
            }
        }
        else timeout_y = 0;

        if(digitalRead(JOYB) == 0)
        {
            if(timeout_b == 0)
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
        else timeout_b = 0;

        if(timeout_x != 0) timeout_x--;
        if(timeout_y != 0) timeout_y--;
        //if(timeout_b != 0) timeout_b--;
    }
    else {
        gyro_read();
        /* if(GyX < gyro_low_threshold)
        {
            if(timeout_x == 0 || no_timeout)
            {
                keychar = 'a';
                timeout_x =  left_timeout;
            }
        }
        else if(GyX > gyro_high_threshold)
        {
            if(timeout_x == 0 || no_timeout)
            {
                keychar = 'd';
                timeout_x =  right_timeout;
            }
        }
        else timeout_x = 0; */
    }
}