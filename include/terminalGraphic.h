#ifndef TERMINAL_GRAPHIC_H
#define TERMINAL_GRAPHIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// WD size
#define WD_WID 320
#define WD_HEI 180

#define ScreenX (WD_WID/2)
#define ScreenY (WD_HEI/2)

#define BLANK ' '

// Cursor movement
#define cursorHide() printf("\033[?25l")
#define cursorShow() printf("\033[?25h")
#define cursorMove(x, y) printf("\033[%d;%dH", (y), (x))
#define cursor00() printf("\033[H")

// Color

typedef enum
{
    RESET = 00,
    RED = 01, GREEN = 02, YELLOW = 03, BLUE = 04, MAGENTA = 05, CYAN = 06, WHITE = 07, BLACK = 8,
    B_RED = 9, B_GREEN = 10, B_YELLOW = 11, B_BLUE = 12, B_MAGENTA = 13, B_CYAN = 14, B_WHITE = 15, B_BLACK = 16,
    AIR = -1
} ColorID;

extern const char* COLOR_STR[];
extern ColorID buffer[WD_HEI][WD_WID];

// some simple math struct
typedef struct Vertice2d 
{
    double x, y;
} Vertice2d;
typedef struct Vertice3d
{
    double x, y, z;
} Vertice3d;
// some simple math func

// buffer func
void bufferClear(ColorID color);
void bufferClear_AVX2(ColorID color);
void bufferPutToScreen();
void bufferDrawPoint(ColorID color, Vertice2d a);
void bufferDrawLine(ColorID color, Vertice2d a, Vertice2d b);
void floodFillRecursive(ColorID newColor, ColorID oldColor, int x, int y);
void bufferFillArea(ColorID newColor, Vertice2d a);
// composive drawing func
void bufferDrawTriangle(ColorID bodyColor, ColorID lineColor, Vertice2d a, Vertice2d b, Vertice2d c);
void bufferDrawCircle(ColorID bodyColor, ColorID lineColor, Vertice2d i, double r);
void programEnd();

#endif
