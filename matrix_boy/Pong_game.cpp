#include "ballgames.h"

bool Pong::check_pong_move(int nextX, int nextY)
{
    if(!(0 <= nextX && nextX < mapx))
    {
        dir = bounce_vertical[dir];
    }
    else if(!(1 <= nextY))
    {
        if(enemy_pos <= posx && posx < enemy_pos + enemy_size)
        {
            atack_cycle++;
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

void Pong::Pong_game()
{
    extern bool gyro_mode;
    run = true;
    gameover = false;
    
    posx = random(mapx);
    posy = mapy -2;
    dir = 0;
    speed = 25;
    atack_cycle = 0;
    required_atacks = random(2, 5);

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
        Serial.print(atack_cycle);
        Serial.print("\t");
        Serial.println(dir);
        if(dir == 0 || dir == 3 && atack_cycle < required_atacks)
        {
            enemy_pos = max(0, min(mapx - enemy_size, posx - 1));
        }
        else
        {
            enemy_pos = max(0, min(mapx - enemy_size, enemy_pos + random(-1, 1)));
        }
    }
}