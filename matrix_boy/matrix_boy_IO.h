#ifndef MATRIX_BOY_IO_H
#define MATRIX_BOY_IO_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define JOYX A0
#define JOYY A1
#define JOYB 9

void Input(bool no_timeout = false);
void gyro_read();
int gyro_xmove(int max);
int gyro_ymove(int max);

extern Adafruit_NeoMatrix matrix;
extern char keychar;
extern int timeout_x, timeout_y, timeout_b;
extern int up_timeout, down_timeout, left_timeout, right_timeout, button_timeout;
extern bool pause_menu;

const int mapx = 8;
const int mapy = 16;
const int default_timeout = 10;
const int restart_timeout = 50;
const int exit_timeout = 100;
const int input_update = 10;
const int joy_high_threshold = 640;
const int joy_low_threshold = 384;
const uint32_t pause_color = matrix.Color(255, 255, 255);

#endif