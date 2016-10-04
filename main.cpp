//
// Created by Dylan on 20/09/2016.
//

#include <iostream>
#include "Image.h"
#include "ImageProcessor.h"

using namespace std;

void testDetectRed(char *file);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage : first argument, input file. second argument, output file.";
    } else {
        cout << argv[1] << endl;
        Image im(argv[1]);
        ImageProcessor ip;
        struct Coordinate *redPixelPositions = new Coordinate[im._nbBytesHeight * im._nbBytesWidth];
        long nbRedPixelFound = ip.getRedPixelPositions(im, redPixelPositions);
        for (long i = 0; i < 10; i = i + 1) {
            cout << redPixelPositions[i].horizontal << "," << redPixelPositions[i].vertical << endl;
        }
        cout << endl;
    }
    return 0;
}

void testDetectRed(char *file) {
    ImageProcessor ip;
    Image im(file);
    Image interestPointsImage = ip.interestPoints(im);
    interestPointsImage.save("C:\\Users\\Dylan\\ClionProjects\\ImageManager\\imagesres\\redinwhite_points.pgm");
}
