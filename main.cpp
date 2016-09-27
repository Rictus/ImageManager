//
// Created by Dylan on 20/09/2016.
//

#include <iostream>
#include "Image.h"
#include "ImageProcessor.h"

using namespace std;

void loadSavePGM(char *inputFile, char *outputFile);


int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage : first argument, input file. second argument, output file.";
    } else {
        loadSavePGM(argv[1], argv[2]);

    }
    return 0;
}

void loadSavePGM(char *inputFile, char *outputFile) {
    ImageProcessor ip;
    Image im(inputFile);
    im.load();
    Image sobel = ip.sobelMask(im);
    Image sobelSeuil = ip.binarisePGM(sobel, 30);
    double outlineRate = ip.calculOutlineRate(sobelSeuil);
    int* hist1 = ip.histogram(im);
    int* hist2 = ip.histogram(im);
    float a = ip.bhattacharyya(hist1, hist2);
    cout << "bhattacharyya say : " << a << endl;
    cout << "outline rate : " << outlineRate << "%" << endl;
    sobelSeuil.save("C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\res_sobelseuil.pgm");
}
