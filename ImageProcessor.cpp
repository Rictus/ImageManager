//
// Created by Dylan on 27/09/2016.
//

#include "ImageProcessor.h"
#include "ImageUtils.h"

Image ImageProcessor::sobelMaskHorizontal(Image &img) {
    long sumH;
    double meanH;
    Image output(img._type, img._nbPixelsHeight, img._nbPixelsWidth);
    for (long i = 1; i < img._nbPixelsHeight - 1; i = i + 1) {
        for (long j = 1; j < img._nbPixelsWidth - 1; j = j + 1) {
            sumH = 0;

            //gauche
            sumH += -1 * img._image[i - 1][j - 1];   //haut gauche
            sumH += -2 * img._image[i - 1][j];     //centre gauche
            sumH += -1 * img._image[i - 1][j + 1];   //bas gauche

            //centre
            sumH += 0 * img._image[i][j - 1];     //haut centre
            sumH += 0 * img._image[i][j];       //centre centre
            sumH += 0 * img._image[i][j + 1];     //bas centre

            //droite
            sumH += 1 * img._image[i + 1][j - 1];   //haut droite
            sumH += 2 * img._image[i + 1][j];     //centre droite
            sumH += 1 * img._image[i + 1][j + 1];   //bas droite
            meanH = std::floor(abs(sumH) * 256 / 1020);

            output._image[i][j] = (byte) meanH;
        }
    }
    return output;
}

Image ImageProcessor::sobelMaskVertical(Image &img) {
    long sumV;
    double meanV;
    Image output(img._type, img._nbPixelsHeight, img._nbPixelsWidth);
    for (long i = 1; i < img._nbPixelsHeight - 1; i = i + 1) {
        for (long j = 1; j < img._nbPixelsWidth - 1; j = j + 1) {
            sumV = 0;

            //gauche
            sumV += -1 * img._image[i - 1][j - 1];   //haut gauche
            sumV += 0 * img._image[i - 1][j];     //centre gauche
            sumV += 1 * img._image[i - 1][j + 1];   //bas gauche

            //centre
            sumV += -2 * img._image[i][j - 1];     //haut centre
            sumV += 0 * img._image[i][j];       //centre centre
            sumV += 2 * img._image[i][j + 1];     //bas centre

            //droite
            sumV += -1 * img._image[i + 1][j - 1];   //haut droite
            sumV += 0 * img._image[i + 1][j];     //centre droite
            sumV += 1 * img._image[i + 1][j + 1];   //bas droite
            meanV = std::floor(abs(sumV) * 256 / 1020);

            output._image[i][j] = (byte) meanV;
        }
    }
    return output;
}

/**
 * Separe les composantes R,G et B en 3 matrices distinctes.
 * Applique les masques de Sobel sur chacune d'entre elles.
 * Réassemble les 3 matrices pour format une image pgm avec un masque de sobel
 * @return
 */
Image ImageProcessor::sobelMaskComponent(Image &img) {
    Image output = Image(ImageType::P6, img._nbPixelsHeight, img._nbPixelsWidth);
    // P5 because each pixel is one byte.
    Image imageRed = Image(ImageType::P5, img._nbBytesHeight, img._nbBytesWidth);
    Image imageGreen = Image(ImageType::P5, img._nbBytesHeight, img._nbBytesWidth);
    Image imageBlue = Image(ImageType::P5, img._nbBytesHeight, img._nbBytesWidth);

    long idxWidth = 0;
    long idxHeight = 0;
    for (long i = 0; i < img._nbPixelsHeight; i = i + 1) {
        for (long j = 0; j < img._nbPixelsWidth; j = j + 1) {
            imageRed._image[idxHeight][idxWidth] = img._image[i][3 * j + 0];
            imageGreen._image[idxHeight][idxWidth] = img._image[i][3 * j + 1];
            imageBlue._image[idxHeight][idxWidth] = img._image[i][3 * j + 2];
            idxWidth = idxWidth + 1;
        }
        idxWidth = 0;
        idxHeight = idxHeight + 1;
    }

    imageRed = this->sobelMask(ImageType::P5, imageRed);
    imageGreen = this->sobelMask(ImageType::P5, imageGreen);
    imageBlue = this->sobelMask(ImageType::P5, imageBlue);

    for (long i = 0; i < img._nbPixelsHeight; i = i + 1) {
        for (long j = 0; j < img._nbPixelsWidth; j = j + 1) {
            output._image[i][3 * j + 0] = imageRed._image[i][j];
            output._image[i][3 * j + 1] = imageGreen._image[i][j];
            output._image[i][3 * j + 2] = imageBlue._image[i][j];
        }
    }
    return output;
}

