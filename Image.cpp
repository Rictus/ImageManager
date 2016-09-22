//
// Created by Dylan on 20/09/2016.
//

#include <cmath>
#include <fstream>
#include "Image.h"
#include <sstream>
#include "FileException.h"

using namespace std;

Image::Image(char *_filename) : _filename(_filename) {
    _nbPixelsWidth = 0;
    _nbPixelsHeight = 0;
    fstream _file(_filename, ios_base::in | ios_base::out | ios_base::binary);
    if (!_file) {
        throw FileException(_filename);
    } else {
        this->close();
    }
    this->readHeader();
}

void Image::readHeader() {
    _imageReader.open(_filename, ios_base::in | ios_base::out | ios_base::binary);
    string inputLine = "";

    int order = 0;
    while (!_imageReader.eof() && order < 3) {
        getline(_imageReader, inputLine);
        if (inputLine.at(0) == '#') {
        } else {
            switch (order) {
                case 0: {
                    this->_type = inputLine;
                    order++;
                }
                    break;
                case 1: {
                    istringstream iss(inputLine);
                    string token;
                    getline(iss, token, ' ');
                    this->_nbPixelsWidth = stol(token);
                    getline(iss, token, ' ');
                    this->_nbPixelsHeight = stol(token);
                    order++;
                    break;
                }
                case 2: {
                    this->_gris = stol(inputLine);
                    order++;
                }
                    break;
                default:
                    break;
            }
        }
    }
    if (this->_type == "P5") {
        _nbBytesHeight = this->_nbPixelsHeight;
        _nbBytesWidth = this->_nbPixelsWidth;
    } else if (this->_type == "P6") {
        // * 3 car un pixel est maintenant composé de 3 composante couleur (rgb)
        _nbBytesHeight = this->_nbPixelsHeight * 3;
        _nbBytesWidth = this->_nbPixelsWidth * 3;
    } else {
        cerr << "Unknown file type : " << this->_type;
    }
}

byte **Image::initMatrix(long nbBytesHeight, long nbBytesWidth) {
    byte **matrix = new byte *[nbBytesHeight];
    for (long i = 0; i < nbBytesHeight; i = i + 1) {
        matrix[i] = new byte[nbBytesWidth];
        for (long j = 0; j < nbBytesWidth; j = j + 1) {
            matrix[i][j] = (unsigned char) 0;
        }
    }
    return matrix;
}

byte **Image::initMatrix() {
    return this->initMatrix(this->_nbBytesHeight, this->_nbBytesWidth);
}

string Image::filename() {
    return _filename;
}

void Image::close() {
    _imageReader.close();
}

