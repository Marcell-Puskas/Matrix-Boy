#include "matrix_boy_IO.h"

void Snake_game()
{
    matrix.clear();

    //config
    const byte def_length = 3;
    const bool screen_warp = true;

    const uint16_t color_snake = matrix.Color(0, 255, 0);
    const uint16_t color_head = matrix.Color(255, 255, 0);
    const uint16_t color_food = matrix.Color(255, 0, 0);
    const uint16_t color_background = matrix.Color(0, 0, 0);

    //create varriables
    byte map[mapx][mapy];
    byte posx = random(mapx);
    byte posy = random(mapy);
    byte dir = random(4);

    bool run = true;
    bool gameover = false;

    byte snakelength = 0;

    byte foodx = random(mapx);
    byte foody = random(mapy);
    byte dir_input = 0;

    extern bool gyro_mode;

    memset(map, 0, sizeof(map));

    while (run && !gameover)
    {
        switch (dir_input)
        {
            case 0: if (dir != 1) dir = 0; break;
            case 1: if (dir != 0) dir = 1; break;
            case 2: if (dir != 3) dir = 2; break;
            case 3: if (dir != 2) dir = 3; break;
        }

        if(screen_warp)
        {
            switch (dir)
            {
                case 0:
                    if (posx + 1 >= mapx) posx = 0;
                    else posx++;
                    break;
                case 1:
                    if (posx <= 0) posx = mapx - 1;
                    else posx--;
                    break;
                case 2:
                    if (posy + 1 >= mapy) posy = 0;
                    else posy++;
                    break;
                case 3:
                    if (posy <= 0) posy = mapy - 1;
                    else posy--;
                    break;
            }
        }
        else
        {
            switch (dir)
            {
                case 0:
                    if (posx + 1 >= mapx) gameover = true;
                    else posx++;
                    break;
                case 1:
                    if (posx <= 0) gameover = true;
                    else posx--;
                    break;
                case 2:
                    if (posy + 1 >= mapy) gameover = true;
                    else posy++;
                    break;
                case 3:
                    if (posy <= 0) gameover = true;
                    else posy--;
                    break;
            }
        }

        if (map[posx][posy] > 0)
        {
            run = false;
            gameover = true;
        }

        map[posx][posy] = 1;

        if (posx == foodx && posy == foody)
        {
            while (map[foodx][foody] != 0)
            {
                foodx = random(mapx);
                foody = random(mapy);
            }
            snakelength++;
        }

        for (size_t cy = 0; cy < mapy; cy++)
        {
            for (size_t cx = 0; cx < mapx; cx++)
            {
                if (map[cx][cy] > 0)
                {
                    if(cx == posx && cy == posy) 
                        matrix.drawPixel(cx, cy, color_head);
                    else
                        matrix.drawPixel(cx, cy, color_snake);
                    
                    map[cx][cy]++;

                    if (map[cx][cy] > snakelength + def_length)
                    {
                        map[cx][cy] = 0;
                    }
                }
                else if (cx == foodx && cy == foody)
                {
                    matrix.drawPixel(cx, cy, color_food);
                }
                else
                {
                    matrix.drawPixel(cx, cy, color_background);
                }
            }
        }
        matrix.show();

        for (size_t i = 0; i < 20 + 50 / (snakelength + 1); i++)
        {
            Input(true);

            switch(keychar)
            {
                case 'd': dir_input = 0; break;
                case 'a': dir_input = 1; break;
                case 's': dir_input = 2; break;
                case 'w': dir_input = 3; break;
                case 'e': run = false; break;
            }
            delay(10);

            if(gyro_mode)
            {
                byte gyx = gyro_xmove(0, 10);
                byte gyy = gyro_ymove(0, 10);
                if(gyx >= 8) dir_input = 0;
                if(gyx <= 2) dir_input = 1;
                if(gyy >= 8) dir_input = 2;
                if(gyy <= 2) dir_input = 3;

                Serial.print(gyx);
                Serial.print("\t");
                Serial.println(gyy);
            }
        }
    }

    if (gameover)
    {
        matrix.setCursor(0, 0);
        matrix.clear();
        matrix.print(snakelength);
        matrix.show();
        delay(2000);
    }
}