#include <math.h>
#include "img.h"

typedef struct color Color;

const Color FLASH = {255, 255, 237};
const Color SKY = {34, 34, 52};

const int HORIZON = 30;

// 点の構造体
typedef struct{
    int x, y;
} Point;

double radius1[100];
double radius2[100];
double radius3[100];
double radius4[100];
double radius5[100];

// 範囲の構造体
// 必ずtoArea (コンストラクタ代わり) を使って作る
typedef struct{
    int xmin, xmax, ymin, ymax;
} Area;

int max(int a, int b){
    return a > b ? a : b;
}

int min(int a, int b){
    return a > b ? b : a;
}

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

// グラフ y = 1 - x / a
double linerAttenuation(int x, int range){
    return 1. - (double)x / range;
}

// グラフ y = sqrt(1 - ax)
double sqrtAttenuation(int x, double a){
    return sqrt(1 - a * x);
}

// グラフ y = if t < a*5/6 then 1 else (1 - 36/a * (t - a*5/6)^2)
double suddenAttenuation(int t, int range){
    if((double)t < range * 5. / 6.)
        return 1;
    else{
        return 1 - 36. * pow((t - 5. * range / 6.), 2.) / pow(range, 2.);
    }
}

void dotFirework(Color innercolor, Color outercolor, int _time, int start, int cycle, Area area, double* radius){
    int time = _time - start;
    if(_time < start || time >= cycle)
        return;

    int width = area.xmax - area.xmin;
    int height = area.ymax - area.ymin;
    int axis = area.xmin + width / 2;

    int time_explosion = 3 * cycle / 5;
    int height_explosion = height - width / 2;

    int head_y = (int)(height_explosion - (height_explosion / pow(time_explosion, 2.)) * pow(time - time_explosion, 2.)) + area.ymin;
    int time_afterex = time - time_explosion;
    int time_flowering = cycle - time_explosion;

    // 軌跡を初期化
    if(time == 0)
        for(int cnt = 0; cnt < 100; cnt++)
            radius[cnt] = 0.;


    int snake(int i){
        if(i % 2 == 0)
            return 0;
        else if((i - 1) % 4 == 0)
            return 1;
        else
            return -1;
    }

    if(time < time_explosion){
        img_fillcircle(addTransparency(FLASH, SKY, suddenAttenuation(time, time_explosion)), axis, head_y, 2);

        for(int i = 0; i < height_explosion / 2; i ++){
            if(head_y - i > HORIZON)
                img_putpixel(addTransparency(FLASH, SKY, linerAttenuation(i, height_explosion / 2) * suddenAttenuation(time, time_explosion)), axis + snake(head_y - i), head_y - i);
        }

    }else{
        int r = width / 2;
        radius[time_afterex] = r * sqrt((double)time_afterex / time_flowering);
        for(int i = 0; i < 16; i++){
            double theta = 2 * 3.14 * i / 16;
            for(int t = 0; t < time_afterex; t++){ // t = 0 => latest
                img_putpixel(addTransparency(outercolor, SKY, sqrtAttenuation(t, 1. / time_afterex) * suddenAttenuation(time_afterex, time_flowering)),
                        (int)(radius[time_afterex - t - 1] * sin(theta))    + axis, (int)(radius[time_afterex - t - 1] * cos(theta))    + height_explosion + area.ymin - 2 * pow((double)(time_afterex - t) / time_flowering, 2.));
                img_putpixel(addTransparency(innercolor, SKY, sqrtAttenuation(t, 1. / time_afterex) * suddenAttenuation(time_afterex, time_flowering)),
                        (int)(radius[time_afterex - t - 1] * sin(theta)/ 2) + axis, (int)(radius[time_afterex - t - 1] * cos(theta)/ 2) + height_explosion + area.ymin - 2 * pow((double)(time_afterex - t) / time_flowering, 2.));
            }
        }
    }
}

void firework(int time){
    Color red = {255, 100, 100};
    Color green = {100, 255, 100};
    Color blue = {100, 100, 255};

    Area firework1 = toArea(toPoint(15, HORIZON), toPoint(75, 150));
    dotFirework(red, FLASH, time, 5, 77, firework1, radius1);

    Area firework2 = toArea(toPoint(120, HORIZON), toPoint(180, 150));
    dotFirework(green, FLASH, time, 0, 83, firework2, radius2);

    Area firework3 = toArea(toPoint(225, HORIZON), toPoint(285, 150));
    dotFirework(blue, FLASH, time, 10, 75, firework3, radius3);

    Area firework4 = toArea(toPoint(85, HORIZON), toPoint(115, 130));
    dotFirework(FLASH, FLASH, time, 14, 74, firework4, radius4);

    Area firework5 = toArea(toPoint(185, HORIZON), toPoint(215, 130));
    dotFirework(FLASH, FLASH, time, 3, 80, firework5, radius5);
}
