//
// Created by Dylan on 20/09/2016.
//

#include "Image.h"

Image::Image(char *_filename) : _filename(_filename) {
    _width = 0;
    _height = 0;
    _header = "";
}

void Image::readHeader() {

}

/*
 * TODO
 * Lire une image et la sauvegarder sans traitement special
 *

void Image::loadPGM() {
    this->_image = LoadPGM_bmatrix(_filename, &topLeft, &topRight, &bottomLeft, &bottomRight);
}

void Image::loadPPM() {
    this->_imageCouleur = LoadPPM_rgb8matrix(this->_filename, &topLeft, &topRight, &bottomLeft,
                                                       &bottomRight);
}

void Image::savePPM(char *OutputFilename) {
    SavePPM_rgb8matrix(_imageCouleur, topLeft, topRight, bottomLeft, bottomRight, OutputFilename);
}

void Image::savePGM(char *OutputFilename) {
    SavePGM_bmatrix(_image, topLeft, topRight, bottomLeft, bottomRight, OutputFilename);
}//*/