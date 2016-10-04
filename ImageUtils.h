//
// Created by Dylan on 04/10/2016.
//

#ifndef IMAGEMANAGER_IMAGEUTILS_H
#define IMAGEMANAGER_IMAGEUTILS_H

#include <iostream>
#include <cmath>
int *RGBToHSV(int r, int g, int b);

bool isRed(const int H, const int S, const int V);
#endif //IMAGEMANAGER_IMAGEUTILS_H
