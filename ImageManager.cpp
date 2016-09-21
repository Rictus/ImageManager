//
// Created by Dylan on 20/09/2016.
//

#include "ImageManager.h"

ImageManager::ImageManager(char *_filename) : _filename(_filename) {
    topLeft = 0;
    topRight = 0;
    bottomLeft = 0;
    bottomRight = 0;
}

/*
 * TODO
 * Lire une image et la sauvegarder sans traitement special
 */

void ImageManager::loadPGM() {
    this->_image = LoadPGM_bmatrix(_filename, &topLeft, &topRight, &bottomLeft, &bottomRight);
}

void ImageManager::loadPPM() {
    this->_imageCouleur = LoadPPM_rgb8matrix(this->_filename, &topLeft, &topRight, &bottomLeft,
                                                       &bottomRight);
}

void ImageManager::savePPM(char *OutputFilename) {
    SavePPM_rgb8matrix(_imageCouleur, topLeft, topRight, bottomLeft, bottomRight, OutputFilename);
}

void ImageManager::savePGM(char *OutputFilename) {
    SavePGM_bmatrix(_image, topLeft, topRight, bottomLeft, bottomRight, OutputFilename);
}