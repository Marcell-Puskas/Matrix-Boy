#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

const int matrixWidth = 8;
const int matrixHeight = 8;
const int tilesX = 1;
const int tilesY = 2;
const int pin = 6;
const int matrixType = NEO_TILE_TOP;
const int ledType = NEO_GRB;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
    matrixWidth, matrixHeight, tilesX, tilesY, pin, matrixType, ledType);

#define joy_x_pin A0;
#define joy_y_pin A1;
#define joy_button_pin 9;

int joy_x = 0;
int joy_y = 0;
int joy_button = 0;
//static const 
const uint16_t snake_bmp[] PROGMEM = {
    0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0xffe0, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0xf800, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f
};

const uint16_t tetris_bmp[] PROGMEM = {
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
    0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 
    0xffff, 0x0000, 0x0000, 0x0000, 0x07ff, 0x0000, 0x0000, 0xffff, 
    0xffff, 0x0000, 0x0000, 0x0000, 0x07ff, 0x0000, 0x0000, 0xffff, 
    0xffff, 0x0000, 0x0000, 0x0000, 0x07ff, 0x0000, 0x0000, 0xffff, 
    0xffff, 0x0000, 0x0000, 0x0000, 0x07ff, 0x0000, 0x0000, 0xffff, 
    0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 
    0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 
    0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 
    0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 
    0xffff, 0xf81f, 0xf800, 0xf800, 0x0000, 0xfd40, 0x0000, 0xffff, 
    0xffff, 0xf81f, 0xf81f, 0xf800, 0xf800, 0xfd40, 0x0000, 0xffff, 
    0xffff, 0xf81f, 0x0000, 0x07e0, 0x07e0, 0xfd40, 0xfd40, 0xffff, 
    0xffff, 0x001f, 0x07e0, 0x07e0, 0x0000, 0xffe0, 0xffe0, 0xffff, 
    0xffff, 0x001f, 0x001f, 0x001f, 0x0000, 0xffe0, 0xffe0, 0xffff, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff
};

/*const String games[] = {
    "snake",
    "tetris"
};*/

const uint16_t *bmps[] = {
    snake_bmp,
    tetris_bmp
};

const int game_count = 2;
const int anim_speed = 25;
char keychar;
int selected = 0;

void call_game(int game_index) {
    switch (game_index)
    {
        case 0:
        Snake_game();
        break;
    }
}

void setup() {
    matrix.begin();
    matrix.setBrightness(1);
    Serial.begin(9600);
    Serial.println("MatrixBoy Running");
}

void loop() {
    if(Serial.available())
    {
        keychar = Serial.read();
        Serial.print("Selected: ");
        Serial.println(selected);
    }

    switch (keychar)
    {
        case 'a':
        if(selected > 0)
        {
            selected--;
            for (size_t i = 0; i < matrixWidth; i++)
            {
                matrix.drawRGBBitmap(i, 0, (bmps[selected+1]), 8, 16);
                matrix.drawRGBBitmap(-matrixWidth+i, 0, (bmps[selected]), 8, 16);
                matrix.show();
                delay(anim_speed);
            }
        }
        break;

        case 'd':
        if(selected + 1 < game_count)
        {
            selected++;
            for (size_t i = 0; i < matrixWidth; i++)
            {
                matrix.drawRGBBitmap(-i, 0, (bmps[selected-1]), 8, 16);
                matrix.drawRGBBitmap(matrixWidth-i, 0, (bmps[selected]), 8, 16);
                matrix.show();
                delay(anim_speed);
            }
        }
        break;

        case 'o':
        call_game(selected);
        break;
    }

    keychar = NULL;

    matrix.drawRGBBitmap(0, 0, (bmps[selected]), 8, 16);
    matrix.show();

    joy_x = analogRead(A0);
    joy_y = analogRead(A1);
    joy_button = digitalRead(9);

    if(joy_x > 640) keychar = 'd';
    if(joy_x < 384) keychar = 'a';
    if(joy_button == 0) keychar = 'o';

    delay(10);
}

