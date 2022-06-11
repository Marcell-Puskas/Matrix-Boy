#include "Tetris_game.h"

void Tetris::Construct_tetro(byte cdir, bool select = false) {
    for (byte cmino = 0; cmino < mino_num; cmino++)
    {
        switch (cdir)
        {
            case 0:
            construncted_tetro[cmino][0] = tetro_cordinates[selected_index][cmino][0];
            construncted_tetro[cmino][1] = tetro_cordinates[selected_index][cmino][1];
            break;

            case 1:
            construncted_tetro[cmino][0] = tetro_offsets[selected_index][0] - tetro_cordinates[selected_index][cmino][1];
            construncted_tetro[cmino][1] = tetro_cordinates[selected_index][cmino][0];
            break;

            case 2:
            construncted_tetro[cmino][0] = tetro_offsets[selected_index][0] - tetro_cordinates[selected_index][cmino][0];
            construncted_tetro[cmino][1] = tetro_offsets[selected_index][1] - tetro_cordinates[selected_index][cmino][1];
            break;

            case 3:
            construncted_tetro[cmino][0] = tetro_cordinates[selected_index][cmino][1];
            construncted_tetro[cmino][1] = tetro_offsets[selected_index][1] - tetro_cordinates[selected_index][cmino][0];
            break;
        }
    }
    if(select)
    {
        for (byte cmino = 0; cmino < mino_num; cmino++)
        {
            selected_tetro[cmino][0] = construncted_tetro[cmino][0];
            selected_tetro[cmino][1] = construncted_tetro[cmino][1];
        }
    }
}

void Tetris::New_tetro()
{
    dir = 0;
    selected_index = random(tetro_num);
    Construct_tetro(dir, true);

    posx = mapx / 2 - tetro_offsets[selected_index][0] / 2;
    if(tetro_offsets[selected_index][1] == 3) posy = -1;
    else posy = 0;
}

void Tetris::Tetris_print()
{
    //draw stack
    for (byte cy = 0; cy < mapy; cy++)
    {
        for (byte cx = 0; cx < mapx; cx++)
        {
            if(map[cx][cy] != -1)
                matrix.drawPixel(cx, cy, (tetro_colors[map[cx][cy]]) );
            else
                matrix.drawPixel(cx, cy, background_color);
        }
    }

    //draw current block
    for (size_t cmino = 0; cmino < mino_num; cmino++)
    {
        matrix.drawPixel(
            posx + selected_tetro[cmino][0],
            posy + selected_tetro[cmino][1],
            tetro_colors[selected_index]);
    }

    matrix.show();
}

bool Tetris::check_move(int8_t nextX, int8_t nextY, byte nextDir)
{
    Construct_tetro(nextDir);
    for(byte cmino = 0; cmino < mino_num; cmino++)
    {
        if(nextX + construncted_tetro[cmino][0] >= mapx) return false;
        if(nextX + construncted_tetro[cmino][0] < 0) return false;
        if(nextY + construncted_tetro[cmino][1] >= mapy) return false;
        if(nextY + construncted_tetro[cmino][1] < 0) return false;

        if(map[ nextX + construncted_tetro[cmino][0] ][ nextY + construncted_tetro[cmino][1] ] != -1)
            return false;
    }
    return true;
}

void Tetris::Update_input()
{
    extern bool gyro_mode;
    for (size_t t = 0; t < speed && run; t++)
    {
        Input();
        
        switch(keychar)
        {
            case 'a': if(check_move(posx - 1, posy, dir)) posx--; break;
            case 'd': if(check_move(posx + 1, posy, dir)) posx++; break;
            case 's': if(check_move(posx, posy + 1, dir)) posy++; break;

            case 'w':
            if(check_move(posx, posy, (dir + 1) % 4))
            {
                dir = (dir + 1) % 4;
                Construct_tetro(dir, true);
            }
            break;

            case 'e': run = false; break;
        }
        if(gyro_mode)
        {
            int8_t gyx = gyro_xmove(-2, mapx);
            if(check_move(gyx, posy, dir)) posx = gyx;

            gyro_down_speed = 1000 - gyro_ymove(20, 1000);
            if(gyro_down_timeout + gyro_down_speed < millis())
            {
                gyro_down_timeout = millis();
                if(check_move(posx, posy + 1, dir)) posy++;
            }
        }
        

        Tetris_print();

        delay(input_update);
    }
}

void Tetris::Check_full_line()
{
    bool lines_to_clear = false;
    for (size_t cline = 0; cline < mapy; cline++)
    {
        bool line_full = true;
        for (size_t crow = 0; crow < mapx; crow++)
            if(map[crow][cline] == -1)
                line_full = false;
        
        if(line_full)
        {
            matrix.drawFastHLine(0, cline, mapx, full_line_color);
            
            lines_to_clear = true;
            points++;
            speed = 10 + 40 / points;

            for (size_t copyy = cline; copyy >= 1; copyy--)
                    for (size_t copyx = 0; copyx < mapx; copyx++)
                        map[copyx][copyy] = map[copyx][copyy - 1];
        }
    }

    if(lines_to_clear)
    {
        matrix.show();
        delay(clear_time);
    }
}

void Tetris::Check_gameover()
{
    if (!check_move(posx, posy, dir))
    {
        gameover = true;
        run = false;
    }
}

void Tetris::Logic()
{
    if(check_move(posx, posy + 1, dir))
    {
        posy += 1;
    }
    else
    {
        for(byte cmino = 0; cmino < mino_num; cmino++)
        {
            map[ posx + selected_tetro[cmino][0] ][ posy + selected_tetro[cmino][1] ] = selected_index;
        }
        Check_full_line();
        New_tetro();
        Check_gameover();
    }

    Tetris_print();
}

void Tetris::Tetris_game()
{
    matrix.clear();

    up_timeout = 140;
    down_timeout = 30;

    points = 0;
    speed = 50;
    run = true;
    gameover = false;
    memset(map, -1, sizeof(map));

    New_tetro();
    
    while(run)
    {
        Update_input();
        Logic();
    }

    if(gameover)
    {
        matrix.clear();
        matrix.setCursor(0, 0);
        matrix.print(points);
        matrix.show();
        delay(score_time);
    }
}