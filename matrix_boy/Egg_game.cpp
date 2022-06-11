#include "Egg_game.h"

void Egg::Egg_print()
{
    for(size_t cy = 0; cy < mapy; cy++)
    {
        for(size_t cx = 0; cx < mapx; cx++)
        {
            matrix.drawPixel(cx, cy, egg_colors[ map[cx][cy] ]);
        }   
    }
    matrix.drawFastHLine(pos_pad, mapy -1, pad_size, pad_color);
    matrix.show();
}

void Egg::Egg_game()
{
    extern bool gyro_mode;
    run = true;
    gameover = false;
    memset(map, 0, sizeof(map));
    pos_pad = 0;
    speed = 25;
    spawnrate = 4;
    points = 0;

    while(run)
    {
        map[ random(mapx) ][0] = random(1, egg_color_num);

        for(size_t rounds = 0; rounds < spawnrate && run; rounds++)
        {
            for(int8_t cy = mapy - 2; cy >= 0; cy--)
            {
                for(size_t cx = 0; cx < mapx; cx++)
                {
                    if(map[cx][cy] != 0)
                    {
                        map[cx][cy + 1] = map[cx][cy];
                        map[cx][cy] = 0;
                    }
                }
            }

            for (size_t i = 0; i < mapx; i++)
            {
                if(map[i][mapy - 1] != 0)
                {
                    if(pos_pad <= i && i < pos_pad + pad_size)
                    {
                        map[i][mapy - 1] = 0;
                        points++;
                        speed = max(10, 15 - points);
                    }
                    else
                    {
                        run = false;
                        gameover = true;
                    }
                }
            }

            for (size_t i = 0; i < speed; i++)
            {
                Input();
                switch (keychar)
                {
                    case 'd': if(pos_pad + pad_size < mapx) pos_pad++; break;
                    case 'a': if(pos_pad > 0) pos_pad--; break;
                    case 'e': run = false;
                }
                if(gyro_mode)
                {
                    pos_pad = gyro_xmove(0, mapx - pad_size);
                    
                }
                Egg_print();
                delay(input_update);
            }
        }
    }

    if(gameover)
    {
        matrix.setCursor(0, 0);
        matrix.clear();
        matrix.print(points);
        matrix.show();
        delay(2000);// hardcode
    }
}
