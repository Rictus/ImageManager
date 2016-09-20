//
// Created by Dylan on 20/09/2016.
//

#ifndef IMAGEMANAGER_IMAGEMANAGER_H
#define IMAGEMANAGER_IMAGEMANAGER_H
#include <iostream>
#include <bitset>

using namespace std;

/** We could go further and define the class Byte
 *  and overloading some operators (+, -, =, [], ...)
 */
typedef bitset<8> byte; // From 00000000 (0) to 11111111 (254)

class ImageManager {
private:
    byte**_image; // Let's find something better than **
public:
    void loadPPM();

    void loadPGM();

    void savePPM();

    void savePGM();

    void applySobelMask();
};


#endif //IMAGEMANAGER_IMAGEMANAGER_H
