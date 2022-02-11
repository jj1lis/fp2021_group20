#pragma once

#include "img.h"

typedef struct{
    int x, y;
} Point;

typedef struct{
    int xmin, xmax, ymin, ymax;
} Area;

typedef struct color Color;

Point toPoint(int, int);

Area toArea(Point, Point);

Color addTransparency(Color, Color, double);

int max(int, int);
int min(int, int);

const Color FLASH;
const Color NIGHT;
const Color NIGHT_DARK;
const Color NIGHT_MIDDLEDARK;
const Color GRAY;
const Color LIGHT;

const int HORIZON_Y;
