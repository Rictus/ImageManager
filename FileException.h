//
// Created by Dylan on 21/09/2016.
//

#ifndef IMAGEMANAGER_FILEEXCEPTION_H
#define IMAGEMANAGER_FILEEXCEPTION_H


class FileException {
public:
    const char *filename;

    FileException(const char *filename) : filename(filename) {}
};


#endif //IMAGEMANAGER_FILEEXCEPTION_H
