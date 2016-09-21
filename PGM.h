//
// Created by Dylan on 21/09/2016.
//

#ifndef IMAGEMANAGER_PGM_H
#define IMAGEMANAGER_PGM_H

#include "Image.h"

class PGM : public Image {
private:
    unsigned char **_image;
public:
    PGM(char *_filename);

    void load();

    void save(char *outputFilename);

    byte **initMatrix();

    byte **seeMatrix();
};


#endif //IMAGEMANAGER_PGM_H
