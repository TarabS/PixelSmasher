//
// Created by timun on 21/10/2018.
//

#ifndef PIXELSMASHER_BMP_H
#define PIXELSMASHER_BMP_H

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include "Pixel/Pixel.h"

class bmp {
public:
    bmp(char *dir, char data[128]);

    void printInfo();

private:
    // File Data
    char filepath[128];
    char filepathout[132];

    FILE *file;
    unsigned long size = 0;
    unsigned char data[64];

    typedef struct bmp_header {
        // Hdr
        unsigned char a, b;
        unsigned int size;
        unsigned int zeros;
        unsigned int offset;
        // Dib
        unsigned int hdrsize;
        unsigned int width;
        unsigned int height;
        unsigned int colourplanecount;
        unsigned int bitsperpixel;
        unsigned int compression;
        unsigned int imgsize;
        unsigned int horizonalppm;
        unsigned int verticalppm;
        unsigned int coloursinpallette;
        unsigned int importantcolours;
    } bmp_header;
    bmp_header header;
    // Pixels
    unsigned short *pixeldata;
    Pixel *pixels;

public :
    Pixel *PixelAt(unsigned long x, unsigned long y);

    void writeFile();

    unsigned long getWidth();

    unsigned long getHeight();

    void printFile();
};


#endif //PIXELSMASHER_BMP_H
