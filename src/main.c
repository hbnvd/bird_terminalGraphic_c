#include <windows.h>
#include <conio.h>
#include <math.h>
#include "terminalGraphic.h"

// define 
#define elif else if

#define JUMP ' '
#define GRAVITY 0.5


// var & struct
typedef struct Obj 
{
    Vertice2d pos;
    int wid, hei;
    ColorID *sprite;
} Obj;
int shouldRun = 1;

Obj *objList[500]; int objListLen = 0;

// func
double clamp(double x, double mx, double mn) 
{
    if (x < mn) return mn;
    if (x > mx) return mx;
    return x;
}
Vertice2d transVector(Vertice2d a, int m[][2])
{
    return (Vertice2d){m[0][0]*a.x + m[0][1]*a.y, m[1][0]*a.x + m[1][1]*a.y};
}

void addObj(Obj *obj) {
    objList[objListLen] = obj;
    ++objListLen;
}
void spriteClear(ColorID sprite[], ColorID color, int wid, int hei) {
    for (int i = 0; i < wid*hei; ++i) sprite[i] = color;
}
ColorID sprGetPixel(Obj *obj, int x, int y) 
{
    if (x < 0 || x >= obj->wid || y < 0 || y >= obj->hei) 
    {
        return AIR; 
    }
    return obj->sprite[y*obj->wid + x];
}
void bufferDrawObj(Obj *obj)
{
    for (int y = 0; y < obj->hei; ++y)
    {
        for (int x = 0; x < obj->wid; ++x) 
        {
            bufferDrawPoint(sprGetPixel(obj, x, y), (Vertice2d){obj->pos.x + x, obj->pos.y + y});
        }
    }
    return;
} 


int main() 
{
    // Init
    system("cls");
    cursorHide();
    bufferClear(B_BLUE);
    
    ColorID spr_pipe[16*8] = {
        
    };
    ColorID spr_flappy_normal[8*4] = {
        AIR, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, AIR, AIR,
        AIR, YELLOW, YELLOW, YELLOW, BLACK, YELLOW, RED, AIR,
        AIR, WHITE, WHITE, YELLOW, YELLOW, YELLOW, RED, RED,
        WHITE, WHITE, WHITE, YELLOW, YELLOW, YELLOW, AIR, AIR,
    };
    Obj flappy = {
        (Vertice2d){0, 0}, 8, 4, spr_flappy_normal
    };
    addObj(&flappy);

    // main loop
    while (shouldRun == 1)
    {
        bufferClear(B_BLUE);

        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 27) {
                programEnd();
            } elif (ch == ' ') {
                flappy.pos.y += -10;
            }
        }
        
        // Physic
        flappy.pos.y += GRAVITY;

        // Render
        for (int i = objListLen-1; i >= 0; --i)
        {
            bufferDrawObj(objList[i]);
        }

        // color testt
        // for (ColorID i = 0; i <= 16; ++i)
        // {
        //     buffer[0][i*2] = i;
        //     buffer[0][i*2+1] = i;
        //     buffer[1][i*2] = i;
        //     buffer[1][i*2+1] = i;
        // }
        // end
        bufferPutToScreen();
        Sleep(1); // milisecond

    }
    programEnd();
    return 0;
}
