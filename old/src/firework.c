#include <math.h>
#include "img.h"
#include "util.h"

double radius1[100];
double radius2[100];
double radius3[100];
double radius4[100];
double radius5[100];
double radius6[100];
double radius7[100];
double radius8[100];

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

void shoot(int time, int cycle, Area area){
    
}

void explode(Color innercolor, Color outercolor, int time, int cycle, Area area){
    
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
        int head_y = (int)(height_explosion - (height_explosion / pow(time_explosion, 2.)) * pow(time - time_explosion, 2.)) + area.ymin;
        img_fillcircle(addTransparency(FLASH, NIGHT, suddenAttenuation(time, time_explosion)), axis, head_y, 2);

        for(int i = 0; i < height_explosion / 2; i ++){
            if(head_y - i > HORIZON_Y)
                img_putpixel(addTransparency(FLASH, NIGHT, linerAttenuation(i, height_explosion / 2) * suddenAttenuation(time, time_explosion)), axis + snake(head_y - i), head_y - i);
        }

    }else{
        int time_afterex = time - time_explosion;
        int time_flowering = cycle - time_explosion;

        int r = width / 2;
        radius[time_afterex] = r * sqrt((double)time_afterex / time_flowering);
        for(int i = 0; i < 16; i++){
            double theta = 2 * 3.14 * i / 16;
            for(int t = 0; t < time_afterex; t++){ // t = 0 => latest
                img_putpixel(addTransparency(outercolor, NIGHT, sqrtAttenuation(t, 1. / time_afterex) * suddenAttenuation(time_afterex, time_flowering)),
                        (int)(radius[time_afterex - t - 1] * sin(theta))    + axis, (int)(radius[time_afterex - t - 1] * cos(theta))    + height_explosion + area.ymin - 2 * pow((double)(time_afterex - t) / time_flowering, 2.));
                img_putpixel(addTransparency(innercolor, NIGHT, sqrtAttenuation(t, 1. / time_afterex) * suddenAttenuation(time_afterex, time_flowering)),
                        (int)(radius[time_afterex - t - 1] * sin(theta)/ 2) + axis, (int)(radius[time_afterex - t - 1] * cos(theta)/ 2) + height_explosion + area.ymin - 2 * pow((double)(time_afterex - t) / time_flowering, 2.));
            }
        }
    }
}

void firework(int time){
    Color red = {255, 100, 100};
    Color green = {100, 255, 100};
    Color blue = {100, 100, 255};

    Area firework1 = toArea(toPoint(15, HORIZON_Y), toPoint(75, 190));
    dotFirework(red, FLASH, time, 5, 77, firework1, radius1);

    Area firework2 = toArea(toPoint(120, HORIZON_Y), toPoint(180, 190));
    dotFirework(green, FLASH, time, 0, 83, firework2, radius2);

    Area firework3 = toArea(toPoint(225, HORIZON_Y), toPoint(285, 190));
    dotFirework(blue, FLASH, time, 10, 75, firework3, radius3);

    Area firework4 = toArea(toPoint(85, HORIZON_Y), toPoint(115, 130));
    dotFirework(FLASH, FLASH, time, 14, 74, firework4, radius4);

    Area firework5 = toArea(toPoint(185, HORIZON_Y), toPoint(215, 130));
    dotFirework(FLASH, FLASH, time, 3, 80, firework5, radius5);

    //Area firework6 = toArea(toPoint(225, HORIZON_Y), toPoint(285, 150));
    //dotFirework(blue, FLASH, time, 10, 80, firework6, radius6);

    //Area firework7 = toArea(toPoint(225, HORIZON_Y), toPoint(285, 150));
    //dotFirework(blue, FLASH, time, 10, 80, firework7, radius7);

    //Area firework8 = toArea(toPoint(225, HORIZON_Y), toPoint(285, 150));
    //dotFirework(blue, FLASH, time, 10, 80, firework8, radius8);
}
