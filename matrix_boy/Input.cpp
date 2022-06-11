#include "matrix_boy_IO.h"

extern bool gyro_mode;
long xtime, ytime, btime;
long blasttime;
bool b_pressed = false;

extern int freeMemory();

void Input(bool no_timeout)
{
    keychar = 'n';

    if(Serial.available()) keychar = Serial.read();

    /* Serial.print(analogRead(JOYX));
    Serial.print("\t");
    Serial.print(analogRead(JOYY));
    Serial.print("\t");
    Serial.println(digitalRead(JOYB)); */

    Serial.print("free Mem: ");
    Serial.println(freeMemory());

    if(analogRead(JOYX) < joy_low_threshold)
    {
        if(xtime< millis() || no_timeout)
        {
            keychar = 'a';
            xtime =  millis() + left_timeout ;
        }
    }
    else if(analogRead(JOYX) > joy_high_threshold)
    {
        if(xtime < millis() || no_timeout)
        {
            keychar = 'd';
            xtime =  millis() + right_timeout;
        }
    }
    else xtime = 0;

    if(analogRead(JOYY) < joy_low_threshold)
    {
        if(ytime < millis() || no_timeout)
        {
            keychar = 'w';
            ytime =  millis() + up_timeout;
        }
    }
    else if(analogRead(JOYY) > joy_high_threshold)
    {
        if(ytime < millis() || no_timeout)
        {
            keychar = 's';
            ytime = millis() + down_timeout;
        }
    }
    else ytime = 0;

    if(digitalRead(JOYB) == b_down)
    {
        if(btime < millis())
        {
            if(millis() - blasttime > 1000)
            {
                keychar = 'e';
                btime = millis() + exit_timeout;
                b_pressed = false;
            }
            else
            {
                b_pressed = true;
            }
        }
    }
    else 
    {
        if(b_pressed)
        {   
            if(pause_menu)
            {
                matrix.drawRect(mapx / 2 - 3, mapy / 2 - 4, 2, 8, pause_color);
                matrix.drawRect(mapx / 2 + 1, mapy / 2 - 4, 2, 8, pause_color);
                matrix.show();
                while (digitalRead(JOYB) == b_up)
                    delay(input_update);
                btime = millis() + restart_timeout;
            }
            else
            {
                keychar = 'o';
                btime = millis() + button_timeout;
            }
            b_pressed = false;
        }
        blasttime = millis();
    }
}