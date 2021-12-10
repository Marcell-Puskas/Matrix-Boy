#include "matrix_boy_IO.h"

extern bool run;
extern int volume;
const  int max_volume = 16;

void Volume_selector()
{
    const uint32_t color_slide = matrix.Color(255, 255, 255);
    run = true;
    pause_menu = false;

    while(run)
    {
        Input();

        switch (keychar)
        {
            case 'w':
                if(volume < max_volume) volume++;
                break;

            case 's':
                if(volume > 0) volume--;
                break;
            
            case 'o':
                run = false;
                break;
        }

        matrix.clear();
        matrix.setCursor(0, 0);
        matrix.print(volume);
        matrix.drawLine(mapx -1 , mapy - volume, mapx -1, mapy - 1, color_slide);
        matrix.show();

        delay(input_update);
    }
}