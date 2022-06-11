#include "ballgames.h"

void Breakout::hit_log(byte moveX, byte moveY, byte f = 0)
{
    if(testmode)
    {
        Serial.print("dir: ");
        Serial.print(dir);
        Serial.print("  posx: ");
        Serial.print(posx);
        Serial.print("  posy: ");
        Serial.print(posy);
        Serial.print("  moveX: ");
        Serial.print(moveX);
        Serial.print("  moveY: ");
        Serial.print(moveY);
        Serial.print("  function number: ");
        Serial.print(f);
        Serial.print("  hits: ");
        Serial.println(hits);

        print();

        while (keychar != 'e')
        {
            delay(10);
            Input();
        }
    }
    
}

bool Breakout::check_move(byte nextX, byte nextY)
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
        
        if(!bricks_map[nextX / 2][posy] && !bricks_map[posx / 2][nextY] && nextY < rows - 1)
        {
            dir = bounce_corner[dir];
            bricks_map[nextX / 2][posy] = true;
            bricks_map[posx / 2][nextY] = true;
            hits += 2;
            hit_log(nextX, nextY, 1);
        }
        else if(!bricks_map[nextX / 2][posy] && nextY < rows - 1)
        {
            dir = bounce_vertical[dir];
            bricks_map[nextX / 2][posy] = true;
            hits++;
            hit_log(nextX, nextY, 2);
        }
    
        else if(!bricks_map[posx / 2][nextY])
        {
            dir = bounce_horisontal[dir];
            bricks_map[posx / 2][nextY] = true;
            hits++;
            hit_log(nextX, nextY, 3);
        }
        else if(!bricks_map[nextX / 2][nextY])
        {
            dir = bounce_corner[dir];
            bricks_map[nextX / 2][nextY] = true;
            hits++;
            hit_log(nextX, nextY, 4);
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

void Breakout::print()
{
    matrix.clear();
        for (size_t cy = 0; cy < rows; cy++)
            for (size_t cx = 0; cx < coloums; cx++)
                if(!bricks_map[cx][cy]) 
                {
                    matrix.drawPixel(cx * 2, cy, row_colors[cy]);
                    matrix.drawPixel(cx * 2 + 1, cy, row_colors[cy]);
                }

        matrix.drawFastHLine(pad_pos, mapy -1, pad_size, pad_color);

        matrix.drawPixel(posx, posy, ball_color);
        matrix.show();
}

void Breakout::Breakout_game()
{
    extern bool gyro_mode;
    run = true;
    gameover = false;
    win = false;
    memset(bricks_map, 0, sizeof(bricks_map));
    
    posx = random(mapx);
    posy = mapy -2;
    dir = 0;
    speed = 25;

    hits = 0;

    while(run)
    {
        print();

        for (size_t i = 0; i < 5 + (all_bricks - hits); i++)
        {
            Input();
            switch (keychar)
            {
                case 'd': if(pad_pos + pad_size < mapx) pad_pos++; break;
                case 'a': if(pad_pos > 0) pad_pos--; break;
                case 'e': run = false;
                case 't': testmode = !testmode;
            }
            if(gyro_mode) pad_pos = gyro_xmove(0, mapx - pad_size);
            
            matrix.drawFastHLine(0, mapy -1, mapx, 0);
            matrix.drawFastHLine(pad_pos, mapy -1, pad_size, pad_color);
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
        if(hits >= all_bricks) 
        {
            run = false;
            win = true;
        }
    }

    matrix.clear();
    matrix.setCursor(0, 0);
    if(win)
    {
        matrix.print("W");
        matrix.show();
        delay(score_time);
    }
    else if(gameover)
    {
        matrix.print(hits);
        matrix.show();
        delay(score_time);
    }
}