void Snake_game()
{
    matrix.clear();

    //config
    const int mapx = 8;
    const int mapy = 16;
    int posx = random(mapx);
    int posy = random(mapy);
    int def_length = 3;
    int snakelength = 0;

    const bool screen_warp = true;

    const uint32_t color_snake = matrix.Color(0, 255, 0);
    const uint32_t color_head = matrix.Color(255, 255, 0);
    const uint32_t color_food = matrix.Color(255, 0, 0);
    const uint32_t color_background = matrix.Color(0, 0, 0);

    //create varriables
    int age_map[mapx][mapy];
    int foodx = random(mapx);
    int foody = random(mapy);
    int dir = random(4);
    int dir_input = 0;
    bool runing = true;
    bool gameover = false;
    char keyc = 'd';

    while (runing && !gameover)
    {
        //controlls
        if(Serial.available())
        {
            keyc = Serial.read();
            switch (keyc)
            {
            case 'd':
                dir_input = 0;
                break;
            case 'a':
                dir_input = 1;
                break;
            case 's':
                dir_input = 2;
                break;
            case 'w':
                dir_input = 3;
                break;
            }
        }

        switch (dir_input)
        {
            case 0:
                if (dir != 1) dir = 0;
                break;

            case 1:
                if (dir != 0) dir = 1;
                break;

            case 2:
                if (dir != 3) dir = 2;
                break;

            case 3:
                if (dir != 2) dir = 3;
                break;
        }

        if(screen_warp)
        {
            switch (dir)
            {
                case 0:
                    if (posx + 1 >= mapx) posx = 0;
                    else posx++;
                    break;
                case 1:
                    if (posx <= 0) posx = mapx - 1;
                    else posx--;
                    break;
                case 2:
                    if (posy + 1 >= mapy) posy = 0;
                    else posy++;
                    break;
                case 3:
                    if (posy <= 0) posy = mapy - 1;
                    else posy--;
                    break;
            }
        }
        else
        {
            switch (dir)
            {
                case 0:
                    if (posx + 1 >= mapx) gameover = true;
                    else posx++;
                    break;
                case 1:
                    if (posx <= 0) gameover = true;
                    else posx--;
                    break;
                case 2:
                    if (posy + 1 >= mapy) gameover = true;
                    else posy++;
                    break;
                case 3:
                    if (posy <= 0) gameover = true;
                    else posy--;
                    break;
            }
        }

        if (age_map[posx][posy] > 0)
        {
            runing = false;
            gameover = true;
        }

        age_map[posx][posy] = 1;

        if (posx == foodx && posy == foody)
        {
            while (age_map[foodx][foody] != 0)
            {
                foodx = random(mapx);
                foody = random(mapy);
            }
            snakelength++;
        }

        for (size_t cy = 0; cy < mapy; cy++)
        {
            for (size_t cx = 0; cx < mapx; cx++)
            {
                if (age_map[cx][cy] > 0)
                {
                    if(cx == posx && cy == posy) 
                        matrix.drawPixel(cx, cy, color_head);
                    else
                        matrix.drawPixel(cx, cy, color_snake);
                    
                    age_map[cx][cy]++;

                    if (age_map[cx][cy] > snakelength + def_length)
                    {
                        age_map[cx][cy] = 0;
                    }
                }
                else if (cx == foodx && cy == foody)
                {
                    matrix.drawPixel(cx, cy, color_food);
                }
                else
                {
                    matrix.drawPixel(cx, cy, color_background);
                }
            }
        }
        matrix.show();
        Serial.print("Score: ");
        Serial.print(snakelength);
        Serial.print(" Direction: ");
        Serial.print(dir);
        Serial.print(" X: ");
        Serial.print(joy_x);
        Serial.print(" Y: ");
        Serial.print(joy_y);
        Serial.print(" btn: ");
        Serial.println(joy_button);

        for (size_t i = 0; i < 20 + 50 / (snakelength + 1); i++)
        {
            joy_x = analogRead(A0);
            joy_y = analogRead(A1);
            joy_button = digitalRead(9);

            if(joy_x > 640) dir_input = 0;
            if(joy_x < 384) dir_input = 1;
            if(joy_y > 640) dir_input = 2;
            if(joy_y < 384) dir_input = 3;

            if(joy_button == 0)
            {
                for (size_t i = 0; i < 200 && joy_button == 0; i++)
                {
                    joy_button = digitalRead(9);
                    delay(10);
                }
                if(joy_button == 0) runing = false;
            }
            delay(10);
        }
    }

    if (gameover)
    {
        Serial.print("Game over, Score: ");
        Serial.println(snakelength);
        matrix.setCursor(0, 0);
        matrix.clear();
        matrix.print(snakelength);
        matrix.show();
        delay(2000);
    }
}