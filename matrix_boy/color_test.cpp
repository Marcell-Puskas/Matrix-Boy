#include "matrix_boy_IO.h"

uint16_t index = 0;
uint16_t r = 0;
uint16_t g = 0;
uint16_t b = 255;
uint16_t c;

void drawcolor()
{
    c = matrix.Color(r, g, b);
    matrix.drawPixel(index % mapx, index / mapx, c);
    index = (index + 1) % (mapx * mapy);
    matrix.show();
    delay(50);
    
    Serial.print("r: ");
    Serial.print(r);
    Serial.print("\tg: ");
    Serial.print(g);
    Serial.print("\tb: ");
    Serial.print(b);
    Serial.print("\ti: ");
    Serial.print(index);
    Serial.println();
}

void color_test() {
    matrix.clear();
    bool run = true;
    char s;

    while (run)
    {
        /* if(Serial.available())
        {
        s = Serial.read();
        switch(s)
        {
            case 'r':
                r = Serial.readStringUntil('\n').toInt();
                break;

            case 'g':
                g = Serial.readStringUntil('\n').toInt();
                break;

            case 'b':
                b = Serial.readStringUntil('\n').toInt();
                break;

            case 'i':
                index = Serial.readStringUntil('\n').toInt();

            case 'p':
                c = matrix.Color(r, g, b);
                matrix.drawPixel(index % mapx, mapx / index, c);
                index++;
                break;
            
            case 'c':
                matrix.clear();
                break;

            case 'e':
                run = false;
                break;
        }

            Input();
            s = keychar;
            if(s == 'p')
            {
                c = matrix.Color(r, g, b);
                matrix.drawPixel(index % mapx, mapx / index, c);
                index++;
            }
            else if(s == 'e') run = false;
            else if(s == 'i') index = mapx * mapy % (index + 1);
            else if(s == 'c') matrix.clear();
            else if(s == 'r') r = 255 % (r + 1);
            else if(s == 'g') g = 255 % (g + 1);
            else if(s == 'b') b = 255 % (b + 1);
        }
        Input();
        Serial.print(keychar);
        s = keychar;
        if(s == 'p')
        {
            c = matrix.Color(r, g, b);
            matrix.drawPixel(index % mapx, mapx / index, c);
            index++;
        }
        else if(s == 'e') run = false;
        else if(s == 'i') index = mapx * mapy % (index + 1);
        else if(s == 'c') matrix.clear();
        else if(s == 'r') r = 255 % (r + 1);
        else if(s == 'g') g = 255 % (g + 1);
        else if(s == 'b') b = 255 % (b + 1); */

        Input();
        if(keychar == 'e') run = false;
        
        
        for (size_t rc = 0; rc < 255; rc++)
        {
            r++;
            drawcolor();
        }
        for (size_t cb = 0; cb < 255; cb++)
        {
            b--;
            drawcolor();
        }
        
        for (size_t gc = 0; gc < 255; gc++)
        {
            g++;
            drawcolor();
        }
        for (size_t rc = 0; rc < 255; rc++)
        {
            r--;
            drawcolor();
        }
        for (size_t cb = 0; cb < 255; cb++)
        {
            b++;
            drawcolor();
        }
        for (size_t cg = 0; cg < 255; cg++)
        {
            g--;
            drawcolor();
        }
    }
}

