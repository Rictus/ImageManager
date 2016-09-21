//
// Created by Dylan on 21/09/2016.
//

#ifndef IMAGEMANAGER_IMAGEFORMATEXCEPTION_H
#define IMAGEMANAGER_IMAGEFORMATEXCEPTION_H

class ImageFormatException {
public:
    const string type;
    const string filename;

    ImageFormatException(const string &type, const string &filename) : type(type), filename(filename) {}
};
#endif //IMAGEMANAGER_IMAGEFORMATEXCEPTION_H
