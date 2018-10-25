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

class bmp {
public:
    bmp(char *dir, char data[128]);

    void printInfo();

private:
    // File Data
    char filepath[128];
    FILE *file;
    unsigned long size = 0;
    unsigned char data[64];
    // Header
    unsigned char filetype[3];
    unsigned long filesize = 0, zeros = 0, offset = 0, hdrsize = 0;
    unsigned long width = 0, height = 0, compression = 0, imagesize = 0, ppmx = 0, ppmy = 0, noofcolours = 0;
    uint16_t planes = 0, bpp = 0;
};



#endif //PIXELSMASHER_BMP_H
