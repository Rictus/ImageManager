//
// Created by Dylan on 20/09/2016.
//

#include <iostream>
#include "Image.h"

using namespace std;

void loadSavePPM(char *inputFile, char *outputFile);

void loadSavePGM(char *inputFile, char *outputFile);


void loadPPMSavePGM();

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage : first argument, input file. second argument, output file.";
    } else {
        loadSavePGM(argv[1], argv[2]);
    }
    return 0;
}

void loadSavePPM(char *inputFile, char *outputFile) {
}

void loadSavePGM(char *inputFile, char *outputFile) {
    Image im(inputFile);
    im.load();
    byte **sobel = im.sobelMask();
    byte **sobelSeuil = im.binarisePGM(sobel,30);
    double outlineRate = im.calculOutlineRate(sobelSeuil);
    cout << "OUTLINE RATE : " << outlineRate << endl;
    im.save("C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\res_sobelseuil.ppm", sobelSeuil);
}

void loadPPMSavePGM(char *inputFile, char *outputFile) {
    Image im(inputFile);
    im.load();
    byte **out = im.convertPPMToPGM();
    im.save(outputFile, out);
}