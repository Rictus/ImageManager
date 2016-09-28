//
// Created by Dylan on 27/09/2016.
//

#ifndef IMAGEMANAGER_IMAGEPROCESSOR_H
#define IMAGEMANAGER_IMAGEPROCESSOR_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include "Image.h"


#ifndef GRAYSCALEALGORITHM_ENUMDEFINE
#define GRAYSCALEALGORITHM_ENUMDEFINE
enum GrayscaleConvertionAlgorithm {
    LIGHTNESS = 0, AVERAGE = 1, LUMINOSITY = 2
};
#else
#pragma message("  ATTENTION : GRAYSCALEALGORITHM ENUMERATION already defined")
#endif

class ImageProcessor : protected Image {
public:
    Image convertPPMToPGM(GrayscaleConvertionAlgorithm algorithm, Image &img);


    Image sobelMaskHorizontal(Image &img);

    Image sobelMaskVertical(Image &img);

    Image sobelMask(ImageType type, Image &img);

    Image sobelMask(Image &img);

    Image sobelMaskComponent(Image &img);

    int *histogram(Image &img);

    void histogramPPM(Image &img);

    float mean(int *histogram);

    float bhattacharyya(int *hist1, int *hist2);

    Image binarisePGM(Image &m, const long &seuil);

    Image binarise(Image &img, long seuil);

    Image binarisePPM(Image &m, long seuil);

    double calculOutlineRate(Image &binarisedMatrix);
};


#endif //IMAGEMANAGER_IMAGEPROCESSOR_H
