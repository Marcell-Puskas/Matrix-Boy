#include <Wire.h>
#include "matrix_boy_IO.h"
#include "settings-eeprom.h"

#define INT16MAX 65536
#define INT16MIN -65535

const int MPU=0x68; 
int16_t AcX,AcY,AcZ,GyX,GyY,GyZ;

extern int16_t GyX_U_max, GyX_D_max;
extern int16_t GyY_L_max, GyY_R_max;

extern bool gyro_mode;

const uint8_t PROGMEM checkmark_bmp[] = {
    B00000000,
    B00000001,
    B00000010,
    B00000100,
    B10001000,
    B01010000,
    B00100000,
    B00000000
};
const uint16_t checkmark_color = matrix.Color(0, 255, 0);

const uint8_t PROGMEM x_bmp[] = {
    B10000001,
    B01000010,
    B00100100,
    B00011000,
    B00011000,
    B00100100,
    B01000010,
    B10000001
};
const uint16_t x_color = matrix.Color(255, 0, 0);

void checkmark_prompt(char c)
{
    matrix.clear();
    matrix.setCursor(0, 0);
    matrix.print(c);
    matrix.drawBitmap(0, mapy - 8, checkmark_bmp, 8, 8, checkmark_color);
    matrix.show();
    delay(300);
}

void x_prompt(char c)
{
    matrix.clear();
    matrix.setCursor(0, 0);
    matrix.print(c);
    matrix.drawBitmap(0, mapy - 8, x_bmp, 8, 8, x_color);
    matrix.show();
    delay(300);
}

void gyro_setup(){
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(0x6B); 
    Wire.write(0);    
    Wire.endTransmission(true);
}

void gyro_read(){
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU,12,true);
    GyX=Wire.read()<<8|Wire.read();
    GyY=Wire.read()<<8|Wire.read();
    GyZ=Wire.read()<<8|Wire.read();
    AcX=Wire.read()<<8|Wire.read();
    AcY=Wire.read()<<8|Wire.read();
    AcZ=Wire.read()<<8|Wire.read();
}
  
void gyro_app() {
    bool run = true;
    bool gyro_or_accel_mode = true;

    const uint32_t x_color = matrix.Color(255, 0, 0);
    const uint32_t y_color = matrix.Color(0, 255, 0);
    const uint32_t z_color = matrix.Color(0, 0, 255);
    const uint32_t dot_color = matrix.Color(255, 170, 0);
    const uint32_t sens_color = matrix.Color(255, 0, 255);
    
    Serial.println(gyro_or_accel_mode? "Gyroscope mode\nGyX\tGyY\tGyZ" : "Accelerometer mode\nAcX\tAcY\tAcZ");

    pause_menu = false;

    while(run)
    {
        gyro_read();
        matrix.clear();
        matrix.setCursor(0, 0);
        matrix.print(gyro_or_accel_mode? "G" : "A");

        if(gyro_or_accel_mode)
        {
            Serial.print(GyX);
            Serial.print("\t");
            Serial.print(GyY);
            Serial.print("\t");
            Serial.println(GyZ);

            matrix.drawLine(mapx - 3, mapy - map(GyX, INT16MIN, INT16MAX, 1, mapy-1), mapx - 3, mapy - 1, x_color);
            matrix.drawLine(mapx - 2, mapy - map(GyY, INT16MIN, INT16MAX, 1, mapy-1), mapx - 2, mapy - 1, y_color);
            matrix.drawLine(mapx - 1, mapy - map(GyZ, INT16MIN, INT16MAX, 1, mapy-1), mapx - 1, mapy - 1, z_color);

            matrix.drawPixel(
                map(GyY, GyY_L_max, GyY_R_max, 0, mapx-3), 
                map(GyZ, GyX_D_max, GyX_U_max, 7, mapy-1), 
                dot_color
            );
        }
        else
        {
            Serial.print(AcX);
            Serial.print("\t"); 
            Serial.print(AcY);
            Serial.print("\t");
            Serial.println(AcZ); 

            matrix.drawLine(mapx - 3, mapy - map(AcX, INT16MIN, INT16MAX, 1, mapy-1), mapx - 3, mapy - 1, x_color);
            matrix.drawLine(mapx - 2, mapy - map(AcY, INT16MIN, INT16MAX, 1, mapy-1), mapx - 2, mapy - 1, y_color);
            matrix.drawLine(mapx - 1, mapy - map(AcZ, INT16MIN, INT16MAX, 1, mapy-1), mapx - 1, mapy - 1, z_color);

            matrix.drawPixel(
                map(AcY, INT16MIN, INT16MAX, 0, mapx-3), 
                map(AcZ, INT16MIN, INT16MAX, 7, mapy-1), 
                dot_color
            );
        }
        matrix.show();

        delay(input_update);

        Input();   
        switch (keychar)
        {
            case 'e':
                run = false;
                break;

            case 'a':
                GyY_L_max = GyY;
                checkmark_prompt('L');
                eeprom_save();
                break;

            case 'd':
                GyY_R_max = GyY;
                checkmark_prompt('R');
                eeprom_save();
                break;

            case 'w':
                GyX_U_max = GyX;
                checkmark_prompt('U');
                eeprom_save();
                break;

            case 's':
                GyX_D_max = GyX;
                checkmark_prompt('D');
                eeprom_save();
                break;
            
            case 'k':
                gyro_or_accel_mode = !gyro_or_accel_mode;
                Serial.println(gyro_or_accel_mode? "Gyroscope mode\nGyX\tGyY\tGyZ" : "Accelerometer mode\nAcX\tAcY\tAcZ");
                break;

            case 'o':
                gyro_mode = !gyro_mode;
                Serial.print(gyro_mode ? "Gyro mode on!" : "Gyro mode off!");
                if(gyro_mode) checkmark_prompt('G');
                else x_prompt('G');
                break;
        }
    }
}

int gyro_xmove(int min, int max)
{
    gyro_read();
    return map( 
        constrain(GyY, GyY_L_max, GyY_R_max), 
        GyY_L_max, 
        GyY_R_max, 
        min, 
        max
    );
}

int gyro_ymove(int min, int max)
{
    gyro_read();
    return map(
        constrain(GyX, GyX_U_max, GyX_D_max), 
        GyX_U_max, 
        GyX_D_max, 
        min, 
        max
    );
}