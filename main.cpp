//
// Created by Dylan on 20/09/2016.
//

#include <iostream>
#include <cstring>
#include "Image.h"
#include "ImageProcessor.h"

using namespace std;

void testSaveInformations(char *inputFile, char *outputFile);

void testPPM(char *inputFile);

void testSetOfPPMs();

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage : first argument, input file. second argument, output file.";
    } else {
//        testSaveInformations(argv[1], argv[2]);
//        testPPM(argv[1]);
        testSetOfPPMs();
    }
    return 0;
}

void testSetOfPPMs() {
    char *directoryPath = "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\images\\set\\";
    char *outputDirectoryPath = "C:\\Users\\Dylan\\ClionProjects\\ImageManager\\textImages\\set\\";
    char *filenames[] = {
            "14.ppm",
            "16.ppm",
            "19.ppm",
            "27.ppm",
            "32.ppm",
            "35.ppm",
            "57.ppm",
            "64.ppm",
            "92.ppm",
            "133.ppm",
            "176.ppm",
            "225.ppm",
            "407.ppm",
            "466.ppm"
    };
    char *outputFilenames[] = {
            "14.txt",
            "16.txt",
            "19.txt",
            "27.txt",
            "32.txt",
            "35.txt",
            "57.txt",
            "64.txt",
            "92.txt",
            "133.txt",
            "176.txt",
            "225.txt",
            "407.txt",
            "466.txt"
    };
    char path[100];
    char outputPath[100];
    for (int i = 0; i < 14; i++) {
        strcpy(path, directoryPath);
        strcat(path, filenames[i]);

        strcpy(outputPath, outputDirectoryPath);
        strcat(outputPath, outputFilenames[i]);

        Image im(path);
        im.saveImageInformations(outputPath);

        cout << path << endl;
        cout << outputPath << endl << endl << endl;
    }
}

void testSaveInformations(char *inputFile, char *outputFile) {
    ImageProcessor ip;
    Image im(inputFile);
    im.saveImageInformations("C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\res_sobelseuil.txt");
}

void testPPM(char *inputFile) {
    ImageProcessor ip;
    Image im(inputFile);
    Image sobel = ip.sobelMask(im);
    Image sobelSeuil = ip.binarise(sobel, 50);
    im.save("C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\res.ppm");
    sobel.save("C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\res_sobel.ppm");
    sobelSeuil.save("C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\res_sobelseuil.ppm");
    double *rateComponents = ip.getComponentsRatesFromHSV(im);
    rateComponents = ip.getComponentsRatesFromRGB(im);
}