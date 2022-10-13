#include "menu.h"

int8_t Menu::menu(const byte app_count, const byte iwidth, const byte iheight, const uint16_t *icons[]) {
    xcenter = mapx / 2 - iwidth / 2;
    ycenter = mapy / 2 - iheight / 2;

    input_code[9] = '\0';

    keychar = 'n';

    while (true)
    {
        if(keychar != last_key && keychar != 'n')
        {
            for (size_t i = sizeof(input_code) - 2; i > 0; i--)
            {
                input_code[i] = input_code[i - 1];
            }
            input_code[0] = keychar;

            Serial.println();
            for (size_t i = 0; i < sizeof(input_code); i++)
            {
                Serial.print(input_code[i]);
            }
            
            if(strcmp(input_code, secret_code) == 0)
            {
                Serial.println("secret code enterd!"); 
                return -2;
            }
        }
        last_key = keychar;
        
        switch (keychar)
        {
            case 'a':
            selected_game = (selected_game - 1 + app_count) % app_count;
            for (size_t i = 0; i < mapx; i++)
            {
                matrix.clear();
                matrix.drawRGBBitmap(xcenter + i, ycenter, (icons[ (selected_game + 1 + app_count) % app_count ]), iwidth, iheight);
                matrix.drawRGBBitmap(xcenter - mapx + i, ycenter, (icons[selected_game]), iwidth, iheight);
                matrix.show();
                delay(anim_speed);
            }
            break;

            case 'd':
            selected_game = (selected_game + 1 + app_count) % app_count;
            for (size_t i = 0; i < mapx; i++)
            {
                matrix.clear();
                matrix.drawRGBBitmap(xcenter - i, ycenter, (icons[ (selected_game - 1 + app_count) % app_count ]), iwidth, iheight);
                matrix.drawRGBBitmap(xcenter + mapx - i, ycenter, (icons[selected_game]), iwidth, iheight);
                matrix.show();
                delay(anim_speed);
            }
            break;

            case 'o':
            keychar = 'n';
            //run = false;
            return selected_game;
            break;

            case 'e':
            return -1;
            break;
        }

        matrix.clear();
        matrix.drawRGBBitmap(xcenter, ycenter, (icons[selected_game]), iwidth, iheight);
        matrix.show();

        pause_menu = false;
        Input(true);

        delay(input_update);
    }
}