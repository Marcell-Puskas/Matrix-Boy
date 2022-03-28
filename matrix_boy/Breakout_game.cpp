#include "ballgames.h"

bool Breakout::check_move(int nextX, int nextY)
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

void Breakout::Breakout_game()
{
    extern bool gyro_mode;
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
            if(gyro_mode) pad_pos = gyro_xmove(mapx - pad_size);
            
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