#include "matrix_boy_IO.h"

extern bool run;
extern int bright;
const  int max_bright = 16;

void Brightness_selector()
{
    const uint32_t color_slide = matrix.Color(255, 255, 255);
    run = true;

    while(run)
    {
        if(Serial.available()) keychar = Serial.read();

        if(analogRead(JOYY) < 384)
        {
            if(timeout_y == 0)
            {
                keychar = 'w';
                timeout_y =  default_timeout;
            }
        }
        else if(analogRead(JOYY) > 640)
        {
            if(timeout_y == 0)
            {
                keychar = 's';
                timeout_y = default_timeout;
            }
        }
        else timeout_y = 0;

        if(digitalRead(JOYB) == 0)
        {
            if(timeout_b == 0)
            {
                keychar = 'o';
                timeout_b = restart_timeout;
            }
        }
        else timeout_b = 0;

        if(timeout_y != 0) timeout_y--;

        switch (keychar)
        {
            case 'w':
                if(bright < max_bright) bright++;
                break;

            case 's':
                if(bright > 1) bright--;
                break;
            
            case 'o':
                run = false;
                break;
        }
        keychar = NULL;

        matrix.setBrightness(bright);

        matrix.clear();
        matrix.setCursor(0, 0);
        matrix.print(bright);
        matrix.drawLine(mapx -1 , mapy - bright, mapx -1, mapy - 1, color_slide);
        matrix.show();

        delay(input_update);
    }
}