#ifndef BALLGAME_H
#define BALLGAME_H

#include "matrix_boy_IO.h"

class Ballgames {
    protected:
    const byte pad_size = 3;

    const uint16_t ball_color = matrix.Color(255, 255, 255);
    const uint16_t pad_color = matrix.Color(0, 0, 255);
    

    const byte bounce_vertical[4] = {3, 2, 1, 0};
    const byte bounce_horisontal[4] = {1, 0, 3, 2};
    const byte bounce_corner[4] = {2, 3, 0, 1};

    byte pad_pos = 0;

    bool move_done;

    byte posx, posy, dir, speed;
    bool run, gameover, win;

};

class Breakout: public Ballgames {
    private:
    static const byte rows = 8;
    static const byte coloums = mapx / 2;

    const byte all_bricks = rows * coloums;

    const uint16_t row_colors[8] = {
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
    
    bool check_move(byte nextX, byte nextY);
    void hit_log(byte nextX, byte nextY, byte f);
    void print();

    bool testmode = false;
    bool win = false;

    byte hits;

    public:
    void Breakout_game();
};

class Pong: public Ballgames {
    private:
    byte enemy_pos;
    const byte enemy_size = 3;
    const uint16_t enemy_color = matrix.Color(0, 0, 255);
    uint16_t atack_cycle;
    byte required_atacks;

    bool check_pong_move(byte nextX, byte nextY);

    public:
    void Pong_game();
};

#endif