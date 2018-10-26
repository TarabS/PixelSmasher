//
// Created by timun on 26/10/2018.
//

#ifndef PIXELSMASHER_PICTUREFUNCTIONS_H
#define PIXELSMASHER_PICTUREFUNCTIONS_H

#include "bmp/bmp.h"

class picturefunctions {
public:
    static void scale(bmp *picture, unsigned short R, unsigned short G, unsigned short B);

    static void invert(bmp *picture);
};


#endif //PIXELSMASHER_PICTUREFUNCTIONS_H
