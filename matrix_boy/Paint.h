#ifndef PAINT_H 
#define PAINT_H 

#include "matrix_boy_IO.h"

class Paint {
    private:
    byte map[mapx][mapy];
    byte posx = 0; 
    byte posy = 0;
    bool run = true;
    bool brush = false;
    byte selected_color = 0;
    bool selecting_menu = false;

    bool cursor_blink = false;
    long last_blink = 0;
    byte blink_dur = 200;

    static const byte colornum = 8;
    uint16_t colors[colornum] = {
        matrix.Color(255, 0, 0),
        matrix.Color(255, 255, 0),
        matrix.Color(0, 255, 0),
        matrix.Color(0, 255, 255),
        matrix.Color(0, 0, 255),
        matrix.Color(255, 0, 255),
        matrix.Color(255, 255, 255),
        0
    };
    uint16_t border_color = matrix.Color(255, 255, 255);
    uint16_t cursor_color = matrix.Color(255, 255, 255);

    void print();

    public:
    void Paint_app();
};

#endif