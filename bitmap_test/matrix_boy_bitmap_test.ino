// Adafruit_NeoMatrix example for tiled NeoPixel matrices.  Scrolls
// 'Howdy' across three 10x8 NeoPixel grids that were created using
// NeoPixel 60 LEDs per meter flex strip.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6

// MATRIX DECLARATION:
// Parameter 1 = width of EACH NEOPIXEL MATRIX (not total display)
// Parameter 2 = height of each matrix
// Parameter 3 = number of matrices arranged horizontally
// Parameter 4 = number of matrices arranged vertically
// Parameter 5 = pin number (most are valid)
// Parameter 6 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the FIRST MATRIX; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs WITHIN EACH MATRIX are
//     arranged in horizontal rows or in vertical columns, respectively;
//     pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns WITHIN
//     EACH MATRIX proceed in the same order, or alternate lines reverse
//     direction; pick one.
//   NEO_TILE_TOP, NEO_TILE_BOTTOM, NEO_TILE_LEFT, NEO_TILE_RIGHT:
//     Position of the FIRST MATRIX (tile) in the OVERALL DISPLAY; pick
//     two, e.g. NEO_TILE_TOP + NEO_TILE_LEFT for the top-left corner.
//   NEO_TILE_ROWS, NEO_TILE_COLUMNS: the matrices in the OVERALL DISPLAY
//     are arranged in horizontal rows or in vertical columns, respectively;
//     pick one or the other.
//   NEO_TILE_PROGRESSIVE, NEO_TILE_ZIGZAG: the ROWS/COLUMS OF MATRICES
//     (tiles) in the OVERALL DISPLAY proceed in the same order for every
//     line, or alternate lines reverse direction; pick one.  When using
//     zig-zag order, the orientation of the matrices in alternate rows
//     will be rotated 180 degrees (this is normal -- simplifies wiring).
//   See example below for these values in action.
// Parameter 7 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 pixels)
//   NEO_GRB     Pixels are wired for GRB bitstream (v2 pixels)
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA v1 pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)

// Example with three 10x8 matrices (created using NeoPixel flex strip --
// these grids are not a ready-made product).  In this application we'd
// like to arrange the three matrices side-by-side in a wide display.
// The first matrix (tile) will be at the left, and the first pixel within
// that matrix is at the top left.  The matrices use zig-zag line ordering.
// There's only one row here, so it doesn't matter if we declare it in row
// or column order.  The matrices use 800 KHz (v2) pixels that expect GRB
// color data.
int matrixWidth = 8;
int matrixHeight = 8;
int tilesX = 1;
int tilesY = 2;
int pin = 6;
int matrixType = NEO_TILE_TOP;
int ledType = NEO_GRB;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
    matrixWidth, matrixHeight, tilesX, tilesY, pin, matrixType, ledType);


static const uint16_t RGB_bmp[] PROGMEM = {
    0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0xffe0, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0xf800, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 
    0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f
};

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
    matrix.begin();
    //matrix.setTextWrap(false);
    matrix.setBrightness(40);
    //matrix.setTextColor(colors[0]);
}

int x    = matrix.width();
int pass = 0;

void loop() {
    matrix.drawRGBBitmap(0, 0, RGB_bmp, 8, 16);
    matrix.show();
    delay(100);
}
