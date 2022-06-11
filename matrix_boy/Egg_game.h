#ifndef EGG_GAME_H
#define EGG_GAME_H

#include "matrix_boy_IO.h"

class Egg {
    private:
    const byte egg_color_num = 5;
    const byte pad_size = 3;

    const uint16_t pad_color = matrix.Color(255, 255, 255);
    const uint16_t egg_colors[6] = {
        0,
        matrix.Color(255, 0, 0),
        matrix.Color(255, 255, 0),
        matrix.Color(0, 255, 0),
        matrix.Color(0, 255, 255),
        matrix.Color(0, 0, 255),
    };

    byte spawnrate, pos_pad;

    byte points, speed;
    int map[mapx][mapy];
    bool run, gameover;

    void Egg_print();

    public:
    void Egg_game();
};

#endif