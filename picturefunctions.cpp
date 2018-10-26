//
// Created by timun on 26/10/2018.
//

#include "picturefunctions.h"


void picturefunctions::scale(bmp *picture, unsigned short R, unsigned short G, unsigned short B) {
    unsigned long width = picture->getWidth(), height = picture->getHeight();
    for (unsigned long y = 0; y < height; y++)
        for (unsigned long x = 0; x < width; x++) {
            picture->PixelAt(x, y)->scale(R, G, B);
        }
}

void picturefunctions::invert(bmp *picture) {

}
