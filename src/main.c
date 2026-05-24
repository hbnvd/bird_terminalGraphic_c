
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include "terminalGraphic.h"

// define 
#define elif else if

#define JUMP ' '
#define GRAVITY 0.5
#define assetsPath "../assets/assets.txt"

// var & struct
typedef struct Sprite {
    int wid, hei;
    ColorID texture[16*16];
} Sprite;

typedef struct Obj 
{
    Vertice2d pos;
    int hbWid, hbHei; // hit box size
    Sprite spr;
} Obj;
int shouldRun = 1;

Obj *objList[500]; int objListLen = 0;

Sprite spr_flappy_normal;
Obj flappy; 

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

void addObj(Obj *obj)
{
    objList[objListLen] = obj;
    ++objListLen;
}
void spriteClear(ColorID sprite[], ColorID color, int wid, int hei)
{
    for (int i = 0; i < wid*hei; ++i) sprite[i] = color;
}
ColorID sprGetPixel(Sprite *spr, int x, int y) 
{
    if (x < 0 || x >= spr->wid || y < 0 || y >= spr->hei) 
    {
        return AIR; 
    }
    return spr->texture[y * spr->wid + x];
}
void bufferDrawObj(Obj *obj)
{
    for (int y = 0; y < obj->spr.hei; ++y)
    {
        for (int x = 0; x < obj->spr.wid; ++x) 
        {
            bufferDrawPoint(sprGetPixel(&(obj->spr), x, y), (Vertice2d){obj->pos.x + x, obj->pos.y + y});
        }
    }
    return;
} 
int loadSpriteFromFile(const char *filePath, const char *spriteName, Sprite *outSpr) {
    FILE *f = fopen(filePath, "r");
    if (f == NULL) {
        printf("%sError: Cannot open file %s%s\n", COLOR_STR[RED], filePath, COLOR_STR[RESET]);
        return 0; 
    }

    char line[256];
    int found = 0;

    // Step 1: Find the sprite identifier tag
    while (fgets(line, sizeof(line), f) != NULL) {
        line[strcspn(line, "\r\n")] = 0;

        if (strcmp(line, spriteName) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("%sError: Sprite tag '%s' not found in file!%s\n", COLOR_STR[RED], spriteName, COLOR_STR[RESET]);
        fclose(f);
        return 0;
    }

    // Step 2: Read width and height
    if (fscanf(f, "%d %d", &(outSpr->wid), &(outSpr->hei)) != 2) {
        printf("%sError: Invalid sprite dimensions!%s\n", COLOR_STR[RED], COLOR_STR[RESET]);
        fclose(f);
        return 0;
    }

    // Step 3: Scan the integer matrix into texture array
    int totalElements = outSpr->wid * outSpr->hei;
    for (int i = 0; i < totalElements; ++i) {
        int colorVal;
        if (fscanf(f, "%d", &colorVal) == 1) {
            outSpr->texture[i] = (ColorID)colorVal;
        } else {
            printf("%sError: Missing texture data at index %d!%s\n", COLOR_STR[RED], i, COLOR_STR[RESET]);
            fclose(f);
            return 0;
        }
    }

    // Step 4: Check for the #END tag
    char endTag[50];
    if (fscanf(f, "%s", endTag) != 1 || strcmp(endTag, "#END") != 0) {
        printf("%sWarning: Missing valid '#END' tag!%s\n", COLOR_STR[YELLOW], COLOR_STR[RESET]);
    }

    fclose(f);
    return 1; 
}

int main() 
{
    // Init
    system("cls");
    cursorHide();
    bufferClear(B_BLUE);
    
    // Kích hoạt hỗ trợ mã màu ANSI \x1b trên Windows Terminal để loadSpriteFromFile báo lỗi có màu
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    
    // Read sprites from file
    loadSpriteFromFile(assetsPath, "#spr_flappy_normal", &spr_flappy_normal);

    flappy.pos = (Vertice2d){0, 0};
    flappy.hbWid = spr_flappy_normal.wid;
    flappy.hbHei = spr_flappy_normal.hei;
    flappy.spr = spr_flappy_normal;
    
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
                shouldRun = 0;
            } elif (ch == ' ') {
                flappy.pos.y += -10;
            }
        }

        flappy.pos.y += GRAVITY;

        // Render
        for (int i = objListLen-1; i >= 0; --i)
        {
            bufferDrawObj(objList[i]);
        }

        bufferPutToScreen();
        Sleep(1);
    }
    
    programEnd();
    return 0;
}
