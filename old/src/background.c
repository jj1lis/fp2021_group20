#include <math.h>
#include "background.h"
#include "img.h"

typedef struct color Color;

const Color NIGHT = {27, 34, 57};
const Color NIGHT_DARK = {23, 20, 41};
const Color NIGHT_MIDDLEDARK = {25, 28, 48};
const Color GRAY = {46, 45, 59};
const Color LIGHT = {210, 207, 202};

const int HORIZON_Y = 60;

int WARNING_LIGHT[2];

int min(int a, int b){
    return (a > b ? b : a);
}

int max(int a, int b){
    return (a > b ? a : b);
}

// 水平線の夜景を描画
void dotHorizon_5(int begin, int hnum1, int hnum2, int hnum3, int hnum4, int hnum5){
    const int HORIZON[][10] = { {0, 1, 2, 3, 5, 7, 8, -1, -1, -1},
        {3, 4, 6, 7, -1, -1, -1, -1, -1, -1},
        {5, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 3, 4, 8, 9, -1, -1, -1, -1, -1},
        {3, 5, 7, 8, 9, -1, -1, -1, -1, -1}
    };

    void dotHorizon(int begin, int hnum){
        int i;
        for(i = 0; HORIZON[hnum][i] > 0; i++)
            img_putpixel(LIGHT, begin + HORIZON[hnum][i], HORIZON_Y);
    }

    dotHorizon(begin + 0,  hnum1);
    dotHorizon(begin + 10, hnum2);
    dotHorizon(begin + 20, hnum3);
    dotHorizon(begin + 30, hnum4);
    dotHorizon(begin + 40, hnum5);
}

// 点(x1, y1)と対角の点(x2, y2)の作る長方形のビルを描画。陰を幅shadow_width、明かりを幅intervalでつける。
void dotBuilding(int x1, int y1, int x2, int y2, int shadow_width, int interval){
    int xmin = min(x1, x2);
    int xmax = max(x1, x2);
    int ymin = min(y1, y2);
    int ymax = max(y1, y2);
    int width = xmax - xmin;
    int height = ymax - ymin;

    int x, y, cnt;

    img_fillrectangle(NIGHT_MIDDLEDARK, x1, y1, x2, y2);

    for(y = ymin; y <= ymax; y++)
        img_putpixel(NIGHT_DARK, xmin, y);

    for(cnt = 0; cnt < shadow_width; cnt++){
        for(x = xmin + cnt; x <= xmax + cnt; x++){
            img_putpixel(NIGHT_DARK, x, ymax + cnt);
        }
    }

    for(cnt = 0; cnt < shadow_width; cnt++){
        for(y = ymin + cnt; y <= ymax + cnt; y++){
            img_putpixel(NIGHT_DARK, xmax + cnt, y);
        }
    }

    for(x = xmin + interval; x <= xmax - interval; x += interval + 1){
        for(y = ymin + interval; y <= ymax - interval; y += interval + 1){
            img_putpixel(LIGHT, x, y);
        }
    }
}

// 根本(x, y)からタワーを描画、高さを返す (再利用のため)。
int dotTower(int x, int y){
    const int width = 3;
    const int height = 40;
    const int deck = 25;

    int i, j;

    for(i = x - width/2 - 1; i <= x + width/2 + 1; i++)
        for(j = y; j <= y + deck / 2; j++)
            img_putpixel(NIGHT_DARK, i, j);
    
    for(i = x - width/2; i <= x + width/2; i++)
        for(j = y; j <= y + deck; j++)
            img_putpixel(NIGHT_DARK, i, j);

    for(i = x - 3; i <= x + 3; i++)
        for(j = y + deck - 1; j <= y + deck + 1; j++)
            img_putpixel(NIGHT_DARK, i, j);

    img_putpixel(LIGHT, x - 2, y + deck);
    img_putpixel(LIGHT, x , y + deck);
    img_putpixel(LIGHT, x + 2, y + deck);

    for(j = y + deck + 1; j <= y + height; j++)
        img_putpixel(NIGHT_DARK, x, j);

    return y + height;
}

// 背景の変化しない部分
void initback(){
    //ベタ塗り
    img_fillrectangle(NIGHT, 0, 0, WIDTH, HEIGHT);
    //img_fillrectangle(NIGHT_MIDDLEDARK, 0, 0, WIDTH, HORIZON_Y);

    //水平線の街明かり
    dotHorizon_5(0, 1, 2, 3, 4, 5);
    dotHorizon_5(50, 3, 4, 3, 1, 5);
    dotHorizon_5(100, 2, 5, 1, 4, 3);
    dotHorizon_5(150, 1, 2, 1, 4, 5);
    dotHorizon_5(200, 2, 3, 3, 4, 1);
    dotHorizon_5(250, 5, 4, 3, 2, 1);

    // ビルを生やす
    dotBuilding(0, 20, 30, 55, 3, 3);
    dotBuilding(10, 10, 40, 50, 3, 3);
    dotBuilding(250, 45, 260, 55, 2, 1);
    dotBuilding(270, 47, 280, 57, 2, 1);
    dotBuilding(265, 37, 275, 45, 2, 1);

    // スカイツリー的なものを生やす
    int tower_x = 240;
    WARNING_LIGHT[0] = tower_x;
    WARNING_LIGHT[1] = dotTower(tower_x, 50);
    
}

void background(int time){
    initback();

    Color warninglight = {max(23, (int)(255 * (sin(2 * 3.14 * (double)(time - 20) / 80)))), 20, 41}; // NIGHT_DARKの上塗り
    img_putpixel(warninglight, WARNING_LIGHT[0], WARNING_LIGHT[1]);
}
