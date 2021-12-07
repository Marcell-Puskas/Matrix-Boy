#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include "matrix_boy_IO.h"
#include "matrix_boy_image_bmps.h"
#include "Snake_game.h"
#include "Tetris_game.h"
#include "Breakout_game.h"
#include "Egg_game.h"
#include "Brightness_selector.h"

const int matrixWidth = 8;
const int matrixHeight = 8;
const int tilesX = 1;
const int tilesY = 2;
const int pin = 6;
const int matrixType = NEO_TILE_TOP;
const int ledType = NEO_GRB;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
    matrixWidth, matrixHeight, tilesX, tilesY, pin, matrixType, ledType);

//static const 
const int game_count = 6;
const int anim_speed = 25;

int bright = 2;
int selected_game = 0;

int timeout_x, timeout_y, timeout_b = 0;
int intmap[mapx][mapy];

char keychar;
int posx, posy, dir, selected_index, points, speed;
bool run, gameover;

void setup() {
    matrix.begin();
    matrix.setBrightness(bright);
    Serial.begin(9600);
    Serial.println("MatrixBoy Running");
    digitalWrite(11, HIGH);
}

void call_game(int game_index) {
    switch (game_index)
    {
        case 0:
        Snake_game();
        break;

        case 1:
        Tetris_game();
        break;

        case 2:
        Breakout_game();
        break;

        case 4:
        Egg_game();
        break;

        case 5:
        Brightness_selector();
        break;
    }
}

void loop() {
    if(Serial.available())
    {
        keychar = Serial.read();
        Serial.print("Selected: ");
        Serial.println(selected_game);
    }

    switch (keychar)
    {
        case 'a':
        selected_game = (selected_game - 1 + game_count) % game_count;
        for (size_t i = 0; i < matrixWidth; i++)
        {
            matrix.drawRGBBitmap(i, 0, (bmps[ (selected_game + 1 + game_count) % game_count ]), 8, 16);
            matrix.drawRGBBitmap(-matrixWidth+i, 0, (bmps[selected_game]), 8, 16);
            matrix.show();
            delay(anim_speed);
        }
        break;

        case 'd':
        selected_game = (selected_game + 1 + game_count) % game_count;
        for (size_t i = 0; i < matrixWidth; i++)
        {
            matrix.drawRGBBitmap(-i, 0, (bmps[ (selected_game - 1 + game_count) % game_count ]), 8, 16);
            matrix.drawRGBBitmap(matrixWidth-i, 0, (bmps[selected_game]), 8, 16);
            matrix.show();
            delay(anim_speed);
        }
        break;

        case 'o':
        call_game(selected_game);
        break;
    }

    keychar = NULL;

    matrix.drawRGBBitmap(0, 0, (bmps[selected_game]), 8, 16);
    matrix.show();

    if(analogRead(JOYX) > 640) keychar = 'd';
    if(analogRead(JOYX) < 384) keychar = 'a';
    if(digitalRead(JOYB) == 0)
    {
        if(timeout_b == 0)
        {
            keychar = 'o';
            timeout_b = restart_timeout;
        }
    }
    else timeout_b = 0;

    delay(10);
}
