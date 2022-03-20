#ifndef EGG_GAME_H
#define EGG_GAME_H

#include "matrix_boy_IO.h"

class Egg {
    private:
    const int egg_color_num = 5;
    const int pad_size = 3;

    const uint32_t pad_color = matrix.Color(255, 255, 255);
    const uint32_t egg_colors[6] = {
        0,
        matrix.Color(255, 0, 0),
        matrix.Color(255, 255, 0),
        matrix.Color(0, 255, 0),
        matrix.Color(0, 255, 255),
        matrix.Color(0, 0, 255),
    };

    int spawnrate, pos_pad;

    int points, speed;
    int intmap[mapx][mapy];
    bool run, gameover;

    void Egg_print();

    public:
    void Egg_game();
};

#endif