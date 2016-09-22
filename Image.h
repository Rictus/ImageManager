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
    byte **_image;
    long _nbPixelsWidth;
    long _nbPixelsHeight;
    long _nbBytesWidth;
    long _nbBytesHeight;
    long _gris;
    string _filename;
    string _type; //P5, P6, ...
    ifstream _imageReader;

    ofstream writeHeader(string outputFilename);

private:
    void readHeader();

public:
    Image(char *_filename);

    string filename();

    void close();

    byte **initMatrix();

    void save(char *outputFilename);

    void load();

    byte **sobelMaskHorizontal();

    void save(char *outputFilename, byte **matrix);

    byte **sobelMaskVertical();

    byte **sobelMask();

    byte ** convertPPMToPGM(int choice = 0);

    byte **initMatrix(long nbBytesHeight, long nbBytesWidth);

    void save(char *outputFilename, byte **matrix, long nbBytesHeight, long nbBytesWidth);
};

#endif //IMAGEMANAGER_IMAGEMANAGER_H
