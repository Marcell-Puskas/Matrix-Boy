#ifndef BALLGAME_H
#define BALLGAME_H

#include "matrix_boy_IO.h"

class Ballgames {
    protected:
    const int pad_size = 3;

    const uint32_t ball_color = matrix.Color(255, 255, 255);
    const uint32_t pad_color = matrix.Color(0, 0, 255);
    

    const int bounce_vertical[4] = {3, 2, 1, 0};
    const int bounce_horisontal[4] = {1, 0, 3, 2};
    const int bounce_corner[4] = {2, 3, 0, 1};

    int pad_pos = 0;

    bool move_done;

    int posx, posy, dir, speed;
    bool run, gameover, win;

};

class Breakout: public Ballgames {
    private:
    static const int rows = 8;
    static const int coloums = mapx / 2;

    const int all_bricks = rows * coloums;

    const uint32_t row_colors[8] = {
        matrix.Color(255, 0, 0),
        matrix.Color(255, 0, 0),
        matrix.Color(255, 170, 0),
        matrix.Color(255, 170, 0),
        matrix.Color(0, 255, 0),
        matrix.Color(0, 255, 0),
        matrix.Color(255, 255, 0),
        matrix.Color(255, 255, 0)
    };

    bool bricks_map[coloums][rows];
    
    bool check_move(int nextX, int nextY);
    void hit_log(int nextX, int nextY, int f);
    void print();

    bool testmode = false;
    bool win = false;

    int hits;

    public:
    void Breakout_game();
};

class Pong: public Ballgames {
    private:
    int enemy_pos;
    const int enemy_size = 3;
    const uint32_t enemy_color = matrix.Color(0, 0, 255);
    int atack_cycle;
    int required_atacks;

    bool check_pong_move(int nextX, int nextY);

    public:
    void Pong_game();
};

#endif