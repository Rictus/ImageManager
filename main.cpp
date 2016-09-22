//
// Created by Dylan on 20/09/2016.
//

#include <iostream>
#include "Image.h"

using namespace std;

void loadSavePPM();

void loadSavePGM();


void loadPPMSavePGM();

int main(int argc, char *argv[]) {
    loadSavePGM();
    loadSavePPM();
//    loadPPMSavePGM();

    return 0;
}

void loadSavePPM() {
    char *testFile = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\images\\Route2.ppm";
    char *outputFile = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\Route2_Sobel.ppm";
    char *outputFileSobelH = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\Route3_SobelH.ppm";
    char *outputFileSobelV = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\Route3_SobelV.ppm";
    Image im(testFile);
    im.load();
    byte **sHor = im.sobelMaskHorizontal();
    byte **sVer = im.sobelMaskVertical();
    byte **sobel = im.sobelMask();
    im.save(outputFileSobelH, sHor);
    im.save(outputFileSobelV, sVer);
    im.save(outputFile, sobel);
}

void loadSavePGM() {/*
    char *testFile = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\images\\rice.pgm";
    char *outputFile = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\rice_Sobel.pgm";
    char *outputFileSobelH = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\rice_SobelH.pgm";
    char *outputFileSobelV = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\rice_SobelV.pgm";
    //*/

    char *testFile = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\images\\route3.pgm";
    char *outputFile = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\route3.pgm";
    char *outputFileSobelH = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\route3_SobelH.pgm";
    char *outputFileSobelV = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\route3_SobelV.pgm";
    Image im(testFile);
    im.load();
    byte **sHor = im.sobelMaskHorizontal();
    byte **sVer = im.sobelMaskVertical();
    byte **sobel = im.sobelMask();
    im.save(outputFileSobelH, sHor);
    im.save(outputFileSobelV, sVer);
    im.save(outputFile, sobel);
}

void loadPPMSavePGM() {
    char *testFile = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\images\\route4.ppm";
    char *outputFile = (char *) "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\route4conv.pgm";

    Image im(testFile);
    im.load();
    byte **out = im.convertPPMToPGM();
    im.save(outputFile, out, 256, 256);

}