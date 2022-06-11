#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "matrix_boy_IO.h"

class Tetris {
private:
    const int tetro_num = 7;
    const int mino_num = 4;
    const int clear_time = 400;

    const int tetro_cordinates[7][4][2] = {
        {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
        {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
        {{2, 0}, {0, 1}, {1, 1}, {2, 1}},
        {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
        {{1, 0}, {2, 0}, {0, 1}, {1, 1}},
        {{1, 0}, {0, 1}, {1, 1}, {2, 1}},
        {{0, 0}, {1, 0}, {1, 1}, {2, 1}}
    };

    const int tetro_offsets[7][2] = {
        {3, 3},
        {2, 2},
        {2, 2},
        {1, 1},
        {2, 2},
        {2, 2},
        {2, 2}
    };

    const uint32_t tetro_colors[7] = {
        matrix.Color(0, 255, 255),
        matrix.Color(0, 0, 255),
        matrix.Color(255, 170, 0),
        matrix.Color(255, 255, 0),
        matrix.Color(0, 255, 0),
        matrix.Color(255, 0, 255),
        matrix.Color(255, 0, 0)
    };

    const uint32_t background_color = matrix.Color(0, 0, 0);
    const uint32_t full_line_color = matrix.Color(255, 255, 255);

    int posx, posy, dir, selected_index, points, speed;
    bool run, gameover;

    long gyro_down_timeout = 0;
    long gyro_down_speed = 30;

    int selected_tetro[4][2];
    int construncted_tetro[4][2];
    int intmap[mapx][mapy];

    void Construct_tetro(int cdir, bool select);
    void New_tetro();
    void Tetris_print();
    bool check_move(int nextX, int nextY, int nextDir);
    void Update_input();
    void Check_full_line();
    void Check_gameover();
    void Logic();
public:
    void Tetris_game();
};

#endif