Image ImageProcessor::sobelMask(ImageType type, Image &img) {
    if (type == ImageType::P6) {
        return sobelMaskComponent(img);
    } else {
        Image output(type, img._nbPixelsHeight, img._nbPixelsWidth);

        Image imX = this->sobelMaskHorizontal(img);
        Image imY = this->sobelMaskVertical(img);
        for (long i = 0; i < img._nbPixelsHeight; i = i + 1) {
            for (long j = 0; j < img._nbPixelsWidth; j = j + 1) {
                output._image[i][j] = sqrt(pow(imX._image[i][j], 2) + pow(imY._image[i][j], 2));
            }
        }
        return output;
    }
}

Image ImageProcessor::sobelMask(Image &img) {
    return ImageProcessor::sobelMask(img._type, img);
}

/**
 * We wanted to convert a PPM file to PGM using different grayscale formula.
 *
 * @param algorithm
 * @return
 */
Image ImageProcessor::convertPPMToPGM(GrayscaleConvertionAlgorithm algorithm, Image &img) {
    Image output = Image(ImageType::P5, img._nbPixelsHeight, img._nbPixelsWidth);
    if (img._type == ImageType::P6) {
        byte outputByte;
        for (long i = 0; i < img._nbPixelsHeight; i = i + 1) {
            for (long j = 0; j < img._nbPixelsWidth; j = j + 1) {
                int r = img._image[i][3 * j + 0];
                int g = img._image[i][3 * j + 1];
                int b = img._image[i][3 * j + 2];
                if (algorithm == GrayscaleConvertionAlgorithm::LIGHTNESS) {
                    outputByte = (byte) ((max(max(r, g), b) + min(min(r, g), b)) / 2);
                } else if (algorithm == GrayscaleConvertionAlgorithm::AVERAGE) {
                    outputByte = (byte) ((r + g + b) / 3);
                } else if (algorithm == GrayscaleConvertionAlgorithm::LUMINOSITY) {
                    outputByte = (byte) (0.21 * r + 0.72 * g + 0.07 * b);
                } else {
                    outputByte = 0;
                }
                output._image[i][j] = outputByte;
            }
        }
    } else {
        cerr << "Not good type of file, expected PPM" << endl;
    }
    return output;
}

Image ImageProcessor::binarisePGM(Image &img, const long &seuil) {
    int curX, curY;
    Image output(ImageType::P5, img._nbPixelsHeight, img._nbPixelsWidth);
    for (curX = 0; curX < img._nbPixelsHeight; curX++) {
        for (curY = 0; curY < img._nbPixelsWidth; curY++) {
            if ((long) (img._image[curX][curY]) > seuil) {
                output._image[curX][curY] = Color::WHITE;
            } else {
                output._image[curX][curY] = Color::BLACK;
            }
        }
    }
    return output;
}

Image ImageProcessor::binarisePPM(Image &img, long seuil) {
    Image pgmImage = this->convertPPMToPGM(GrayscaleConvertionAlgorithm::LIGHTNESS, img);
    return this->binarisePGM(pgmImage, seuil);
}

Image ImageProcessor::binarise(Image &img, long seuil) {
    if (img._type == ImageType::P6) {
        return this->binarisePPM(img, seuil);
    } else if (img._type == ImageType::P5) {
        return this->binarisePGM(img, seuil);
    }
}

double ImageProcessor::calculOutlineRate(Image &m) {
    long totalNumberOfPixel = m._nbPixelsWidth * m._nbPixelsHeight;
    long totalNumberOfWhitePixel = 0;
    for (long i = 0; i < m._nbPixelsHeight; i = i + 1) {
        for (long j = 0; j < m._nbPixelsWidth; j = j + 1) {
            if (m._image[i][j] == Color::BLACK) {
                totalNumberOfWhitePixel = totalNumberOfWhitePixel + 1;
            }
        }
    }
    if (totalNumberOfPixel == 0) {
        return 0;
    }
    return (double) (totalNumberOfWhitePixel * 100) / (double) totalNumberOfPixel;
}

int *ImageProcessor::histogram(Image &img) {
    for (int i = 0; i < 256; i++) {
        img._histogram[i] = 0;
    }

    for (long i = 0; i < img._nbPixelsHeight; i = i + 1) {
        for (long j = 0; j < img._nbPixelsWidth; j = j + 1) {
            byte pixel = img._image[i][j];
            int intPixel = (int) pixel;
            img._histogram[intPixel] = img._histogram[intPixel] + 1;

        }
    }
    return img._histogram;
}

