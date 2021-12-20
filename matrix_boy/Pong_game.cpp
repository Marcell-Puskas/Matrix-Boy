/* #include "matrix_boy_IO.h"

const int pad_size = 3;

const uint32_t ball_color = matrix.Color(255, 255, 255);
const uint32_t pad_color = matrix.Color(0, 0, 255);

const int bounce_vertical[] = {3, 2, 1, 0};
const int bounce_horisontal[] = {1, 0, 3, 2};
const int bounce_corner[] = {2, 3, 0, 1};

int pospad = 0;

bool move_done;

extern int posx, posy, dir, speed;
extern bool run, gameover;

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
    else if(nextY >= mapy -1)
    {
        if(pospad <= posx && posx < pospad + pad_size)
        {
            switch(posx - pospad)
            {
                case 0: dir = 3; break;
                case 1: dir = bounce_horisontal[dir]; break;
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
*/
//void Pong_game(){}
/*
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
        matrix.drawLine(pospad, mapy -1, pospad + pad_size -1, mapy-1, pad_color);

        matrix.drawPixel(posx, posy, ball_color);
        matrix.show();

        for (size_t i = 0; i < speed; i++)
        {
            Input();
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
 */
