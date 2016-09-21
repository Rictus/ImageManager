//
// Created by Dylan on 21/09/2016.
//
#include "PGM.h"

PGM::PGM(char *_filename) : Image(_filename) {}

void PGM::load() {

    string inputLine = "";
    byte b;

    while (!Image::imageReader.eof()) {
        Image::imageReader.read((char *) &b, 1);


    }
}

byte **initMatrix() {
    byte matrix[_width][Image::_height];
}

void PGM::save() {

}
