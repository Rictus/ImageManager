//
// Created by Dylan on 04/10/2016.
//
#include "ImageUtils.h"

using namespace std;

int *RGBToHSV(int r, int g, int b) {
    float H = 0;
    float S = 0;//TODO We could use S/V to escape from white/black
    float V = 0;
    float rPrime, gPrime, bPrime;
    float Cmax, Cmin;
    float delta;
    /**Hue calculation. See : http://www.rapidtables.com/convert/color/rgb-to-hsv.htm**/
    rPrime = (float) (r / 255.0);
    gPrime = (float) (g / 255.0);
    bPrime = (float) (b / 255.0);
    Cmax = max(max(rPrime, gPrime), bPrime);
    Cmin = min(min(rPrime, gPrime), bPrime);
    delta = Cmax - Cmin;
    V = Cmax;
    if (delta == 0) {
        H = 0;
        S = 0;
    } else {
        if (Cmax == rPrime) {
            H = gPrime - bPrime;
            H = abs(H / delta);
            H = (float) fmod(H, 6.0);
            H = (float) (H * 60.0);
        } else if (Cmax == gPrime) {
            H = (bPrime - rPrime);
            H = abs(H / delta);
            H = (float) (H + 2.0);
            H = (float) (H * 60.0);
        } else if (Cmax == bPrime) {
            H = (rPrime - gPrime);
            H = abs(H / delta);
            H = (float) (H + 4.0);
            H = (float) (H * 60.0);
        }
        S = delta / Cmax;
    }
    int *output = new int[3];
    S = (float) (255.0 * S);
    V = V * (float) 255.0;
    output[0] = (int) H;
    output[1] = (int) S;
    output[2] = (int) V;
    return output;
}

bool isRed(const int H, const int S, const int V) {

    //first: 0-26, 125-255, 107-255
    //second: 330/360, 199-255, 157-255
    // We need to check twice because Red color is on both extremities of chromatic HSV circle.
    const int FIRST_THRESHOLD_H_MIN = 0;
    const int FIRST_THRESHOLD_S_MIN = 125;
    const int FIRST_THRESHOLD_V_MIN = 107;

    const int FIRST_THRESHOLD_H_MAX = 26;
    const int FIRST_THRESHOLD_S_MAX = 255;
    const int FIRST_THRESHOLD_V_MAX = 255;

    const int SECOND_THRESHOLD_H_MIN = 330;
    const int SECOND_THRESHOLD_S_MIN = 199;
    const int SECOND_THRESHOLD_V_MIN = 157;

    const int SECOND_THRESHOLD_H_MAX = 360;
    const int SECOND_THRESHOLD_S_MAX = 255;
    const int SECOND_THRESHOLD_V_MAX = 255;

    if (H >= FIRST_THRESHOLD_H_MIN && H <= FIRST_THRESHOLD_H_MAX &&
        S >= FIRST_THRESHOLD_S_MIN && S >= FIRST_THRESHOLD_S_MAX &&
        V >= FIRST_THRESHOLD_V_MIN && V <= FIRST_THRESHOLD_V_MAX) {
        return true;
    }

    if (H >= SECOND_THRESHOLD_H_MIN && H <= SECOND_THRESHOLD_H_MAX &&
        S >= SECOND_THRESHOLD_S_MIN && S >= SECOND_THRESHOLD_S_MAX &&
        V >= SECOND_THRESHOLD_V_MIN && V <= SECOND_THRESHOLD_V_MAX) {
        return true;
    }

    return false;
}