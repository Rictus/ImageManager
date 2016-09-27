#ifndef IMAGEMANAGER_IMAGEMANAGER_H
#define IMAGEMANAGER_IMAGEMANAGER_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include "NRC/def.h"
#include "FileException.h"

using namespace std;

class Image {
private:
    // The only data for PPM and PGM files
    byte **_image;
    // In PPM File : NbBytes = 3* NbPixels
    // In PGM File : NbBytes = NbPixels
    long _nbPixelsWidth;
    long _nbPixelsHeight;
    long _nbBytesWidth;
    long _nbBytesHeight;
    long _gris;
    string _filename;
    string _type; //P5, P6, ...
    // The only reader for the current image
    std::ifstream _imageReader;

    int _histogram [256];
    int _histogramR [256];
    int _histogramG [256];
    int _histogramB [256];

    std::ofstream writeHeader(string outputFilename);

private:
    void readHeader();

public:
    Image(char *_filename);

    void close();

    byte **initMatrix();

    void load();

    void save(char *outputFilename);

    void save(char *outputFilename, byte **matrix);

    void save(char *outputFilename, byte **matrix, long nbBytesHeight, long nbBytesWidth);

    byte **convertPPMToPGM(int choice = 0);

    byte **initMatrix(long nbBytesHeight, long nbBytesWidth);

    byte **sobelMask();

    byte **sobelMaskHorizontal(byte **givenMatrix);

    byte **sobelMaskVertical(byte **givenMatrix);

    byte **sobelMask(string type, byte **givenMatrix);

    byte **sobelMaskComponent();

    byte **binarise(byte **m, long seuil);

    int * histogram();

    void histogramPPM();

    float mean(int *histogram);

    double bhattacharyya(int *hist1, int *hist2);

};

#endif //IMAGEMANAGER_IMAGEMANAGER_H