void ImageProcessor::histogramPPM(Image &img) {
    for (int i = 0; i < 256; i++) {
        img._histogramR[i] = 0;
        img._histogramG[i] = 0;
        img._histogramB[i] = 0;
    }

    /***THIS COULD BE OPTIMIZE IN ONE LOOP**/
    for (long i = 0; i < img._nbPixelsHeight; i = i + 3) {
        for (long j = 0; j < img._nbPixelsWidth; j = j + 3) {
            byte pixel = img._image[i][j];
            int intPixel = (int) pixel;
            img._histogramR[intPixel]++;
        }
    }

    for (long i = 0; i < img._nbPixelsHeight; i = i + 3) {
        for (long j = 1; j < img._nbPixelsWidth; j = j + 3) {
            byte pixel = img._image[i][j];
            int intPixel = (int) pixel;
            img._histogramG[intPixel]++;
        }
    }

    for (long i = 0; i < img._nbPixelsHeight; i = i + 3) {
        for (long j = 2; j < img._nbPixelsWidth; j = j + 3) {
            byte pixel = img._image[i][j];
            int intPixel = (int) pixel;
            img._histogramB[intPixel]++;
        }
    }
}

float ImageProcessor::mean(int *histogram) {
    float mean;
    double sum = 0;
    for (int i = 0; i < 256; ++i) {
        cout << histogram[i] << ' ' << endl;
        sum = sum + histogram[i];
    }

    mean = (float) (sum / 256.0);

    return mean;
}

float ImageProcessor::bhattacharyya(int *hist1, int *hist2) {

    float meanHist1;
    float meanHist2;

    float score = 0;
    float firstTerm;
    double secondTerm = 0;

    meanHist1 = mean(hist1);
    meanHist2 = mean(hist2);
    firstTerm = sqrt(meanHist1 * meanHist2 * pow(256, 2));

    for (int i = 0; i < 256; i = i + 1) {
        secondTerm = secondTerm + sqrt((double) hist1[i] * (double) hist2[i]);
    }

    score = (float) sqrt(abs(1 - (1 / firstTerm) * secondTerm));

    return score;
}

double *ImageProcessor::getComponentsRatesFromHSV(Image &img) {
    double *componentRates = new double[3];
    int idxRedComponent = 0;
    int idxGreenComponent = 1;
    int idxBlueComponent = 2;
    int r, g, b;
    int maxValueComponent = 255;
    float denominator;
    float Hue = 0;
    float saturation = 0;//TODO We could use saturation/lightness to escape from white/black
    float lightness = 0;

    componentRates[idxRedComponent] = 0;
    componentRates[idxBlueComponent] = 0;
    componentRates[idxGreenComponent] = 0;

    for (int i = 0; i < img._nbBytesHeight; i++) {
        for (int j = 0; j < img._nbBytesWidth; j = j + 3) {
            r = img._image[i][j + 0];
            g = img._image[i][j + 1];
            b = img._image[i][j + 2];
            /**Hue calculation. See : http://www.rapidtables.com/convert/color/rgb-to-hsv.htm**/
            int *HSVTable = RGBToHSV(r, g, b);
            Hue = HSVTable[0];
            saturation = HSVTable[1];
            lightness = HSVTable[2];


//            cout << endl;
            /**Red Component**/
            if ((Hue > 340 || Hue < 7) && lightness > 125 && saturation > 100) {
                componentRates[idxRedComponent] = componentRates[idxRedComponent] + r;
            }
            /**Green Component**/
            if (Hue > 86 && Hue < 152) {
                componentRates[idxGreenComponent] = componentRates[idxGreenComponent] + g;
            }
            /**Blue Component**/
            if (Hue > 163 && Hue < 256) {
                componentRates[idxBlueComponent] = componentRates[idxBlueComponent] + b;
            }
        }
    }

    denominator = (img._nbPixelsHeight * img._nbPixelsWidth * (float) maxValueComponent);

    componentRates[idxRedComponent] = (componentRates[idxRedComponent] * 100.0) / denominator;
    componentRates[idxGreenComponent] = (componentRates[idxGreenComponent] * 100.0) / denominator;
    componentRates[idxBlueComponent] = (componentRates[idxBlueComponent] * 100.0) / denominator;

    return componentRates;
}

