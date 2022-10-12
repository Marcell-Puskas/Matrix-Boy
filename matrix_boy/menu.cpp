#include "menu.h"

byte Menu::menu(const byte app_count, const byte iwidth, const byte iheight, const uint16_t *icons[]) {
    xcenter = mapx / 2 - iwidth / 2;
    ycenter = mapy / 2 - iheight / 2;

    while (true)
    {
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
            //run = false;
            return selected_game;
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