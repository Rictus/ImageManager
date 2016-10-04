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

/**
 * This function is 100x slower than isColor_Hardcoded. Don't use it for real time stuff
 * @param H
 * @param S
 * @param V
 * @param color
 * @return
 */
bool isColor(int H, int S, int V, Color color) {
    /**It might be better to use unordered_map instead of map for O(1) access.**/
    map<string, int> redThresholds;
    redThresholds["HAS_TWO_THRESHOLDS"] = 1;
    redThresholds["FIRST_THRESHOLD_H_MIN"] = 0;
    redThresholds["FIRST_THRESHOLD_S_MIN"] = 125;
    redThresholds["FIRST_THRESHOLD_V_MIN"] = 107;
    redThresholds["FIRST_THRESHOLD_H_MAX"] = 30;
    redThresholds["FIRST_THRESHOLD_S_MAX"] = 255;
    redThresholds["FIRST_THRESHOLD_V_MAX"] = 255;
    redThresholds["SECOND_THRESHOLD_H_MIN"] = 330;
    redThresholds["SECOND_THRESHOLD_S_MIN"] = 199;
    redThresholds["SECOND_THRESHOLD_V_MIN"] = 157;
    redThresholds["SECOND_THRESHOLD_H_MAX"] = 360;
    redThresholds["SECOND_THRESHOLD_S_MAX"] = 255;
    redThresholds["SECOND_THRESHOLD_V_MAX"] = 255;
    map<Color, map<string, int>> THRESHOLDS;
    THRESHOLDS[Color::RED] = redThresholds;

    switch (color) {
        case Color::RED:
            if (H >= THRESHOLDS[color]["FIRST_THRESHOLD_H_MIN"] &&
                H <= THRESHOLDS[color]["FIRST_THRESHOLD_H_MAX"] &&
                S >= THRESHOLDS[color]["FIRST_THRESHOLD_S_MIN"] &&
                S <= THRESHOLDS[color]["FIRST_THRESHOLD_S_MAX"] &&
                V >= THRESHOLDS[color]["FIRST_THRESHOLD_V_MIN"] &&
                V <= THRESHOLDS[color]["FIRST_THRESHOLD_V_MAX"]) {
                return true;
            }
            if (THRESHOLDS[color]["HAS_TWO_THRESHOLDS"] == 1) {
                if (H >= THRESHOLDS[color]["SECOND_THRESHOLD_H_MIN"] &&
                    H <= THRESHOLDS[color]["SECOND_THRESHOLD_H_MAX"] &&
                    S >= THRESHOLDS[color]["SECOND_THRESHOLD_S_MIN"] &&
                    S <= THRESHOLDS[color]["SECOND_THRESHOLD_S_MAX"] &&
                    V >= THRESHOLDS[color]["SECOND_THRESHOLD_V_MIN"] &&
                    V <= THRESHOLDS[color]["SECOND_THRESHOLD_V_MAX"]) {
                    return true;
                }
            }
            break;
        default:
            cerr << "This color is not yet suported : " << color << endl;
            return false;
            break;
    }
    return false;
}


bool isColor_Hardcoded(int H, int S, int V, Color color) {
    switch (color) {
        case Color::RED:
            if ((H >= 0 && H <= 30 &&
                 S >= 125 && S <= 225 &&
                 V >= 107 && V <= 255)) {
                return true;
            }
            if ((H >= 330 && H <= 360 &&
                 S >= 199 && S <= 255 &&
                 V >= 157 && V <= 255)) {
                return true;
            }
            break;
        default:
            cerr << "This color is not yet suported : " << color << endl;
            return false;
            break;
    }
    return false;
}