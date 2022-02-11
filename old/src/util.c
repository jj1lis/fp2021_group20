#include "img.h"
#include "util.h"

const Color FLASH = {255, 255, 237};
const Color NIGHT = {27, 34, 57};
const Color NIGHT_DARK = {23, 20, 41};
const Color NIGHT_MIDDLEDARK = {25, 28, 48};
const Color GRAY = {46, 45, 59};
const Color LIGHT = {210, 207, 202};

const int HORIZON_Y = 60;

// Pointのコンストラクタ
Point toPoint(int x, int y){
    Point point = {x, y};
    return point;
}

// Areaのコンストラクタ
Area toArea(Point p, Point q){
    Area area = {min(p.x, q.x), max(p.x, q.x), min(p.y, q.y), max(p.y, q.y)};
    return area;
}

// 色baseを下地として、透明度rateの色cを与えた色を取得
Color addTransparency(Color c, Color base, double rate){
    if(rate < 0)
        rate = 0.;
    else if(rate > 1.)
        rate = 1.;

    int diff_r = c.r - base.r;
    int diff_g = c.g - base.g;
    int diff_b = c.b - base.b;

    Color res = {base.r + (int)(rate * diff_r),
                 base.g + (int)(rate * diff_g),
                 base.b + (int)(rate * diff_b) };

    return res;
}

int max(int a, int b){
    return a > b ? a : b;
}

int min(int a, int b){
    return a > b ? b : a;
}