ofstream Image::writeHeader(string outputFilename) {
    ofstream imageWriter;
    imageWriter.open(outputFilename,
                     std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
    imageWriter << this->_type << endl;
    imageWriter << this->_nbPixelsWidth << " " << this->_nbPixelsHeight << endl;
    imageWriter << this->_gris << endl;

    return imageWriter;
}


void Image::load() {
    byte b;
    this->_image = this->initMatrix();
    long i = 0, j = 0;
    while (!this->_imageReader.eof()) {
        this->_imageReader.read((char *) &b, 1);
        this->_image[i][j] = (byte) b;
        j = j + 1;
        if (j == _nbBytesWidth) {
            j = 0;
            i = i + 1;
        }
        if (i == _nbBytesHeight) {
            break;
        }
    }
}

void Image::save(char *outputFilename, byte **matrix, long nbBytesHeight, long nbBytesWidth) {
    ofstream imageWriter = this->writeHeader(outputFilename);
    for (long i = 0; i < nbBytesHeight; i = i + 1) {
        for (long j = 0; j < nbBytesWidth; j = j + 1) {
            imageWriter << matrix[i][j];
        }
    }
    imageWriter.close();
}

void Image::save(char *outputFilename, byte **matrix) {
    this->save(outputFilename, matrix, _nbBytesHeight, _nbPixelsWidth);
}

void Image::save(char *outputFilename) {
    this->save(outputFilename, this->_image);
}

byte **Image::sobelMaskHorizontal() {
    long sumH;
    double meanH;
    byte **resM = initMatrix();
    for (long i = 1; i < _nbPixelsHeight - 1; i = i + 1) {
        for (long j = 1; j < _nbPixelsWidth - 1; j = j + 1) {
            sumH = 0;

            //gauche
            sumH += -1 * this->_image[i - 1][j - 1];   //haut gauche
            sumH += -2 * this->_image[i - 1][j];     //centre gauche
            sumH += -1 * this->_image[i - 1][j + 1];   //bas gauche

            //centre
            sumH += 0 * this->_image[i][j - 1];     //haut centre
            sumH += 0 * this->_image[i][j];       //centre centre
            sumH += 0 * this->_image[i][j + 1];     //bas centre

            //droite
            sumH += 1 * this->_image[i + 1][j - 1];   //haut droite
            sumH += 2 * this->_image[i + 1][j];     //centre droite
            sumH += 1 * this->_image[i + 1][j + 1];   //bas droite
            meanH = std::floor(abs(sumH) * 255 / 1020);

            resM[i][j] = (byte) meanH;
        }
    }
    return resM;
}


byte **Image::sobelMaskVertical() {
    long sumH;
    double meanH;
    byte **resM = initMatrix();
    for (long i = 1; i < _nbPixelsHeight - 1; i = i + 1) {
        for (long j = 1; j < _nbPixelsWidth - 1; j = j + 1) {
            sumH = 0;

            //gauche
            sumH += -1 * this->_image[i - 1][j - 1];   //haut gauche
            sumH += 0 * this->_image[i - 1][j];     //centre gauche
            sumH += 1 * this->_image[i - 1][j + 1];   //bas gauche

            //centre
            sumH += -2 * this->_image[i][j - 1];     //haut centre
            sumH += 0 * this->_image[i][j];       //centre centre
            sumH += 2 * this->_image[i][j + 1];     //bas centre

            //droite
            sumH += -1 * this->_image[i + 1][j - 1];   //haut droite
            sumH += 0 * this->_image[i + 1][j];     //centre droite
            sumH += 1 * this->_image[i + 1][j + 1];   //bas droite
            meanH = std::floor(abs(sumH) * 255 / 1020);

            resM[i][j] = (byte) meanH;
        }
    }
    return resM;
}


byte **Image::sobelMask() {

    byte **resM = initMatrix();

    byte **Ix = this->sobelMaskHorizontal();
    byte **Iy = this->sobelMaskVertical();

    for (long i = 0; i < _nbPixelsHeight; i = i + 1) {
        for (long j = 0; j < _nbPixelsWidth; j = j + 1) {
            resM[i][j] = sqrt(pow(Ix[i][j], 2) + pow(Iy[i][j], 2));
        }
    }

    return resM;
}

//WIP
byte **Image::convertPPMToPGM(int choice) {
    byte **outputMatrix = initMatrix(_nbPixelsHeight, _nbPixelsWidth);
    long k = 0, l = 0;
    if (this->_type == "P6") {/*
        switch (choice) {
            case 0:
                auto toGreyScale = [](byte r, byte g, byte b) {
                    return (byte) ((max(r, g, b) + min(r, g, b)) / 2);
                };
                break;
            case 1:
                auto toGreyScale = [](byte r, byte g, byte b) {
                    return (byte) ((r + g + b) / 3);
                };
                break;
            case 2:
                toGreyScale = [](byte r, byte g, byte b) {
                    return (byte) ((0.21 * r) + (0.72 * g) + (0.07 * b));
                };
                break;
        }//*/

        for (long i = 0; i < _nbPixelsHeight; i = i + 1) {
            for (long j = 0; j < _nbPixelsWidth; j = j + 1) {
                byte r = this->_image[i][3 * j + 0];
                byte g = this->_image[i][3 * j + 1];
                byte b = this->_image[i][3 * j + 2];
                outputMatrix[i][j] = (byte) r;
            }
        }
        /*
        for (long i = 0; i < _nbBytesHeight; i = i + 1) {
            for (long j = 0; j < _nbBytesWidth - 2; j = j + 3) {
                byte r = this->_image[i][j];
                byte g = this->_image[i][j + 1];
                byte b = this->_image[i][j + 2];
                outputMatrix[k][l] = (byte) floor(((r + g + b) / 3));
                l = l + 1;
                if (l == _nbPixelsWidth) {
                    k = k + 1;
                    l = 0;
                }
                if (k == _nbPixelsHeight) {
                    break;
                }
            }
            if (k == _nbPixelsHeight) {
                break;
            }
        }
         //*/
    } else {
        cerr << "Not good type of file, expected PPM" << endl;
    }
    return outputMatrix;
}
