#include "matrix_boy_IO.h"

const int rows = 8;
const int coloums = mapx / 2;
const int pad_size = 3;

const uint32_t ball_color = matrix.Color(255, 255, 255);
const uint32_t pad_color = matrix.Color(0, 0, 255);
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

const int bounce_vertical[] = {3, 2, 1, 0};
const int bounce_horisontal[] = {1, 0, 3, 2};
const int bounce_corner[] = {2, 3, 0, 1};

int pad_pos = 0;

bool bricks_map[coloums][rows];
bool move_done;

extern int posx, posy, dir, speed;
extern bool run, gameover, win;

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
        if(pad_pos <= posx && posx < pad_pos + pad_size)
        {
            if(posx - pad_pos == 0) dir = 3;
            else if(posx - pad_pos == pad_size - 1) dir = 0;
            else dir = bounce_horisontal[dir];
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

void Breakout_game()
{
    run = true;
    gameover = false;
    memset(bricks_map, 0, sizeof(bricks_map));
    
    posx = random(mapx);
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

        matrix.drawLine(pad_pos, mapy -1, pad_pos + pad_size -1, mapy-1, pad_color);

        matrix.drawPixel(posx, posy, ball_color);
        matrix.show();

        for (size_t i = 0; i < speed; i++)
        {
            Input();
            switch (keychar)
            {
                case 'd': if(pad_pos + pad_size < mapx) pad_pos++; break;
                case 'a': if(pad_pos > 0) pad_pos--; break;
                case 'e': run = false;
            }
            matrix.drawLine(0, mapy -1, mapx -1, mapy-1, 0);
            matrix.drawLine(pad_pos, mapy -1, pad_pos + pad_size -1, mapy-1, pad_color);
            matrix.show();
            delay(input_update);
        }


        move_done = false;
        while(!move_done && run)
        {
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
        }
    }
}

int enemy_pos;
const int enemy_size = 3;
const uint32_t enemy_color = matrix.Color(0, 0, 255);

bool check_pong_move(int nextX, int nextY)
{
    if(!(0 <= nextX && nextX < mapx))
    {
        dir = bounce_vertical[dir];
    }
    else if(!(1 <= nextY))
    {
        if(enemy_pos <= posx && posx < enemy_pos + enemy_size)
        {
            if(posx - pad_pos == 0) dir = 2;
            else if(posx - pad_pos == pad_size - 1) dir = 1;
            else dir = bounce_horisontal[dir];
        }
        else
        {
            win = true;
            run = false;
        }
    }
    else if(nextY >= mapy -1)
    {
        if(pad_pos <= posx && posx < pad_pos + pad_size)
        {
            if(posx - pad_pos == 0) dir = 3;
            else if(posx - pad_pos == pad_size - 1) dir = 0;
            else dir = bounce_horisontal[dir];
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

void Pong_game()
{
    run = true;
    gameover = false;
    
    posx = random(mapx);
    posy = mapy -2;
    dir = 0;
    speed = 25;

    while(run)
    {
        matrix.clear();
        matrix.drawLine(pad_pos, mapy -1, pad_pos + pad_size -1, mapy-1, pad_color);
        matrix.drawLine(enemy_pos, 0, enemy_pos + enemy_size -1, 0, enemy_color);

        matrix.drawPixel(posx, posy, ball_color);
        matrix.show();

        for (size_t i = 0; i < speed; i++)
        {
            Input();
            switch (keychar)
            {
                case 'd': if(pad_pos + pad_size < mapx) pad_pos++; break;
                case 'a': if(pad_pos > 0) pad_pos--; break;
                case 'e': run = false;
            }
            matrix.drawLine(0, mapy -1, mapx -1, mapy-1, 0);
            matrix.drawLine(pad_pos, mapy -1, pad_pos + pad_size -1, mapy-1, pad_color);
            matrix.show();
            delay(input_update);
        }


        move_done = false;
        while(!move_done && run)
        {
            switch (dir)
            {
                case 0:
                    if(check_pong_move(posx + 1, posy - 1))
                    {
                        posx++;
                        posy--;
                        move_done = true;
                    }
                    break;

                case 1:
                    if(check_pong_move(posx + 1, posy + 1))
                    {
                        posx++;
                        posy++;
                        move_done = true;
                    }
                    break;

                case 2:
                    if(check_pong_move(posx - 1, posy + 1))
                    {
                        posx--;
                        posy++;
                        move_done = true;
                    }
                    break;

                case 3:
                    if(check_pong_move(posx - 1, posy - 1))
                    {
                        posx--;
                        posy--;
                        move_done = true;
                    }
                    break;
            }
        }

        if(dir == 0 || dir == 3)
        {
            enemy_pos = max(0, min(mapx - enemy_size, posx - 1));
        }

        switch(random(0, 10))
        {  
            case 0:
            break;

            default:
            break;
        }
    }
}
