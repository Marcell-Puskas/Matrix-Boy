#include "matrix_boy_IO.h"

int egg_map[mapx][mapy];

const uint32_t pad_color = matrix.Color(255, 255, 255);

const uint32_t egg_colors[] = {
    0,
    matrix.Color(255, 0, 0),
    matrix.Color(255, 255, 0),
    matrix.Color(0, 255, 0),
    matrix.Color(0, 255, 255),
    matrix.Color(0, 0, 255),
};

const int egg_color_num = 4;
const int pad_size = 3;

int spawnrate;
int score;
int pos_pad;
extern bool run;
extern bool gameover;
extern char keychar;
int speed2;

void input2()
{
    keychar = NULL;

    if(Serial.available()) keychar = Serial.read();

    if(analogRead(JOYX) < 384)
    {
        if(timeout_x == 0)
        {
            keychar = 'a';
            timeout_x =  default_timeout;
        }
    }
    else if(analogRead(JOYX) > 640)
    {
        if(timeout_x == 0)
        {
            keychar = 'd';
            timeout_x =  default_timeout;
        }
    }
    else timeout_x = 0;

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
            for (size_t i = 0; i < 200 && digitalRead(JOYB) == 0; i++)
                delay(input_update);
            
            if(digitalRead(JOYB) == 0)
            {
                keychar = 'e';
                timeout_b = restart_timeout;
            }
            else
            {
                matrix.drawRect(1, 4, 2, 8, pause_color);
                matrix.drawRect(5, 4, 2, 8, pause_color);
                matrix.show();
                while (digitalRead(JOYB) == 1)
                    delay(input_update);
                
                timeout_b = default_timeout;
            }
        }
    }
    else timeout_b = 0;

    if(timeout_x != 0) timeout_x--;
    if(timeout_y != 0) timeout_y--;
    //if(timeout_b != 0) timeout_b--;
    
    //return keychar;
}

void Egg_print()
{
    for(size_t cy = 0; cy < mapy; cy++)
    {
        for(size_t cx = 0; cx < mapx; cx++)
        {
            matrix.drawPixel(cx, cy, egg_colors[ egg_map[cx][cy] ]);
        }   
    }
    matrix.drawLine(pos_pad, mapy -1, pos_pad + pad_size -1, mapy-1, pad_color);
    matrix.show();
}

void Egg_game()
{
    run = true;
    gameover = false;
    memset(egg_map, 0, sizeof(egg_map));
    pos_pad = 0;
    speed2 = 25;
    spawnrate = 4;
    score = 0;

    while(run)
    {
        egg_map[ random(mapx) ][0] = random(1, egg_color_num);

        for(size_t rounds = 0; rounds < spawnrate && run; rounds++)
        {
            for(int cy = mapy - 2; cy >= 0; cy--)
            {
                for(size_t cx = 0; cx < mapx; cx++)
                {
                    if(egg_map[cx][cy] != 0)
                    {
                        egg_map[cx][cy + 1] = egg_map[cx][cy];
                        egg_map[cx][cy] = 0;
                    }
                }
            }

            for (size_t i = 0; i < mapx; i++)
            {
                if(egg_map[i][mapy - 1] != 0)
                {
                    if(pos_pad <= i && i < pos_pad + pad_size)
                    {
                        egg_map[i][mapy - 1] = 0;
                        score++;
                        speed2 = max(10, 15 - score);
                    }
                    else
                    {
                        run = false;
                        gameover = true;
                    }
                }
            }

            for (size_t i = 0; i < speed2; i++)
            {
                input2();
                switch (keychar)
                {
                    case 'd': if(pos_pad + pad_size < mapx) pos_pad++; break;
                    case 'a': if(pos_pad > 0) pos_pad--; break;
                    case 'e': run = false;
                }
                Egg_print();
                delay(input_update);
            }
        }
    }

    if(gameover)
    {
        Serial.print("Game over, Score: ");
        Serial.println(score);
        matrix.setCursor(0, 0);
        matrix.clear();
        matrix.print(score);
        matrix.show();
        delay(2000);// hardcode
    }
}