double *ImageProcessor::getComponentsRatesFromRGB(Image &img) {
    double *componentRates = new double[3];
    int idxRedComponent = 0;
    int idxGreenComponent = 1;
    int idxBlueComponent = 2;
    int r, g, b;
    int maxValueComponent = 255;
    int seuil = 80;
    float denominator;
    componentRates[idxRedComponent] = 0;
    componentRates[idxGreenComponent] = 0;
    componentRates[idxBlueComponent] = 0;

    for (int i = 0; i < img._nbBytesHeight; i++) {
        for (int j = 0; j < img._nbBytesWidth; j = j + 3) {
            r = img._image[i][j + 0];
            g = img._image[i][j + 1];
            b = img._image[i][j + 2];
            if (r > 150 && g > 150 && b > 150) {
                // White color
            } else if (r < 50 && g < 50 && b < 50) {
                // Black color
            } else {
                /**Red Component**/
                if (r > 100 && g + b < 200) {
                    componentRates[idxRedComponent] = componentRates[idxRedComponent] + r;
                }
                /**Green Component**/
                if (g > 100 && r + b < 200) {
                    componentRates[idxGreenComponent] = componentRates[idxGreenComponent] + g;
                }
                /**Blue Component**/
                if (b > 100 && r + g < 200) {
                    componentRates[idxBlueComponent] = componentRates[idxBlueComponent] + b;
                }
            }
        }
    }

    denominator = (img._nbPixelsHeight * img._nbPixelsWidth * (float) maxValueComponent);
    componentRates[idxRedComponent] = (componentRates[idxRedComponent] * 100.0) / denominator;
    componentRates[idxGreenComponent] = (componentRates[idxGreenComponent] * 100.0) / denominator;
    componentRates[idxBlueComponent] = (componentRates[idxBlueComponent] * 100.0) / denominator;

    return componentRates;
}

Image ImageProcessor::interestPoints(Image &img) { //Do not work for PGM for now...

    long sumH, sumV, sumN;
    double Ix, Iy;
    //      <Ix²>      <Iy²>
    double IConvHor, IConvVer;
    double IConvHorSquare, IConvVerSquare;
    double k;
//    Image imgProcess = Image(img);
//    if (img._type == ImageType::P6) {
    Image imgProcess = this->convertPPMToPGM(GrayscaleConvertionAlgorithm::LUMINOSITY, img);
//    }

    for (int i = 1; i < imgProcess._nbPixelsHeight - 1; i++) {
        for (int j = 1; j < imgProcess._nbPixelsWidth - 1; j++) {
            sumH = 0;
            sumV = 0;

            /**Gradient Horizontal**/
            //gauche
            sumH += -1 * imgProcess._image[i - 1][j - 1];   //haut
            sumH += -2 * imgProcess._image[i - 1][j];     //centre
            sumH += -1 * imgProcess._image[i - 1][j + 1];   //bas

            //centre
            sumH += 0 * imgProcess._image[i][j - 1];     //haut
            sumH += 0 * imgProcess._image[i][j];       //centre
            sumH += 0 * imgProcess._image[i][j + 1];     //bas

            //droite
            sumH += 1 * imgProcess._image[i + 1][j - 1];   //haut
            sumH += 2 * imgProcess._image[i + 1][j];     //centre
            sumH += 1 * imgProcess._image[i + 1][j + 1];   //bas
            Ix = std::floor(abs(sumH) * 256.0 / 1020.0);

            /**Gradient Vertical**/
            sumN = 0;
            //gauche
            sumV += -1 * img._image[i - 1][j - 1];   //haut gauche
            sumV += 0 * img._image[i - 1][j];     //centre gauche
            sumV += 1 * img._image[i - 1][j + 1];   //bas gauche

            //centre
            sumV += -2 * img._image[i][j - 1];     //haut centre
            sumV += 0 * img._image[i][j];       //centre centre
            sumV += 2 * img._image[i][j + 1];     //bas centre

            //droite
            sumV += -1 * img._image[i + 1][j - 1];   //haut droite
            sumV += 0 * img._image[i + 1][j];     //centre droite
            sumV += 1 * img._image[i + 1][j + 1];   //bas droite
            Iy = std::floor(abs(sumV) * 256 / 1020);

            /**Convolution avec le voisinage (Ix:Gradient horizontal) : <Ix²>**/
            sumN = 0;
            //gauche
            sumN += 1 * Ix * Ix;
            sumN += 1 * Ix * Ix;
            sumN += 1 * Ix * Ix;

            //centre
            sumN += 1 * Ix * Ix;
            sumN += 0 * Ix * Ix;
            sumN += 1 * Ix * Ix;

            //droite
            sumN += 1 * Ix * Ix;
            sumN += 1 * Ix * Ix;
            sumN += 1 * Ix * Ix;
            IConvHorSquare = std::floor(abs(sumN) * 256 / (8.0 * 255.0));

            /**Convolution avec le voisinage (Ix:Gradient vertical) : <Iy²>**/
            //gauche
            sumN += 1 * Iy * Iy;
            sumN += 1 * Iy * Iy;
            sumN += 1 * Iy * Iy;

            //centre
            sumN += 1 * Iy * Iy;
            sumN += 0 * Iy * Iy;
            sumN += 1 * Iy * Iy;

            //droite
            sumN += 1 * Iy * Iy;
            sumN += 1 * Iy * Iy;
            sumN += 1 * Iy * Iy;
            IConvVerSquare = std::floor(abs(sumN) * 256 / (8.0 * 255.0));


            /**Convolution avec le voisinage (Ix:Gradient horizontal) : <Ix>**/
            sumN = 0;
            //gauche
            sumN += 1 * Ix;
            sumN += 1 * Ix;
            sumN += 1 * Ix;

            //centre
            sumN += 1 * Ix;
            sumN += 0 * Ix;
            sumN += 1 * Ix;

            //droite
            sumN += 1 * Ix;
            sumN += 1 * Ix;
            sumN += 1 * Ix;
            IConvHor = std::floor(abs(sumN) * 256 / (8.0 * 255.0));

            /**Convolution avec le voisinage (Ix:Gradient vertical) : <Iy>**/
            //gauche
            sumN += 1 * Iy;
            sumN += 1 * Iy;
            sumN += 1 * Iy;

            //centre
            sumN += 1 * Iy;
            sumN += 0 * Iy;
            sumN += 1 * Iy;

            //droite
            sumN += 1 * Iy;
            sumN += 1 * Iy;
            sumN += 1 * Iy;
            IConvVer = std::floor(abs(sumN) * 256 / (8.0 * 255.0));

            k = Ix * Ix * IConvVerSquare + Iy * Iy * IConvHorSquare - 2 * Ix * Iy * IConvHor * IConvVer;
            k = k / (IConvHorSquare + IConvVerSquare);

            if (!isnan(k) && k > 5000) {
                imgProcess._image[i][j] = 0;
                cout << "At (" << j << ", " << i << ") : k=" << k << endl;
            }
        }
    }
    return imgProcess;
}

