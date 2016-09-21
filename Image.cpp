//
// Created by Dylan on 20/09/2016.
//

#include <fstream>
#include "Image.h"
#include <sstream>
#include "FileException.h"

Image::Image(char *_filename) : _filename(_filename) {
    _width = 0;
    _height = 0;
    fstream _file(_filename, ios_base::in | ios_base::out | ios_base::binary);
    if (!_file) {
        throw FileException(_filename);
    } else {
        this->close();
    }
    this->readHeader();
}

void Image::readHeader() {
    _imageReader.open(_filename, fstream::in | fstream::out | fstream::binary);
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
                    this->_width = stol(token);
                    getline(iss, token, ' ');
                    this->_height = stol(token);
                    order++;
                    break;
                }
                case 2: {
                    //Don't use this one // TODO We need to get this to write it to output file
                    this->_gris = stol(inputLine);
                    order++;
                }
                    break;
                default:
                    break;
            }
        }
    }
}

string Image::filename() {
    return _filename;
}

void Image::close() {
    _imageReader.close();
}

ofstream Image::writeHeader(string outputFilename) {
    ofstream imageWriter;
    imageWriter.open(outputFilename, std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);
    imageWriter << this->_type << endl;
    imageWriter << this->_width + " " + this->_height << endl;
    imageWriter << this->_gris << endl;

    return imageWriter;
}

