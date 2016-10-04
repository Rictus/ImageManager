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
        struct ImageCoordinate *redPixelPositions = new struct ImageCoordinate[im._nbPixelsHeight * im._nbPixelsWidth];
        long nbRedPixelFound = ip.getRedPixelPositions(im, redPixelPositions);
        for (long i = 0; i < nbRedPixelFound; i = i + 1) {
            im._image[redPixelPositions[i].vertical][3 * redPixelPositions[i].horizontal] = 0;
            im._image[redPixelPositions[i].vertical][3 * redPixelPositions[i].horizontal + 1] = 0;
            im._image[redPixelPositions[i].vertical][3 * redPixelPositions[i].horizontal + 2] = 0;
        }//*/
        ImageCoordinate barycenter = ip.getBarycenterOfPoints(redPixelPositions, (int) nbRedPixelFound);
        cout << "Barycenter : (x,y)=(" << barycenter.horizontal << ", " << barycenter.vertical << ") " << endl;
        im.save(argv[2]);
        cout << endl;
    }
    return 0;
}