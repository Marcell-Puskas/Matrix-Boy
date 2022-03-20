#ifndef PAINT_H 
#define PAINT_H 

#include "matrix_boy_IO.h"

class Paint {
    private:
    int map[mapx][mapy];
    int posx, posy;
    bool run = true;
    bool brush = false;
    int selected_color = 1;
    bool selecting_menu = false;

    bool cursor_blink = false;
    long last_blink = 0;
    int blink_dur = 200;

    static const int colornum = 8;
    uint32_t colors[colornum] = {
        0,
        matrix.Color(255, 0, 0),
        matrix.Color(255, 255, 0),
        matrix.Color(0, 255, 0),
        matrix.Color(0, 255, 255),
        matrix.Color(0, 0, 255),
        matrix.Color(255, 0, 255),
        matrix.Color(255, 255, 255)
    };
    uint32_t border_color = matrix.Color(255, 255, 255);
    uint32_t cursor_color = matrix.Color(255, 255, 255);

    public:
    void Paint_app();
};

#endif