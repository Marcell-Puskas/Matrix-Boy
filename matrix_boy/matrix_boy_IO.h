#ifndef MATRIX_BOY_IO_H
#define MATRIX_BOY_IO_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define JOYX A0
#define JOYY A1
#define JOYB 9

const bool b_down = 0;
const bool b_up = 1;

void Input(bool no_timeout = false);
void gyro_read();
int16_t gyro_xmove(int16_t min, int16_t max);
int16_t gyro_ymove(int16_t min, int16_t max);

extern Adafruit_NeoMatrix matrix;
extern char keychar;
extern byte up_timeout, down_timeout, left_timeout, right_timeout, button_timeout;
extern bool pause_menu;

const byte mapx = 8;
const byte mapy = 16;
const uint16_t default_timeout = 100;
const uint16_t restart_timeout = 500;
const uint16_t exit_timeout = 1000;
const uint16_t input_update = 10;
const uint16_t joy_high_threshold = 640;
const uint16_t joy_low_threshold = 384;
const uint16_t score_time = 2000;
const uint16_t pause_color = matrix.Color(255, 255, 255);

#endif