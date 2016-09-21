//
// Created by Dylan on 20/09/2016.
//

#include <iostream>
#include <sstream>
#include "Image.h"
#include "PGM.h"

using namespace std;

void loadSavePPM();

void loadSavePGM();

int main(int argc, char *argv) {
//    loadSavePGM();
//    loadSavePPM();
    char *testFile = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\images\\Route3.pgm";
    PGM pgm(testFile);
    pgm.load();
    return 0;
}

void loadSavePPM() {
    char *testFile = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\images\\route0.ppm";
    char *outputFile = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\route0.ppm";
    Image im(testFile);
}

void loadSavePGM() {
    char *testFile = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\images\\route0.pgm";
    char *outputFile = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\route0.pgm";
    Image im(testFile);
}


