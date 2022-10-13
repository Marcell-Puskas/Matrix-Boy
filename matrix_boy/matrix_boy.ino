#include "matrix_boy_IO.h"
#include "matrix_boy_apps.h"
#include "settings-eeprom.h"
#include "menu.h"

#include "Tetris_game.h"
#include "ballgames.h"
#include "Egg_game.h"
#include "Paint.h"

#include "freeMemory.h"

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 1, 2, 6, NEO_TILE_TOP, NEO_GRB);
//matrixWidth, matrixHeight, tilesX, tilesY, pin, matrixType, ledType

byte bright = 2;

int8_t select = 0;

byte up_timeout, down_timeout, left_timeout, right_timeout, button_timeout;
bool pause_menu;
bool gyro_mode = false;
char keychar;

int16_t GyX_U_max, GyX_D_max;
int16_t GyY_L_max, GyY_R_max;

byte settingnum = 4;

int16_t *settings[] = {
    &GyX_U_max, &GyX_D_max,
    &GyY_L_max, &GyY_R_max
};

void call_game(int8_t game_index) {
    Serial.print("b");
    switch (game_index)
    {
        case 0:
        Snake_game();
        break;

        case 1:
        {
            Tetris T;
            T.Tetris_game();
        }
        break;

        case 2:
        {
            Breakout B;
            B.Breakout_game();
        }
        break;
        
        case 3:
        {
            Pong P;
            P.Pong_game();
        }
        break;

        case 4:
        {
            Egg E;
            E.Egg_game();
        }
        break;

        case 5:
        {
            Paint P;
            P.Paint_app();
        }
        break;
    }
}

void call_setting(int8_t setting_index) {
    switch (setting_index)
    {
        case 0:
        Brightness_selector();
        break;

        case 1:
        gyro_app();
        break;

        case 2:
        color_test();
        break; 
    }
}

void setup() {
    matrix.begin();
    matrix.setBrightness(bright);
    Serial.begin(115200);
    Serial.println("MatrixBoy Running");
    pinMode(JOYB, INPUT_PULLUP);
    gyro_setup();
    eeprom_load();
}

void loop() {
    Serial.println(freeMemory());

    reset_timeouts();

    if(select == -2) {
        while (select != -1) {
            Menu Settings;
            select = Settings.menu(setting_count, iwidth, iheight, setting_icons);
            if(select >= 0) call_setting(select);
        }
        
    }
    else {
        Menu Games;
        select = Games.menu(game_count, iwidth, iheight, game_icons);
        Serial.print(select);
        if(select >= 0) call_game(select);
    }
}
