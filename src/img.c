#include <stdio.h>
#include <stdlib.h>
#include "img.h"

// buf[y][x][c]が点(x, y)の色c(r:c==0, g:c==1, b:c==2)を表す
// 画面上ではx軸が右方向、y軸が下方向
static unsigned char buf[HEIGHT][WIDTH][3];

// ファイル名用のカウンタ
static int filecnt = 0;

// ファイル名
static char fname[100];

void img_clear(void){
    int i, j;
    for(j = 0; j < HEIGHT; j++){
        for(i = 0; i < WIDTH; i++){
            // 各点を#ffffff(白)にセット
            buf[j][i][0] = buf[j][i][1] = buf[j][i][2] = 255;
        }
    }
}

void img_write(void){
    // fnameを書き出すファイル名に変更
    sprintf(fname, "img%04d.ppm", ++filecnt);
    
    // "fname"というファイルに対するファイルポインタを作成
    // 書き込みモードでファイルを開く
    FILE *f = fopen(fname, "wb");

    // ファイル作成に失敗したらエラーを吐いて終了
    if(f == NULL){
        fprintf(stderr, "can't open %s\n", fname);
        exit(1);
    }

    // PPMのヘッダ書き込み
    fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);

    // bufの中身を書き込み
    fwrite(buf, sizeof(buf), 1, f);

    // ファイルを閉じる
    fclose(f);
}

void img_putpixel(struct color c, int x, int y){
    // もし指定座標が領域外なら何もせずreturn
    if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT){
        return;
    }

    // bufの各点と対応する領域に代入
    buf[HEIGHT - y - 1][x][0] = c.r;
    buf[HEIGHT - y - 1][x][1] = c.g;
    buf[HEIGHT - y - 1][x][2] = c.b;
}

void img_fillcircle(struct color c, double x, double y, double r){
    // それぞれ円領域のx座標、y座標のうち最小値と最大値
    int imin = (int)(x - r - 1);
    int imax = (int)(x + r + 1);
    int jmin = (int)(y - r - 1);
    int jmax = (int)(y + r + 1);

    int i, j;

    // 矩形領域の各点について、もし円の内側なら img_putpixel で色を塗る
    for(j = jmin; j <= jmax; j++){
        for(i = imin; i <= imax; i++){
            if((x - i) * (x - i) + (y - j) * (y - j) <= r*r){   // 点が円の内部かチェック
                img_putpixel(c, i, j);
            }
        }
    }
}

void img_fillrectangle(struct color c, int x1, int y1, int x2, int y2){
    int min(int a, int b){
        return (a > b ? b : a);
    }

    int max(int a, int b){
        return (a > b ? a : b);
    }

    // それぞれ矩形領域のx座標、y座標のうち最小値と最大値
    int imin = min(x1, x2);
    int imax = max(x1, x2);
    int jmin = min(y1, y2);
    int jmax = max(y1, y2);

    int i, j;

    // 矩形領域の各点に img_putpixel で色を塗る
    for(j = jmin; j <= jmax; j++){
        for(i = imin; i <= imax; i++){
            img_putpixel(c, i, j);
        }
    }
}
