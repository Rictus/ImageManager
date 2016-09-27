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
    cout << "Main : img: " << endl;
    im.explain();
    im.save("C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\res_im.pgm");
    Image sobel = ip.sobelMask(im);
    cout << "Main : Dim sobel: " << endl;
    sobel.explain();
    sobel.save("C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\res_sobel.pgm");
    Image sobelSeuil = ip.binarisePGM(sobel, 30);
    cout << "Main : Dim sobel seuil : " << endl;
    sobelSeuil.explain();
    double outlineRate = ip.calculOutlineRate(sobelSeuil);
    cout << "OUTLINE RATE : " << outlineRate << endl;
    sobelSeuil.save("C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\res_sobelseuil.pgm");
    cout << "done" << endl;
}
