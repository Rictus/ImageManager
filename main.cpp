//
// Created by Dylan on 20/09/2016.
//

#include <iostream>
#include "Image.h"
#include "ImageProcessor.h"

using namespace std;

void testSaveInformations(char *inputFile, char *outputFile);

void testPPM(char *inputFile);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage : first argument, input file. second argument, output file.";
    } else {
//        testSaveInformations(argv[1], argv[2]);
        testPPM(argv[1]);
    }
    return 0;
}

void testSaveInformations(char *inputFile, char *outputFile) {
    ImageProcessor ip;
    Image im(inputFile);
    im.load();
    im.saveImageInformations("C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\res_sobelseuil.txt");
}

void testPPM(char *inputFile) {
    ImageProcessor ip;
    Image im(inputFile);
    im.load();
    Image test = ip.sobelMask(im);
    test = ip.binarise(test, 50);
    test.save("C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\res.ppm");
}
