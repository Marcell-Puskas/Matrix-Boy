#include "matrix_boy_IO.h"

const int rows = 8;
const int coloums = mapx / 2;

const uint32_t row_colors[] = {
    matrix.Color(255, 0, 0),
    matrix.Color(255, 0, 0),
    matrix.Color(255, 170, 0),
    matrix.Color(255, 170, 0),
    matrix.Color(0, 255, 0),
    matrix.Color(0, 255, 0),
    matrix.Color(255, 255, 0),
    matrix.Color(255, 255, 0)
};

const uint32_t ball_color = matrix.Color(255, 255, 255);
const uint32_t pad_color = matrix.Color(0, 0, 255);

const int pad_size = 3;
int pospad = 0;

bool bricks_map[coloums][rows];

bool rotation_clockvise = true;

bool move_done;

extern int posx, posy;
extern bool run;
extern bool gameover;
extern char keychar;
extern int dir;
extern int speed;

const int bounce_vertical[] = {3, 2, 1, 0};
const int bounce_horisontal[] = {1, 0, 3, 2};
const int bounce_corner[] = {2, 3, 0, 1};

bool check_move(int nextX, int nextY)
{
    if(!(0 <= nextX && nextX < mapx))
    {
        dir = bounce_vertical[dir];
    }
    else if(!(0 <= nextY))
    {
        dir = bounce_horisontal[dir];
    }
    else if(nextY < rows)
    {
        if(!bricks_map[nextX / 2][posy] && !bricks_map[posx / 2][nextY])
        {
            dir = bounce_corner[dir];
            bricks_map[nextX / 2][posy] = true;
            bricks_map[posx / 2][nextY] = true;
        }
        else if(!bricks_map[nextX / 2][posy])
        {
            dir = bounce_vertical[dir];
            bricks_map[nextX / 2][posy] = true;
        }
        else if(!bricks_map[posx / 2][nextY])
        {
            dir = bounce_horisontal[dir];
            bricks_map[posx / 2][nextY] = true;
        }
        else if(!bricks_map[nextX / 2][nextY])
        {
            dir = bounce_corner[dir];
            bricks_map[nextX / 2][nextY] = true;
        }
        else return true;
    }
    else if(nextY >= mapy -1)
    {
        if(pospad <= posx && posx < pospad + pad_size)
        {
            switch(posx - pospad)
            {
                case 0: dir = 3; break;
                case 1: dir = bounce_vertical[dir]; break;
                case 2: dir = 0; break;
            }
        }
        else
        {
            gameover = true;
            run = false;
        }
    }
    else return true;
    return false;
}

void input()
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
    if(timeout_b != 0) timeout_b--;
    
    //return keychar;
}

void Breakout_game()
{
    run = true;
    gameover = false;
    memset(bricks_map, 0, sizeof(bricks_map));
    
    posx = 0;
    posy = mapy -2;
    dir = 0;
    speed = 25;

    while(run)
    {
        matrix.clear();
        for (size_t cy = 0; cy < rows; cy++)
            for (size_t cx = 0; cx < coloums; cx++)
                if(!bricks_map[cx][cy]) 
                {
                    matrix.drawPixel(cx * 2, cy, row_colors[cy]);
                    matrix.drawPixel(cx * 2 + 1, cy, row_colors[cy]);
                }

        matrix.drawLine(pospad, mapy -1, pospad + pad_size -1, mapy-1, pad_color);

        matrix.drawPixel(posx, posy, ball_color);
        matrix.show();

        for (size_t i = 0; i < speed; i++)
        {
            input();
            switch (keychar)
            {
                case 'd': if(pospad + pad_size < mapx) pospad++; break;
                case 'a': if(pospad > 0) pospad--; break;
                case 'e': run = false;
            }
            matrix.drawLine(0, mapy -1, mapx -1, mapy-1, 0);
            matrix.drawLine(pospad, mapy -1, pospad + pad_size -1, mapy-1, pad_color);
            matrix.show();
            delay(input_update);
        }


        move_done = false;
        while(!move_done && run)
        {
            Serial.println(dir);
            Serial.print(run);
            switch (dir)
            {
            case 0:
                if(check_move(posx + 1, posy - 1))
                {
                    posx++;
                    posy--;
                    move_done = true;
                }
                break;

            case 1:
                if(check_move(posx + 1, posy + 1))
                {
                    posx++;
                    posy++;
                    move_done = true;
                }
                break;

            case 2:
                if(check_move(posx - 1, posy + 1))
                {
                    posx--;
                    posy++;
                    move_done = true;
                }
                break;

            case 3:
                if(check_move(posx - 1, posy - 1))
                {
                    posx--;
                    posy--;
                    move_done = true;
                }
                break;
            }
            
            keychar = NULL;
        }
    }
}