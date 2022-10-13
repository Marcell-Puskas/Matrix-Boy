#ifndef MENU_H
#define MENU_H

#include "matrix_boy_IO.h"

class Menu
{
private:
    const byte anim_speed = 25;

    int8_t selected_game = 0;

    byte xcenter;
    byte ycenter;

    const char secret_code[10] = "odadassww";//"ondnandnansnsnwnwn";  //wwssadado    
                                //odadassww
    char last_key;                  
    char input_code[10];
public:
    int8_t menu(
        const byte app_count, 
        const byte iwidth, 
        const byte iheight,
        const uint16_t *icons[]
    );
};


#endif