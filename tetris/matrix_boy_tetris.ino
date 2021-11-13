#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

int joy_x = 0;
int joy_y = 0;
int joy_button = 0;

int matrixWidth = 8;
int matrixHeight = 8;
int tilesX = 1;
int tilesY = 2;
int pin = 6;
int matrixType = NEO_TILE_TOP;
int ledType = NEO_GRB;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
    matrixWidth, matrixHeight, tilesX, tilesY, pin, matrixType, ledType);

void setup() {
    pinMode(6, OUTPUT);
    matrix.begin();
    matrix.setBrightness(1);
    Serial.begin(9600);
}

void loop()
{
	matrix.clear();

    //config
    int mapx = 8;
    int mapy = 16;

    /*int blI[][4] { 
        {0, 0, 0, 0},
        {1, 1, 1, 1}, 
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    int blJ[][4] { 
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 1},
        {0, 0, 0, 0}
    };
    int blL[][4] {
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    };
    int blO[][4] {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };
    int blS[][4] {
        {0, 0, 0, 0},
        {0, 0, 1, 1},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };
    int blT[][4] {
        {0, 1, 0},
        {1, 1, 1}
    };
    int blZ[][4] {
        {1, 1, 0},
        {0, 1, 1}
    };*/
    /* typedef struct blck
    {
        int x;
        int y;
    };
    
    blck testb[] = {
        {x = 1, testb->y = 2},
        {testb->x = 1, testb->y = 3}
    }; */

    /* int blI[][2] = {{}, {}, {}, {}};
    int blJ[][2] = {{}, {}, {}, {}};
    int blL[][2] = {{}, {}, {}, {}};
    int blO[][2] = {{}, {}, {}, {}};
    int blS[][2] = {{}, {}, {}, {}};
    int blT[][2] = {{}, {}, {}, {}};
    int blZ[][2] = {{}, {}, {}, {}}; */

    int block_cordinates[][4][2] = {
        {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
        {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
        {{2, 0}, {0, 1}, {1, 1}, {2, 1}},
        {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
        {{1, 0}, {2, 0}, {0, 1}, {1, 1}},
        {{1, 0}, {0, 1}, {1, 1}, {2, 1}},
        {{0, 0}, {1, 0}, {1, 1}, {2, 1}}
    };

    int block_offsets[][2] = {

    };

    /* int *blocks[] = 
    {
        blI,
        blJ,
        blL,
        blO,
        blS,
        blT,
        blZ
    }; */
}
