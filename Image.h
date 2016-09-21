//
// Created by Dylan on 20/09/2016.
//

#ifndef IMAGEMANAGER_IMAGEMANAGER_H
#define IMAGEMANAGER_IMAGEMANAGER_H

#include <iostream>
#include <fstream>

using namespace std;
typedef unsigned char byte;

class Image {
protected:
    long _width;
    long _height;
    long _gris;
    string _filename;
    string _type; //P5, P6, ...
    ifstream _imageReader;

    ofstream writeHeader(string outputFilename);

public:
    Image(char *_filename);

    string filename();

    void close();

private:
    void readHeader();
};


#endif //IMAGEMANAGER_IMAGEMANAGER_H
