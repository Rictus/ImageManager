//
// Created by Dylan on 20/09/2016.
//

#include <iostream>
#include "Image.h"

using namespace std;

void loadSavePPM();

void loadSavePGM();

int main(int argc, char *argv) {
    loadSavePGM();
    loadSavePPM();
    return 0;
}

void loadSavePPM() {
    char* testFile = (char *) "C:\\Users\\Dylan\\ClionProjects\\Image\\images\\route0.ppm";
    char* outputFile = (char *)"C:\\Users\\Dylan\\ClionProjects\\Image\\imagesres\\route0.ppm";
    Image im(testFile);
    im.loadPPM();
    im.savePPM(outputFile);
}

void loadSavePGM() {
    char* testFile = (char *) "C:\\Users\\Dylan\\ClionProjects\\Image\\images\\route0.pgm";
    char* outputFile = (char *)"C:\\Users\\Dylan\\ClionProjects\\Image\\imagesres\\route0.pgm";
    Image im(testFile);
    im.loadPGM();
    im.savePGM(outputFile);
}


