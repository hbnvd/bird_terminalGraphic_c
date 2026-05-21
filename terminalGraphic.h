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

typedef enum {
    RESET = 0,
    RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, BLACK,
    B_RED, B_GREEN, B_YELLOW, B_BLUE, B_MAGENTA, B_CYAN, B_WHITE, B_BLACK,
    BG_RED, BG_GREEN, BG_YELLOW, BG_BLUE, BG_MAGENTA, BG_CYAN, BG_WHITE, BG_BLACK,
    BG_B_RED, BG_B_GREEN, BG_B_YELLOW, BG_B_BLUE, BG_B_MAGENTA, BG_B_CYAN, BG_B_WHITE, BG_B_BLACK,
    COLOR_COUNT, AIR = 0
} ColorID;

extern const char* COLOR_STR[];
extern ColorID buffer[WD_HEI][WD_WID];

// some simple math struct
typedef struct Vertice2d {
    double x, y;
} Vertice2d;
typedef struct Vertice3d {
    double x, y, z;
} Vertice3d;
// some simple math func

// buffer func
void bufferClear(ColorID color);
void bufferClear_AVX2(ColorID color);
void bufferPutToScreen();
void bufferDrawPoint(ColorID color, Vertice2d a);
void bufferDrawLine(ColorID color, Vertice2d a, Vertice2d b);
void floodFillRecursive(ColorID newColor, int x, int y);
void bufferFillArea(ColorID newColor, Vertice2d a);
// composive drawing func
void bufferDrawTriangle(ColorID bodyColor, ColorID lineColor, Vertice2d a, Vertice2d b, Vertice2d c);
void bufferDrawCircle(ColorID bodyColor, ColorID lineColor, Vertice2d i, double r);
void programEnd();

#endif
