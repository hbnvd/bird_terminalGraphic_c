#include "terminalGraphic.h"
ColorID buffer[WD_HEI][WD_WID];

const char* COLOR_STR[] = {
    [RESET] = "\x1b[0m",
    [RED] = "\x1b[31m", [GREEN] = "\x1b[32m", [YELLOW] = "\x1b[33m", [BLUE] = "\x1b[34m",
    [MAGENTA] = "\x1b[35m", [CYAN] = "\x1b[36m", [WHITE] = "\x1b[37m", [BLACK] = "\x1b[30m",
    [B_RED] = "\x1b[91m", [B_GREEN] = "\x1b[92m", [B_YELLOW] = "\x1b[93m", [B_BLUE] = "\x1b[94m",
    [B_MAGENTA] = "\x1b[95m", [B_CYAN] = "\x1b[96m", [B_WHITE] = "\x1b[97m", [B_BLACK] = "\x1b[90m",
    [BG_RED] = "\x1b[41m", [BG_GREEN] = "\x1b[42m", [BG_YELLOW] = "\x1b[43m", [BG_BLUE] = "\x1b[44m",
    [BG_MAGENTA] = "\x1b[45m", [BG_CYAN] = "\x1b[46m", [BG_WHITE] = "\x1b[47m", [BG_BLACK] = "\x1b[40m",
    [BG_B_RED] = "\x1b[101m", [BG_B_GREEN] = "\x1b[102m", [BG_B_YELLOW] = "\x1b[103m", [BG_B_BLUE] = "\x1b[104m",
    [BG_B_MAGENTA] = "\x1b[105m", [BG_B_CYAN] = "\x1b[106m", [BG_B_WHITE] = "\x1b[107m", [BG_B_BLACK] = "\x1b[100m"
};

void programEnd() {
    printf("%s", COLOR_STR[RESET]);
    cursorMove(0, WD_HEI + 1);
    cursorShow();
    exit(0);
}
// some utilitize func
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}
// some str func

// Some simple math func

