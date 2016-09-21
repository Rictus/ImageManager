//
// Created by Dylan on 20/09/2016.
//

#ifndef IMAGEMANAGER_IMAGEMANAGER_H
#define IMAGEMANAGER_IMAGEMANAGER_H

#include <iostream>
#include "NRC/def.h"
#include "NRC/nrio.h"
#include "NRC/nralloc.h"
#include "NRC/nrarith.h"

using namespace std;

class ImageManager {
private:
    byte **_image;
    rgb8 **_imageCouleur;
    char *_filename;
    long topLeft; //nrl
    long topRight; //nrh
    long bottomLeft;//ncl
    long bottomRight;//nch
public:
    ImageManager(char *_filename);

    void loadPPM();

    void loadPGM();

    void savePPM(char *OutputFilename);

    void savePGM(char *OutputFilename);
};


#endif //IMAGEMANAGER_IMAGEMANAGER_H
