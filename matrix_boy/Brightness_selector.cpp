#include "matrix_boy_IO.h"

bool selecting = true;
char keychar2 = NULL;;
extern int bright;
const extern int max_bright_select;
const extern int max_bright;
const extern int min_bright;

void Brightness_selector()
{
    const uint32_t color_slide = matrix.Color(255, 255, 255);
    selecting = true;

    while(selecting)
    {
        if(Serial.available()) keychar2 = Serial.read();

        if(analogRead(JOYY) < 384)
        {
            if(timeout_y == 0)
            {
                keychar2 = 'w';
                timeout_y =  default_timeout;
            }
        }
        else if(analogRead(JOYY) > 640)
        {
            if(timeout_y == 0)
            {
                keychar2 = 's';
                timeout_y = default_timeout;
            }
        }
        else timeout_y = 0;

        if(digitalRead(JOYB) == 0)
        {
            if(timeout_b == 0)
            {
                keychar2 = 'o';
                timeout_b = restart_timeout;
            }
        }
        else timeout_b = 0;

        if(timeout_y != 0) timeout_y--;

        switch (keychar2)
        {
            case 'w':
                if(bright < max_bright_select) bright++;
                break;

            case 's':
                if(bright > 1) bright--;
                break;
            
            case 'o':
                selecting = false;
                break;
        }
        keychar2 = NULL;

        matrix.setBrightness(bright);

        matrix.clear();
        matrix.setCursor(0, 0);
        matrix.print(bright);
        matrix.drawLine(mapx -1 , mapy - bright, mapx -1, mapy - 1, color_slide);
        matrix.show();

        delay(input_update);
    }
}