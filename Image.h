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

class Image {
private:
    int _width;
    int _height;
    string _filename;
    string _header;

public:
    Image(char *_filename);

private:
    void readHeader();
};


#endif //IMAGEMANAGER_IMAGEMANAGER_H