long ImageProcessor::getRedPixelPositions(Image &img, ImageCoordinate *redPixelPositions) {
    int H = 0, S = 0, V = 0, R = 0, G = 0, B = 0;
    int *HSVTable = new int[3];
//    redPixelPositions = new ImageCoordinate[img._nbPixelsHeight * img._nbPixelsWidth];
    long nbRedPixelFound = 0;
    if (img._type != ImageType::P6) {
        cerr << "ImageProcessor::getRedPixelPositions : Can't process non-ppm image : Need ppm." << endl;
    }

    for (int i = 0; i < img._nbPixelsHeight; i++) {
        for (int j = 0; j < img._nbPixelsWidth; j++) {
            R = img._image[i][3 * j + 0];
            G = img._image[i][3 * j + 1];
            B = img._image[i][3 * j + 2];
            HSVTable = RGBToHSV(R, G, B);
            H = HSVTable[0];
            S = HSVTable[1];
            V = HSVTable[2];

            if (isColor_Hardcoded(H, S, V, Color::RED)) {
                redPixelPositions[nbRedPixelFound] = {horizontal:(long) j, vertical:(long) i};
                nbRedPixelFound = nbRedPixelFound + 1;
            }
        }
    }
    return nbRedPixelFound;
}

ImageCoordinate ImageProcessor::getBarycenterOfPoints(ImageCoordinate *points, int nbPoints) {
    ImageCoordinate barycenter;

    long sumX = 0, sumY = 0;
    double meanX, meanY;

    for (int i = 0; i < nbPoints; i++) {
        double a = points[i].horizontal;
        double b = points[i].vertical;
        sumX += points[i].horizontal;
        sumY += points[i].vertical;
    }

    meanX = sumX / (float) nbPoints;
    meanY = sumY / (float) nbPoints;

    barycenter = {horizontal:(long) meanX, vertical:(long) meanY};
    return barycenter;
}
