#ifndef IMAGEMANAGER_IMAGEMANAGER_H
#define IMAGEMANAGER_IMAGEMANAGER_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <map>
#include "FileException.h"

#ifndef IMAGETYPE_ENUMDEFINE
#define IMAGETYPE_ENUMDEFINE
enum ImageType {
    P5 = 0, P6 = 1
};
#else
#pragma message("  ATTENTION : IMAGETYPE ENUMERATION already defined")
#endif


#ifndef TYPE_COORDINATE
#define TYPE_COORDINATE
struct ImageCoordinate {
    long horizontal;
    long vertical;
};
#else
#pragma message("  ATTENTION : TYPE_COORDINATE already defined")
#endif

#ifndef BYTE_AS_UNSIGNED_CHAR
#define BYTE_AS_UNSIGNED_CHAR
typedef unsigned char byte;
#else
#pragma message("  ATTENTION : BYTE_AS_UNSIGNED_CHAR already defined")
#endif

#ifndef COLOR_DEFINE
#define COLOR_DEFINE
enum Color {
    WHITE = 255, BLACK = 0, RED=200
};
#else
#pragma message("  ATTENTION : COLOR already defined")
#endif

using namespace std;

class Image {
public:
    byte **_image;          // Source
    // In PPM File : NbBytes = 3* NbPixels
    // In PGM File : NbBytes = NbPixels
    long _nbPixelsWidth;
    long _nbPixelsHeight;
    long _nbBytesWidth;
    long _nbBytesHeight;
    long _gris;
    string _filename;
    ImageType _type; //P5, P6, ...
    // The only reader for the current image
    std::ifstream _imageReader;

    int _histogram[256];
    int _histogramR[256];
    int _histogramG[256];
    int _histogramB[256];

    std::ofstream writeHeader(string outputFilename);

private:
    void readHeader();

    void initImageMatrix();

    void load();

    void initImageType(string basic_string);

public:

    Image();

    Image(char *_filename);

    Image(ImageType type, long height, long width);

    Image(ImageType type, long height, long width, byte **matrix);

    void close();

    byte **initMatrix(long &nbBytesHeight, long &nbBytesWidth);

    void save(char *outputFilename);

    void save(char *outputFilename, byte **matrix, long &nbBytesHeight, long &nbBytesWidth);

    void explain();

    void initHistoArrays();

    void saveImageInformations(char *outputFilename);

//    Image operator=(const Image &arg);
};

#endif //IMAGEMANAGER_IMAGEMANAGER_H
