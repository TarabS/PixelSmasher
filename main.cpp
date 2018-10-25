#include <iostream>

#include "bmp/bmp.h"

int main(int argc, char *argv[]) {
    bmp *pic = new bmp(argv[0], "pictures\\PandaNoise.bmp");
    pic->printInfo();
    return 0;
}