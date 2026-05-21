#include <windows.h>
#include <conio.h>
#include <math.h>
#include "terminalGraphic.h"

int shouldRun = 1;

double clamp(double x, double mx, double mn) {
    if (x < mn) return mn;
    if (x > mx) return mx;
    return x;
}
Vertice2d transVector(Vertice2d a, int m[][2]) {
    return (Vertice2d){m[0][0]*a.x + m[0][1]*a.y, m[1][0]*a.x + m[1][1]*a.y};
}

int main() {
    system("cls");
    cursorHide();
    bufferClear(BG_B_BLUE);
    

    while (shouldRun == 1) {
        // bufferClear(BG_B_BLUE);
        bufferClear(BG_B_BLUE);
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 27) {
                programEnd();
            }
        }
        
        



        bufferPutToScreen();
        Sleep(1); // milisecond

    }
    programEnd();
    return 0;
}
