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

#endif