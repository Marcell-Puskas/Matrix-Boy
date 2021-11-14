#ifndef MATRIX_BOY_IO_H
#define MATRIX_BOY_IO_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define JOYX A0
#define JOYY A1
#define JOYB 9

extern Adafruit_NeoMatrix matrix;

extern char keychar;

extern int timeout_x, timeout_y, timeout_b;

const int restart_timeout = 50;
const int default_timeout = 10;
const int input_update = 10;
const uint32_t pause_color = matrix.Color(255, 255, 255);

#endif