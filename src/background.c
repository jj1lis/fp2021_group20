#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"img.h"
#include"background.h"

struct color skycol = {34, 34, 52};
struct color white = {255, 255, 255};
int t0 = 0;
int x0 = 0;
bool flag=true;

//星をランダムで生成し,空を描画
void makesky(int t){
    int w, h;
    w = 300;
    h = 170;
    if(t==0){
        for (int i = 0; i < w; ++i)
        {
            for (int j = 0; j < h; ++j)
            {
                img_putpixel(skycol, i, j + 30);
            }
        }
        for (int i = 0; i < 24; ++i)
        {
            int numy = rand() % 30 + 1;
            int numx = rand() % 300 + 1;
            img_putpixel(white, numx, numy+170);
        }
    }

}
//地面を描画
void makeground(void){
    int w, h;
    struct color c = {12, 12, 25};
    w = 300;
    h = 30;
    for (int i = 0; i < w; ++i)
    {
        for (int j = 0; j < h; ++j)
        {
            img_putpixel(c, i, j);
        }
    }
}

//幅w,高さhの建物を(x,y)を左下にして描画
void makebuild(struct color c, int w,int h, int x, int y){

    for (int i = 0; i < w; ++i)
    {
        for (int j = 0; j < h; ++j)
        {
            img_putpixel(c, x + i, y + j);
        }
    }
    for (int i = 0; i < w; ++i)
    {
        if(i%3!=0){
            for (int j = 0; j < h; ++j)
            {
                struct color gray = {10, 10, 10};
                j += 1;
                img_putpixel(gray, x + i, y + j);
            }
        }

    }
}

//流れ星を描画
void shootingstar(int x,int y, int t){

    if (t == 10 || t == 60){
        t0 = t;
        x0 = x;

        flag = false;
    }

    if(!flag){
        int dt = t - t0;
        if(y-3*dt>160){
            if (dt < 30)
            {
                img_putpixel(white, x0 - 3 * dt, y - 3 * dt);
                img_putpixel(white, x0 - 3 * dt +1, y - 3 * dt+1);
                img_putpixel(white, x0 - 3 * dt + 2, y - 3 * dt + 2);
            }
        }
        if (dt >= 1)
        {
            img_putpixel(skycol, x0 - 3 * dt + 30, y - 3 * dt + 30);
            img_putpixel(skycol, x0 - 3 * dt + 30 + 1, y - 3 * dt + 30 + 1);
            img_putpixel(skycol, x0 - 3 * dt + 30 + 2, y - 3 * dt + 30 + 2);
        }
        if (dt + 5 > 60)
        {
            flag = true;
        }
    }
}

void background(int t){
    struct color c1 = {129, 129, 134};
    struct color c2 = {90, 90, 100};
    makesky(t);
    makeground();
    makebuild(c2, 15, 30, 239, 30);
    makebuild(c1, 12, 20, 235, 27);
    makebuild(c1, 10, 25, 50, 25);
    makebuild(c1, 13, 20, 123, 21);
    makebuild(c2, 15, 45, 21, 30);
    shootingstar(100+t, 198, t);
}
