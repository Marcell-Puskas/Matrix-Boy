#ifndef MENU_H
#define MENU_H

#include "matrix_boy_IO.h"

class Menu
{
private:
    const byte anim_speed = 25;

    byte selected_game = 0;

    byte xcenter;
    byte ycenter;
    //bool run = true;
public:
    byte menu(
        const byte app_count, 
        const byte iwidth, 
        const byte iheight,
        const uint16_t *icons[]
    );
};


#endif