// draw into buffer func
void bufferDrawPoint(ColorID color, Vertice2d a) {
    if (color == AIR) return;
    int x = (int)a.x + ScreenX, y = (int)a.y + ScreenY;
    if (x<0 || y<0 || x>=WD_WID || y>=WD_HEI) {
    //     printf("%s\nU draw a %spoint%s out of the screen\n", COLOR_STR[RESET], COLOR_STR[RED], COLOR_STR[RESET]);
    //     exit(-1);
        return;
    }
    buffer[y][x] = color;
    return;
}
void bufferDrawLine(ColorID color, Vertice2d a, Vertice2d b) {
    if (color == AIR) return;
    int x1 = (int)a.x + ScreenX, y1 = (int)a.y + ScreenY;
    int x2 = (int)b.x + ScreenX, y2 = (int)b.y + ScreenY;

    if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 || x1 >= WD_WID || x2 >= WD_WID || y1 >= WD_HEI || y2 >= WD_HEI) {
        // printf("%s\nU draw %sline%s out of the screen\n", COLOR_STR[RESET], COLOR_STR[RED], COLOR_STR[RESET]);
        // exit(-1);
        return;
    }

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    
    int sx;
    if (x1 < x2) {
        sx = 1;
    } else {
        sx = -1;
    }
    int sy;
    if (y1 < y2) {
        sy = 1;
    } else {
        sy = -1;
    }

    // 3. Biến sai số (Error) - Trái tim của thuật toán Bresenham
    int err = dx - dy;

    while (1) {
        buffer[y1][x1] = color;

        // Nếu đã vẽ đến điểm cuối thì thoát vòng lặp
        if (x1 == x2 && y1 == y2) {
            break;
        }

        int e2 = 2 * err;

        if (e2 > -dy) {
            err = err - dy;
            x1 = x1 + sx;
        }
        if (e2 < dx) {
            err = err + dx;
            y1 = y1 + sy;
        }
    }
}
void floodFillRecursive(ColorID newColor, int x, int y) {
    if (x < 0 || y < 0 || x >= WD_WID || y >= WD_HEI) return;

    if (buffer[y][x] == newColor) return;

    buffer[y][x] = newColor;

    floodFillRecursive(newColor, x + 1, y);
    floodFillRecursive(newColor, x - 1, y);
    floodFillRecursive(newColor, x, y + 1);
    floodFillRecursive(newColor, x, y - 1);
}
void bufferFillArea(ColorID newColor, Vertice2d a) {
    if (newColor == AIR) return;
    int x = (int)a.x + ScreenX, y = (int)a.y + ScreenY;

    if (x < 0 || y < 0 || x >= WD_WID || y >= WD_HEI) return;
    
    if (buffer[y][x] == newColor) return;
    
    floodFillRecursive(newColor, x, y);
}
// composive drawing func
void bufferDrawTriangle(ColorID bodyColor, ColorID lineColor, Vertice2d a, Vertice2d b, Vertice2d c) {
    if (a.x < -ScreenX || a.y < -ScreenY || b.x < -ScreenX || b.y < -ScreenY || c.x < -ScreenX || c.y < -ScreenY) {
        // printf("%s\nU draw %sTRIANGLE%s out of the screen\n",COLOR_STR[RESET], COLOR_STR[RED], COLOR_STR[RESET]);
        // exit(-1);
        return;
    }
    if (a.x >= ScreenX || a.y >= ScreenY || b.x >= ScreenX || b.y >= ScreenY || c.x >= ScreenX || c.y >= ScreenY) {
        // printf("%s\nU draw %sTRIANGLE%s out of the screen\n",COLOR_STR[RESET], COLOR_STR[RED], COLOR_STR[RESET]);
        // exit(-1);
        return;
    }
    bufferDrawLine(lineColor, a, b);
    bufferDrawLine(lineColor, a, c);
    bufferDrawLine(lineColor, b, c);

    Vertice2d centroid = {(a.x + b.x + c.x)/3, (a.y + b.y + c.y)/3};
    bufferFillArea(bodyColor, centroid);
    return;
}
void bufferDrawCircle(ColorID bodyColor, ColorID lineColor, Vertice2d center, double r) {
    int x0 = (int)center.x + ScreenX;
    int y0 = (int)center.y + ScreenY;
    int radius = (int)r;

    if (x0 - radius < 0 || x0 + radius >= WD_WID || 
        y0 - radius < 0 || y0 + radius >= WD_HEI) {
        return;
    }

    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        buffer[y0 + y][x0 + x] = lineColor;
        buffer[y0 + x][x0 + y] = lineColor;
        buffer[y0 + x][x0 - y] = lineColor;
        buffer[y0 + y][x0 - x] = lineColor;
        buffer[y0 - y][x0 - x] = lineColor;
        buffer[y0 - x][x0 - y] = lineColor;
        buffer[y0 - x][x0 + y] = lineColor;
        buffer[y0 - y][x0 + x] = lineColor;

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
    
    if (bodyColor != AIR) {
        x = radius; y = 0; err = 0;
        while (x >= y) {
            for (int i = x0 - x; i <= x0 + x; i++) buffer[y0 + y][i] = bodyColor;
            for (int i = x0 - x; i <= x0 + x; i++) buffer[y0 - y][i] = bodyColor;
            for (int i = x0 - y; i <= x0 + y; i++) buffer[y0 + x][i] = bodyColor;
            for (int i = x0 - y; i <= x0 + y; i++) buffer[y0 - x][i] = bodyColor;

            if (err <= 0) {
                y += 1;
                err += 2 * y + 1;
            }
            if (err > 0) {
                x -= 1;
                err -= 2 * x + 1;
            }
        }
    }
}
// buffer func
void bufferClear(ColorID color) {
    for (int i = 0; i < WD_HEI; ++i) {
        for (int j = 0; j < WD_WID; ++j) {
            buffer[i][j] = color;
        }
    }
}
void bufferPutToScreen() {
    cursor00();
    static char subBuffer[WD_HEI * WD_WID * 8 + WD_HEI*10]; 
    subBuffer[0] = '\0';

    char *ptr = subBuffer;

    for (int i = 0; i < WD_HEI; ++i) {
        for (int j = 0; j < WD_WID; ++j) {
            ptr += sprintf(ptr, "%s%c", COLOR_STR[buffer[i][j]], BLANK);
        }
        ptr += sprintf(ptr, "%s\n", COLOR_STR[RESET]);
    }

    fputs(subBuffer, stdout); 
}
