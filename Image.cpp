//
// Created by Dylan on 20/09/2016.
//

#include "Image.h"

using namespace std;

Image::Image(char *_filename) : _filename(_filename) {
    _nbPixelsWidth = 0;
    _nbPixelsHeight = 0;
    std::fstream _file(_filename, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    if (!_file) {
        throw FileException(_filename);
    } else {
        this->close();
    }
    this->readHeader();
}

void Image::readHeader() {
    _imageReader.open(_filename, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    string inputLine = "";

    int order = 0;
    // get each word in the header
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
        // * 3 because a pixel is composed of 3 bytes (rgb)
        _nbBytesHeight = this->_nbPixelsHeight * 3;
        _nbBytesWidth = this->_nbPixelsWidth * 3;
    } else {
        cerr << "Unknown file type : " << this->_type;
    }
    _imageReader.close();
}

byte **Image::initMatrix(const long &nbBytesHeight, const long &nbBytesWidth) {
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
    return this->initMatrix(this->_nbBytesHeight, _nbBytesWidth);
}

void Image::close() {
    _imageReader.close();
}

ofstream Image::writeHeader(string outputFilename) {
    std::ofstream imageWriter;
    imageWriter.open(outputFilename,
                     std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
    imageWriter << this->_type << endl;
    imageWriter << this->_nbPixelsWidth << " " << this->_nbPixelsHeight << endl;
    imageWriter << this->_gris << endl;
    // The ofsteram is not closed so save() can still write data
    return imageWriter;
}

void Image::load() { //No longer work properly for PPM
    byte b;
    _imageReader.open(_filename, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    this->_image = this->initMatrix(); //If ppm, the init matrix is big enough
    long i, j;
    for (i = 0; i < _nbBytesHeight; i = i + 1) {
        for (j = 0; j < _nbBytesWidth; j = j + 1) {
            this->_imageReader.read((char *) &b, 1);
            this->_image[i][j] = (byte) b;
        }
    }
    this->_imageReader.close();
}

void Image::save(char *outputFilename, byte **matrix, long &nbBytesHeight, long &nbBytesWidth) {
    // Récupérer le ofstream initialisé par writeHeader
    std::ofstream imageWriter = this->writeHeader(outputFilename);
    for (long i = 0; i < nbBytesHeight; i = i + 1) {
        for (long j = 0; j < nbBytesWidth; j = j + 1) {
            imageWriter << matrix[i][j];
        }
    }
    imageWriter.close();
}

void Image::save(char *outputFilename, byte **matrix) {
    this->save(outputFilename, matrix, this->_nbBytesHeight, this->_nbBytesWidth);
}

void Image::save(char *outputFilename) {
    this->save(outputFilename, this->_image);
}

byte **Image::sobelMaskHorizontal(byte **givenMatrix) {
    long sumH;
    double meanH;
    byte **resM = initMatrix();
    for (long i = 1; i < _nbPixelsHeight - 1; i = i + 1) {
        for (long j = 1; j < _nbPixelsWidth - 1; j = j + 1) {
            sumH = 0;

            //gauche
            sumH += -1 * givenMatrix[i - 1][j - 1];   //haut gauche
            sumH += -2 * givenMatrix[i - 1][j];     //centre gauche
            sumH += -1 * givenMatrix[i - 1][j + 1];   //bas gauche

            //centre
            sumH += 0 * givenMatrix[i][j - 1];     //haut centre
            sumH += 0 * givenMatrix[i][j];       //centre centre
            sumH += 0 * givenMatrix[i][j + 1];     //bas centre

            //droite
            sumH += 1 * givenMatrix[i + 1][j - 1];   //haut droite
            sumH += 2 * givenMatrix[i + 1][j];     //centre droite
            sumH += 1 * givenMatrix[i + 1][j + 1];   //bas droite
            meanH = std::floor(abs(sumH) * 255 / 1020);

            resM[i][j] = (byte) meanH;
        }
    }
    return resM;
}

byte **Image::sobelMaskVertical(byte **givenMatrix) {
    long sumH;
    double meanH;
    byte **resM = initMatrix();
    for (long i = 1; i < _nbPixelsHeight - 1; i = i + 1) {
        for (long j = 1; j < _nbPixelsWidth - 1; j = j + 1) {
            sumH = 0;

            //gauche
            sumH += -1 * givenMatrix[i - 1][j - 1];   //haut gauche
            sumH += 0 * givenMatrix[i - 1][j];     //centre gauche
            sumH += 1 * givenMatrix[i - 1][j + 1];   //bas gauche

            //centre
            sumH += -2 * givenMatrix[i][j - 1];     //haut centre
            sumH += 0 * givenMatrix[i][j];       //centre centre
            sumH += 2 * givenMatrix[i][j + 1];     //bas centre

            //droite
            sumH += -1 * givenMatrix[i + 1][j - 1];   //haut droite
            sumH += 0 * givenMatrix[i + 1][j];     //centre droite
            sumH += 1 * givenMatrix[i + 1][j + 1];   //bas droite
            meanH = std::floor(abs(sumH) * 255 / 1020);

            resM[i][j] = (byte) meanH;
        }
    }
    return resM;
}

/**
 * Separe les composantes R,G et B en 3 matrices distinctes.
 * Applique les masques de Sobel sur chacune d'entre elles.
 * Réassemble les 3 matrices pour format une image pgm avec un masque de sobel
 * @return
 */
byte **Image::sobelMaskComponent(byte **givenMatrix) {
    byte **output = initMatrix(_nbBytesHeight, _nbBytesWidth);
    byte **matrixRed = initMatrix(_nbPixelsHeight, _nbPixelsWidth);
    byte **matrixGreen = initMatrix(_nbPixelsHeight, _nbPixelsWidth);
    byte **matrixBlue = initMatrix(_nbPixelsHeight, _nbPixelsWidth);

    long idxWidth = 0;
    long idxHeight = 0;
    for (long i = 0; i < _nbPixelsHeight; i = i + 1) {
        for (long j = 0; j < _nbPixelsWidth; j = j + 1) {
            matrixRed[idxHeight][idxWidth] = givenMatrix[i][3 * j + 0];
            matrixGreen[idxHeight][idxWidth] = givenMatrix[i][3 * j + 1];
            matrixBlue[idxHeight][idxWidth] = givenMatrix[i][3 * j + 2];
            idxWidth = idxWidth + 1;
        }
        idxWidth = 0;
        idxHeight = idxHeight + 1;
    }
    // P5 because each pixel is one byte.
    byte **matrixRedSobel = sobelMask("P5", matrixRed);
    byte **matrixGreenSobel = sobelMask("P5", matrixGreen);
    byte **matrixBlueSobel = sobelMask("P5", matrixBlue);


    for (long i = 0; i < _nbPixelsHeight; i = i + 1) {
        for (long j = 0; j < _nbPixelsWidth; j = j + 1) {
            output[i][3 * j + 0] = matrixRedSobel[i][j];
            output[i][3 * j + 1] = matrixGreenSobel[i][j];
            output[i][3 * j + 2] = matrixBlueSobel[i][j];
        }
    }

    return output;
}

byte **Image::sobelMask(string type, byte **givenMatrix) {
    if (type == "P6") {
        return sobelMaskComponent(givenMatrix);
    } else {
        byte **resM = initMatrix();

        byte **Ix = this->sobelMaskHorizontal(givenMatrix);
        byte **Iy = this->sobelMaskVertical(givenMatrix);

        for (long i = 0; i < _nbPixelsHeight; i = i + 1) {
            for (long j = 0; j < _nbPixelsWidth; j = j + 1) {
                resM[i][j] = sqrt(pow(Ix[i][j], 2) + pow(Iy[i][j], 2));
            }
        }
        return resM;
    }
}

byte **Image::sobelMask() {
    return this->sobelMask(this->_type, this->_image);
}


/**
 * We wanted to convert a PPM file to PGM using different grayscale formula.
 *
 * @param choice
 * @return
 */
byte **Image::convertPPMToPGM(int choice) {
    byte **outputMatrix = initMatrix(_nbPixelsHeight, _nbPixelsWidth);
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
    } else {
        cerr << "Not good type of file, expected PPM" << endl;
    }
    return outputMatrix;
}

byte **Image::binarisePGM(byte **givenMatrix, const long &seuil) {
    int curX, curY;
    byte **pgmMatrix = initMatrix(this->_nbPixelsHeight, this->_nbPixelsWidth);
    for (curX = 0; curX < this->_nbPixelsHeight; curX++) {
        for (curY = 0; curY < this->_nbPixelsWidth; curY++) {
            if ((long) (givenMatrix[curX][curY]) > seuil) {
                pgmMatrix[curX][curY] = 255;
            } else {
                pgmMatrix[curX][curY] = 0;
            }
        }
    }
    return pgmMatrix;
}

byte **Image::binarisePPM(byte **m, long seuil, char channel) {

    int curX, curY;
    byte **pgmMatrix = initMatrix(this->_nbBytesHeight, this->_nbPixelsWidth);
    for (curX = 0; curX < this->_nbBytesHeight; curX = curX + 1) {
        for (curY = 0; curY < _nbBytesWidth; curY = curY + 1) {
            if ((long) this->_image[curX][curY] > seuil) {
                pgmMatrix[curX][curY] = 255;// TODO
            } else {
                pgmMatrix[curX][curY] = 0;
            }
        }
    }
}

byte **Image::binarise(long seuil) {
    if (this->_type == "P6") {
        return this->binarisePPM(this->_image, seuil, 'a');
    } else if (this->_type == "P5") {
        return this->binarisePGM(this->_image, seuil);
    }
}

double Image::calculOutlineRate(byte **binarisedMatrix) {
    long totalNumberOfPixel = _nbBytesWidth * _nbPixelsHeight;
    long totalNumberOfWhitePixel = 0;
    for (long i = 0; i < _nbPixelsHeight; i = i + 1) {
        for (long j = 0; j < _nbPixelsWidth; j = j + 1) {
            if (binarisedMatrix[i][j] == 255) {
                totalNumberOfWhitePixel = totalNumberOfWhitePixel + 1;
            }
        }
    }
    if(totalNumberOfPixel==0){
        return 0;
    }
    return (double) (totalNumberOfWhitePixel *100)/ (double) totalNumberOfPixel;
}
