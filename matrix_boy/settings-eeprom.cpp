#include <EEPROM.h>
#include "settings-eeprom.h"

void eeprom_load() {
    for (size_t i = 0; i < settingnum; i++)
    {
        *settings[i] = EEPROM[i * 2] * 256 + EEPROM[i * 2 + 1];
        Serial.print("Loaded: ");
        Serial.println(*settings[i]);
    }
}

void eeprom_save() {
    for (size_t i = 0; i < settingnum; i++)
    {
        EEPROM.update(i * 2, *settings[i] / 256);
        EEPROM.update(i * 2 + 1, *settings[i] % 256);
        Serial.print("Saved: ");
        Serial.println(*settings[i]);
    }
}