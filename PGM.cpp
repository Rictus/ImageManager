//
// Created by Dylan on 21/09/2016.
//
#include "PGM.h"

PGM::PGM(char *_filename) : Image(_filename) {}

void PGM::load() {
    byte b;
    this->_image = Image::initMatrix();
    long i = 0, j = 0;
    while (!Image::_imageReader.eof()) {
        Image::_imageReader.read((char *) &b, 1);
        this->_image[i][j] = (byte) b;
        i = i + 1;
        if (i == _nbBytesWidth) {
            i = 0;
            j = j + 1;
        }
    }
}

void PGM::save(char *outputFilename) {
    ofstream imageWriter = Image::writeHeader(outputFilename);
    for (long i = 0; i < _nbBytesHeight; i = i + 1) {
        for (long j = 0; j < _nbBytesWidth; j = j + 1) {
            imageWriter << this->_image[j][i];
        }
    }
    imageWriter.close();
}
