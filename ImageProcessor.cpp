//
// Created by Dylan on 27/09/2016.
//

#include "ImageProcessor.h"

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
            meanH = std::floor(abs(sumH) * 255 / 1020);

            output._image[i][j] = (byte) meanH;
        }
    }
    return output;
}

Image ImageProcessor::sobelMaskVertical(Image &img) {
    long sumH;
    double meanH;
    Image output(img._type, img._nbPixelsHeight, img._nbPixelsWidth);
    for (long i = 1; i < img._nbPixelsHeight - 1; i = i + 1) {
        for (long j = 1; j < img._nbPixelsWidth - 1; j = j + 1) {
            sumH = 0;

            //gauche
            sumH += -1 * img._image[i - 1][j - 1];   //haut gauche
            sumH += 0 * img._image[i - 1][j];     //centre gauche
            sumH += 1 * img._image[i - 1][j + 1];   //bas gauche

            //centre
            sumH += -2 * img._image[i][j - 1];     //haut centre
            sumH += 0 * img._image[i][j];       //centre centre
            sumH += 2 * img._image[i][j + 1];     //bas centre

            //droite
            sumH += -1 * img._image[i + 1][j - 1];   //haut droite
            sumH += 0 * img._image[i + 1][j];     //centre droite
            sumH += 1 * img._image[i + 1][j + 1];   //bas droite
            meanH = std::floor(abs(sumH) * 255 / 1020);

            output._image[i][j] = (byte) meanH;
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
    Image output = Image(ImageType::P6, img._nbBytesHeight, img._nbBytesWidth);
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
 * @param choice
 * @return
 */
Image ImageProcessor::convertPPMToPGM(int choice) {
    /**You should precise where this _nbPixelsHeight comes from*/
    Image output = Image(ImageType::P6, _nbPixelsHeight, _nbPixelsWidth);
    if (this->_type == ImageType::P6) {/*
        switch (choice) {
            case 0:
                auto toGreyScale = [](byte r, byte g, byte b) {
                    return (byte) ((max(r, g, b) + min(r, g, b)) / 2);
                };
                break;
            case 1:
                auto toGreyScale = [](byte r, byte g, byte b) {
                    return (byte) ((r + g + b) / 3);
                };
                break;
            case 2:
                toGreyScale = [](byte r, byte g, byte b) {
                    return (byte) ((0.21 * r) + (0.72 * g) + (0.07 * b));
                };
                break;
        }//*/
        for (long i = 0; i < _nbPixelsHeight; i = i + 1) {
            for (long j = 0; j < _nbPixelsWidth; j = j + 1) {
                byte r = this->_image[i][3 * j + 0];
                byte g = this->_image[i][3 * j + 1];
                byte b = this->_image[i][3 * j + 2];
                output._image[i][j] = (byte) r;
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
                output._image[curX][curY] = 255;
            } else {
                output._image[curX][curY] = 0;
            }
        }
    }
    return output;
}

Image ImageProcessor::binarisePPM(Image &img, long seuil, char channel) {
    int curX, curY;
    Image output(ImageType::P6, img._nbPixelsHeight, img._nbPixelsWidth);
    for (curX = 0; curX < img._nbPixelsHeight; curX++) {
        for (curY = 0; curY < img._nbPixelsWidth; curY++) {
            if ((long) (img._image[curX][curY]) > seuil) {
                output._image[curX][curY] = 255;//TODO
            } else {
                output._image[curX][curY] = 0;
            }
        }
    }
    return output;
}

Image ImageProcessor::binarise(Image &img, long seuil) {
    if (this->_type == ImageType::P6) {
        return this->binarisePPM(img, seuil, 'a');
    } else if (this->_type == ImageType::P5) {
        return this->binarisePGM(img, seuil);
    }
}

double ImageProcessor::calculOutlineRate(Image &m) {
    long totalNumberOfPixel = m._nbBytesWidth * m._nbPixelsHeight;
    long totalNumberOfWhitePixel = 0;
    for (long i = 0; i < m._nbPixelsHeight; i = i + 1) {
        for (long j = 0; j < m._nbPixelsWidth; j = j + 1) {
            if (m._image[i][j] == 255) {
                totalNumberOfWhitePixel = totalNumberOfWhitePixel + 1;
            }
        }
    }
    if (totalNumberOfPixel == 0) {
        return 0;
    }
    return (double) (totalNumberOfWhitePixel * 100) / (double) totalNumberOfPixel;
}

int *ImageProcessor::histogram() {
    for (int i = 0; i < 255; i++) {
        this->_histogram[i] = 0;
    }
/**Where dies _nb truc come from ?*/
    for (long i = 0; i < _nbPixelsHeight; i = i + 1) {
        for (long j = 0; j < _nbPixelsWidth; j = j + 1) {
            byte pixel = this->_image[i][j];
            int intPixel = (int) pixel;
            this->_histogram[intPixel]++;
        }
    }

    return _histogram;
}

void ImageProcessor::histogramPPM() {
    for (int i = 0; i < 255; i++) {
        this->_histogramR[i] = 0;
        this->_histogramG[i] = 0;
        this->_histogramB[i] = 0;
    }
/**Where dies _nb truc come from ?*/
    for (long i = 0; i < _nbPixelsHeight; i = i + 3) {
        for (long j = 0; j < _nbPixelsWidth; j = j + 3) {
            byte pixel = this->_image[i][j];
            int intPixel = (int) pixel;
            this->_histogramR[intPixel]++;
        }
    }
/**Where dies _nb truc come from ?*/

    for (long i = 0; i < _nbPixelsHeight; i = i + 3) {
        for (long j = 1; j < _nbPixelsWidth; j = j + 3) {
            byte pixel = this->_image[i][j];
            int intPixel = (int) pixel;
            this->_histogramG[intPixel]++;
        }
    }/**Where dies _nb truc come from ?*/


    for (long i = 0; i < _nbPixelsHeight; i = i + 3) {
        for (long j = 2; j < _nbPixelsWidth; j = j + 3) {
            byte pixel = this->_image[i][j];
            int intPixel = (int) pixel;
            this->_histogramB[intPixel]++;
        }
    }

/*    for(int i = 0; i<255; i++){
        cout << this->_histogramR[i]<<"_"<<endl;
    }
    cout << "------------------------------" <<endl;

    for(int i = 0; i<255; i++){
        cout << this->_histogramG[i]<<"_"<<endl;
    }

    cout << "------------------------------" <<endl;

    for(int i = 0; i<255; i++){
        cout << this->_histogramB[i]<<"_"<<endl;
    }
*/
}

float ImageProcessor::mean(int *histogram) {
    float mean = 0.0;
    for (int i = 0; i < 255; ++i) {
        mean += i;
        mean /= 255;
    }
    return mean;
}

double ImageProcessor::bhattacharyya(int *hist1, int *hist2) {

    //the less the score is, the more histograms are similar, thus, images are sim


    float meanHist1;
    float meanHist2;

    meanHist1 = mean(hist1);
    meanHist2 = mean(hist2);

    cout << "meanHist1 = ";
    cout << meanHist1 << endl;

    cout << "meanHist2 = ";
    cout << meanHist2 << endl;

    double score = 0.0;

    for (int i = 0; i < 255; ++i) {
        score += sqrt(hist1[i] * hist2[i]);
    }

    cout << "score before = " << score << endl;

    cout << sqrt(1 - ((1.0 / sqrt(meanHist1 * meanHist2 * 256 * 256)) * score)) << endl;

    score = sqrt(1 - (1 / sqrt(meanHist1 * meanHist2 * 256 * 256)) * score);

    cout << "score after = ";
    cout << score << endl;
    return score;
}

