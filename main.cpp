//
// Created by Dylan on 20/09/2016.
//

#include <iostream>
#include "Image.h"

using namespace std;

void loadSavePPM(char *inputFile, char *outputFile);

void loadSavePGM(char *inputFile, char *outputFile);

void histogram(char *inputFile);

void histogramPPM(char *inputFile);

void bhatDistance (char *inputFile1, char *inputFile2);


void loadPPMSavePGM();

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage : first argument, input file. second argument, output file.";
    } else {
        //loadSavePGM(argv[1], argv[2]);
        bhatDistance(argv[1], argv[2]);

    }
    return 0;
}

void histogram(char *inputFile){
    Image im(inputFile);
    im.load();
    im.histogram();
}

void bhatDistance (char *inputFile1, char *inputFile2){

    int *hist1 [255];
    int *hist2 [255];
    double scoreFinal;

    Image image1(inputFile1);
    image1.load();

    *hist1 = image1.histogram();

    Image image2(inputFile2);
    image2.load();

    *hist2 = image2.histogram();


    scoreFinal = image1.bhattacharyya(*hist1, *hist2);

    cout << scoreFinal << endl;
}

void histogramPPM(char *inputFile){
    Image im(inputFile);
    im.load();
    im.histogramPPM();
}

void loadSavePPM(char *inputFile, char *outputFile) {
    Image im(inputFile);
    im.load();
    byte **sobel = im.sobelMask();
    im.save(outputFile, sobel);
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