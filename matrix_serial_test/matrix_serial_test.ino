#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define MATRIX_PIN = 6;

int matrixWidth = 8;
int matrixHeight = 8;
int tilesX = 1;
int tilesY = 2;
int pin = 6;
int matrixType = NEO_TILE_TOP;
int ledType = NEO_RGB;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
  matrixWidth, matrixHeight, tilesX, tilesY, pin, matrixType, ledType);

String data = "";
int x, y = 0;
int color = 888;

void setup() {
  matrix.begin();
  matrix.setBrightness(150);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available())
  {
    data = Serial.readStringUntil(';');
    switch(data[0])
    {
      case 'x':
      x = data.substring(1).toInt();
      break;
      
      case 'y':
      y = data.substring(1).toInt();
      break;
      
      case 'c':
      color = data.substring(1).toInt();
      break;

      case 'b':
      matrix.setBrightness(data.substring(1).toInt());
      break;
    }

    Serial.print("X: ");
    Serial.println(x);
    Serial.print("Y: ");
    Serial.println(y);
    Serial.println();
    
    
  }
  matrix.drawPixel(x, y, color);
  matrix.show();
  delay(1000);
}
