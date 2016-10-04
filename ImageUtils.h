//
// Created by Dylan on 04/10/2016.
//

#ifndef IMAGEMANAGER_IMAGEUTILS_H
#define IMAGEMANAGER_IMAGEUTILS_H

#include <iostream>
#include <cmath>
#include "Image.h"

int *RGBToHSV(int r, int g, int b);

bool isColor(int H, int S, int V, Color color);
bool isColor_Hardcoded(int H, int S, int V, Color color);
#endif //IMAGEMANAGER_IMAGEUTILS_H
