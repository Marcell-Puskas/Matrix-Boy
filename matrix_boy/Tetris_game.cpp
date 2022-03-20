#include "Tetris_game.h"

void Tetris::Construct_tetro(int cdir, bool select = false) {
    for (int cmino = 0; cmino < mino_num; cmino++)
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
        for (int cmino = 0; cmino < mino_num; cmino++)
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
    for (int cy = 0; cy < mapy; cy++)
    {
        for (int cx = 0; cx < mapx; cx++)
        {
            if(intmap[cx][cy] != -1)
                matrix.drawPixel(cx, cy, (tetro_colors[intmap[cx][cy]]) );
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

bool Tetris::check_move(int nextX, int nextY, int nextDir)
{
    Construct_tetro(nextDir);
    for(int cmino = 0; cmino < mino_num; cmino++)
    {
        if(nextX + construncted_tetro[cmino][0] >= mapx) return false;
        if(nextX + construncted_tetro[cmino][0] < 0) return false;
        if(nextY + construncted_tetro[cmino][1] >= mapy) return false;
        if(nextY + construncted_tetro[cmino][1] < 0) return false;

        if(intmap[ nextX + construncted_tetro[cmino][0] ][ nextY + construncted_tetro[cmino][1] ] != -1)
            return false;
    }
    return true;
}

void Tetris::Update_input()
{
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
            if(intmap[crow][cline] == -1)
                line_full = false;
        
        if(line_full)
        {
            matrix.drawLine(0, cline, mapx - 1, cline, full_line_color);
            
            lines_to_clear = true;
            points++;
            speed = 10 + 40 / points;

            for (size_t copyy = cline; copyy >= 1; copyy--)
                    for (size_t copyx = 0; copyx < mapx; copyx++)
                        intmap[copyx][copyy] = intmap[copyx][copyy - 1];
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
        for(int cmino = 0; cmino < mino_num; cmino++)
        {
            intmap[ posx + selected_tetro[cmino][0] ][ posy + selected_tetro[cmino][1] ] = selected_index;
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

    up_timeout = 14;
    down_timeout = 3;

    points = 0;
    speed = 50;
    run = true;
    gameover = false;
    memset(intmap, -1, sizeof(intmap));

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