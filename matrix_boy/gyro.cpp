#include <Wire.h>
#include "matrix_boy_IO.h"

const int MPU=0x68; 
int16_t AcX,AcY,AcZ,GyX,GyY,GyZ;
int16_t AcXC,AcYC,AcZC,GyXC,GyYC,GyZC;

int sgyro = 8;      //gyro sensitivity
const int mgyro = 4095;  //gyro_multiplier
const int max_sgyro = 8;

int sacc = 8;       //acc_sensitivity
const int macc = 4095;   //acc_multiplier
const int max_sacc = 8;

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
  
void gyro_test() {
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
        matrix.setCursor(0, 1);
        matrix.print(gyro_or_accel_mode? "G" : "A");

        if(gyro_or_accel_mode)
        {
            Serial.print(GyX);
            Serial.print("\t");
            Serial.print(GyY);
            Serial.print("\t");
            Serial.println(GyZ);

            matrix.drawLine(mapx - 3, mapy - map(GyX, -sgyro * mgyro, sgyro * mgyro, 1, mapy-1), mapx - 3, mapy - 1, x_color);
            matrix.drawLine(mapx - 2, mapy - map(GyY, -sgyro * mgyro, sgyro * mgyro, 1, mapy-1), mapx - 2, mapy - 1, y_color);
            matrix.drawLine(mapx - 1, mapy - map(GyZ, -sgyro * mgyro, sgyro * mgyro, 1, mapy-1), mapx - 1, mapy - 1, z_color);

            matrix.drawPixel(map(GyY, -sgyro * mgyro, sgyro * mgyro, 0, mapx-3), map(GyZ, -sgyro * mgyro, sgyro * mgyro, 7, mapy-1), dot_color);

            matrix.drawLine(0, 0, sgyro-1, 0, sens_color);
        }
        else
        {
            Serial.print(AcX);
            Serial.print("\t"); 
            Serial.print(AcY);
            Serial.print("\t");
            Serial.println(AcZ); 

            matrix.drawLine(mapx - 3, mapy - map(AcX, -sacc * macc, sacc * macc, 1, mapy-1), mapx - 3, mapy - 1, x_color);
            matrix.drawLine(mapx - 2, mapy - map(AcY, -sacc * macc, sacc * macc, 1, mapy-1), mapx - 2, mapy - 1, y_color);
            matrix.drawLine(mapx - 1, mapy - map(AcZ, -sacc * macc, sacc * macc, 1, mapy-1), mapx - 1, mapy - 1, z_color);

            matrix.drawPixel(map(AcY, -sacc * macc, sacc * macc, 0, mapx-3), map(AcZ, -sacc * macc, sacc * macc, 7, mapy-1), dot_color);
            
            matrix.drawLine(0, 0, sacc-1, 0, sens_color);
        }
        matrix.show();

        delay(input_update);

        Input();   
        switch (keychar)
        {
            case 'e':
                run = false;
                break;
            
            case 'd':
                if(gyro_or_accel_mode){ if(sgyro < max_sgyro) sgyro++; }
                else{ if(sacc < max_sacc) sacc++; }
                break;

            case 'a':
                if(gyro_or_accel_mode){ if(sgyro > 1) sgyro--; }
                else{ if(sacc > 1) sacc--;}
                break;
            
            case 'w':
                gyro_or_accel_mode = !gyro_or_accel_mode;
                Serial.println(gyro_or_accel_mode? "Gyroscope mode\nGyX\tGyY\tGyZ" : "Accelerometer mode\nAcX\tAcY\tAcZ");
                break;

            case 's':
                AcXC = AcX;
                AcYC = AcY;
                AcZC = AcZ;
                GyXC = GyX;
                GyYC = GyY;
                GyZC = GyZ;
                break;
        }
    }
}
