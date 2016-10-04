//
// Created by Dylan on 20/09/2016.
//

#include <iomanip>
#include "Image.h"
#include "ImageProcessor.h"

using namespace std;

Image::Image() {}

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
    initImageMatrix();
    initHistoArrays();
    load();
}

Image::Image(ImageType type, long height, long width, byte **matrix) {
    this->_image = matrix;
    Image(type, height, width);
}

Image::Image(ImageType type, long height, long width) {
    _type = type;
    _nbPixelsHeight = height;
    _nbPixelsWidth = width;
    if (this->_type == ImageType::P5) {
        _nbBytesHeight = height;
        _nbBytesWidth = width;
    } else if (this->_type == ImageType::P6) {
        // * 3 because a pixel is composed of 3 bytes (rgb)
        _nbBytesHeight = height * 3;
        _nbBytesWidth = width * 3;
    } else {
        cerr << "Unknown file type : " << this->_type;
    }
    initImageMatrix();
    initHistoArrays();
}

void Image::readHeader() {
    _imageReader.open(_filename, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    _imageReader.seekg(_NULL, std::ios_base::beg);
    string inputLine = "";

    int order = 0;
    // get each word in the header
    while (!_imageReader.eof() && order < 3) {
        getline(_imageReader, inputLine);
        if (inputLine.at(0) == '#') {
            //Ignoring commentary
        } else {
            switch (order) {
                case 0: {
                    initImageType(inputLine);
                    order++;
                    break;
                }
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
                    break;
                }
                default:
                    break;
            }
        }
    }

    if (this->_type == ImageType::P5) {
        _nbBytesHeight = this->_nbPixelsHeight;
        _nbBytesWidth = this->_nbPixelsWidth;
    } else if (this->_type == ImageType::P6) {
        // * 3 because a pixel is composed of 3 bytes (rgb)
        _nbBytesHeight = this->_nbPixelsHeight * 3;
        _nbBytesWidth = this->_nbPixelsWidth * 3;
    } else {
        cerr << "Unknown file type : " << this->_type;
    }
}

ofstream Image::writeHeader(string outputFilename) {
    std::ofstream imageWriter;
    imageWriter.open(outputFilename,
                     std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
    string strType;
    if (_type == ImageType::P6) {
        strType = "P6";
    } else if (_type == ImageType::P5) {
        strType = "P5";
    } else {
        strType = "";
    }
    imageWriter << strType << endl;
    imageWriter << this->_nbPixelsWidth << " " << this->_nbPixelsHeight << endl;
    imageWriter << this->_gris << endl;
    // The ofsteram is not closed so save() can still write data
    return imageWriter;
}

byte **Image::initMatrix(long &nbBytesHeight, long &nbBytesWidth) {
    byte **matrix = new byte *[nbBytesHeight];
    for (long i = 0; i < nbBytesHeight; i = i + 1) {
        matrix[i] = new byte[nbBytesWidth];
        for (long j = 0; j < nbBytesWidth; j = j + 1) {
            matrix[i][j] = (unsigned char) Color::BLACK;
        }
    }
    return matrix;
}

void Image::initImageMatrix() {
    this->_image = initMatrix(_nbBytesHeight, _nbBytesWidth);
}

void Image::initImageType(string basic_string) {
    if (basic_string == "P5") {
        this->_type = ImageType::P5;
    } else if (basic_string == "P6") {
        this->_type = ImageType::P6;
    }
}

void Image::close() {
    _imageReader.close();
}

void Image::load() { //No longer work properly for PPM
    byte b;
//    _imageReader.open(_filename, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
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
    cout << "saving" << endl;
    for (long i = 0; i < nbBytesHeight; i = i + 1) {
        for (long j = 0; j < nbBytesWidth; j = j + 1) {
            imageWriter << matrix[i][j];

        }
    }
    imageWriter.close();
}

void Image::save(char *outputFilename) {
    this->save(outputFilename, this->_image, this->_nbBytesHeight, this->_nbBytesWidth);
}

void Image::explain() {
    cout << "Dimension : " << endl;
    cout << "Pixels : " << _nbPixelsHeight << " " << _nbPixelsWidth << endl;
    cout << "Bytes  : " << _nbBytesHeight << " " << _nbBytesWidth << endl;
    cout << "Type : ";
    if (ImageType::P6 == _type) {
        cout << "P6" << endl;
    } else if (ImageType::P5 == _type) {
        cout << "P5" << endl;
    } else {
        cout << "unknown" << endl;
    }
}

void Image::initHistoArrays() {
    for (int i = 0; i < 256; i++) {
        _histogram[i] = 0;
        _histogramB[i] = 0;
        _histogramG[i] = 0;
        _histogramR[i] = 0;
    }
}

void Image::saveImageInformations(char *outputFilename) {
    double outlineRate;
    int *hist;
    int seuil = 100;
    std::ofstream imageWriter;
    imageWriter.open(outputFilename,
                     std::ios_base::in | std::ios_base::out | std::ios_base::trunc);

    string strType;
    if (_type == ImageType::P6) {
        strType = "P6";
    } else if (_type == ImageType::P5) {
        strType = "P5";
    } else {
        strType = "";
    }
    ImageProcessor ip;
    hist = ip.histogram(*this);
    Image sobel = ip.sobelMask(*this);
    Image sobelSeuil = ip.binarisePGM(sobel, seuil);
    outlineRate = ip.calculOutlineRate(sobelSeuil);

    double *componentsRates = ip.getComponentsRatesFromRGB(*this);

    imageWriter << strType << endl;
    imageWriter << this->_nbPixelsWidth << endl;
    imageWriter << this->_nbPixelsHeight << endl;
    imageWriter << this->_gris << endl;
//    for (int i = 0; i < 256; i++) {
//        imageWriter << hist[i] << " ";
//    }
//    imageWriter << endl;
    imageWriter << outlineRate << endl;
    imageWriter << fixed << showpoint;
    imageWriter << setprecision(4);
    imageWriter << componentsRates[0] << endl;
    imageWriter << componentsRates[1] << endl;
    imageWriter << componentsRates[2] << endl;

    imageWriter.close();
}

/*
Image Image::operator=(const Image &arg) {
    this->_nbPixelsHeight = arg._nbPixelsHeight;
    this->_nbPixelsWidth = arg._nbPixelsWidth;
    this->_nbBytesWidth = arg._nbBytesWidth;
    this->_nbBytesHeight = arg._nbBytesHeight;
    this->_image = arg._image;
    this->_gris = arg._gris;
    this->_type = arg._type;
    return *this;
}
//*/