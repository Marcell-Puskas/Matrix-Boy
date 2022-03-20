#include "Paint.h"

void Paint::Paint_app() {
    pause_menu = false;
    memset(map, -1, sizeof(map));

    while (run)
    {
        matrix.clear();
        for (size_t cy = 0; cy < mapy; cy++)
        {
            for (size_t cx = 0; cx < mapx; cx++)
            {
                matrix.drawPixel(cx, cy, colors[ map[cx][cy] ]);
            }
        }
        if(last_blink + blink_dur < millis())
        {
            last_blink = millis();
            cursor_blink = !cursor_blink;
        }
        if(cursor_blink) matrix.drawPixel(posx, posy, cursor_color);
        else matrix.drawPixel(posx, posy, 0);
        matrix.show();

        Input();
        switch (keychar)
        {
            case 'd': if(posx < mapx - 1) posx++; break;
            case 'a': if(posx > 0) posx--; break;
            case 's': if(posy < mapy - 1) posy++; break;
            case 'w': if(posy > 0) posy--; break;
            case 'o': brush = true; break;
            case 'e': selecting_menu = true; break;
        }

        while (selecting_menu)
        {
            matrix.clear();
            for (size_t cc = 0; cc < colornum; cc++)
            {
                matrix.drawRect(1, 1 + cc * 2, mapx - 2, 1, colors[cc]);
            }
            matrix.drawRect(0, selected_color * 2, mapx, 3, border_color);
            matrix.show();
            
            Input();
            switch (keychar)
            {
                case 's': if(selected_color < colornum - 1) selected_color++; break;
                case 'w': if(selected_color > 0) selected_color--; break;
                case 'o': selecting_menu = false; break;
                case 'e': selecting_menu = false; run = false; break;
            }
        }
        

        if (brush)
        {
            map[posx][posy] = selected_color;
            brush = false;
        }
        
    }
    
}