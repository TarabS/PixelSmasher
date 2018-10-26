//
// Created by timun on 26/10/2018.
//

#include "Pixel.h"

Pixel::Pixel(unsigned short &Red, unsigned short &Green, unsigned short &Blue) {
    R = Red;
    G = Green;
    B = Blue;
}

unsigned short Pixel::Red() {
    return R;
}

unsigned short Pixel::Green() {
    return G;
}

unsigned short Pixel::Blue() {
    return B;
}


// Pixel Functions

void Pixel::scale(unsigned short dR, unsigned short dG, unsigned short dB) {
    R /= dR;
    G /= dG;
    B /= dB;
}

void Pixel::invert() {
    R = (unsigned short) 0xFF - R;
    G = (unsigned short) 0xFF - G;
    B = (unsigned short) 0xFF - B;
}