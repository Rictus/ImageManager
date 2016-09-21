//
// Created by Dylan on 21/09/2016.
//
#include "PGM.h"

PGM::PGM(char *_filename) : Image(_filename) {}

void PGM::load() {
    if (Image::_type != "P5") {
        std::cerr << "The given file is not of type P5. Check if its a PGM file." << endl;

    } else {
        char b;
        this->_image = initMatrix();
        long i = 0, j = 0;
        while (!Image::_imageReader.eof()) {
            Image::_imageReader.read(&b, 1);
            this->_image[i][j] = (byte) b;
            i = i + 1;
            if (i == Image::_width) {
                i = 0;
                j = j + 1;
            }
        }
    }
}

byte **PGM::initMatrix() {
    byte **matrix = new byte *[Image::_height];
    for (long i = 0; i < Image::_height; i = i + 1) {
        matrix[i] = new byte[Image::_width];
        for (long j = 0; j < Image::_width; j = j + 1) {
            matrix[i][j] = (unsigned char) 0;
        }
    }
    return matrix;
}

void PGM::save(char *outputFilename) {
    ofstream imageWriter = Image::writeHeader(outputFilename);

    for (long i = 0; i < Image::_height; i = i + 1) {
        for (long j = 0; j < Image::_width; j = j + 1) {
            imageWriter << this->_image[j][i];
//            const char * buffer = (const char *) this->_image[i][j];
//            imageWriter.write(buffer, 1);
//            imageWriter.put(this->_image[i][j]);
        }
    }
    imageWriter.close();
}
