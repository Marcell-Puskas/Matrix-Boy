#ifndef SETTINGS_EEPROM_H
#define SETTINGS_EEPROM_H

#include "matrix_boy_IO.h"

extern int16_t GyX_U_max, GyX_D_max;
extern int16_t GyY_L_max, GyY_R_max;
extern byte settingnum;
extern int16_t *settings[];

void eeprom_load();
void eeprom_save();

#endif