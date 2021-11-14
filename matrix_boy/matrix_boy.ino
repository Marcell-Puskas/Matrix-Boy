#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include "matrix_boy_IO.h"
#include "matrix_boy_image_bmps.h"
#include "Snake_game.h"
#include "Tetris_game.h"


//static const 
const int game_count = 2;
const int anim_speed = 25;
int selected = 0;
char keychar;

int timeout_x, timeout_y, timeout_b = 0;

const int matrixWidth = 8;
const int matrixHeight = 8;
const int tilesX = 1;
const int tilesY = 2;
const int pin = 6;
const int matrixType = NEO_TILE_TOP;
const int ledType = NEO_GRB;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
    matrixWidth, matrixHeight, tilesX, tilesY, pin, matrixType, ledType);



void call_game(int game_index) {
    switch (game_index)
    {
        case 0:
        Snake_game();
        break;

        case 1:
        Tetris_game();
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

