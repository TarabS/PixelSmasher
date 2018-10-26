#include <iostream>

#include "bmp/bmp.h"
#include "picturefunctions.h"

int main(int argc, char *argv[]) {
    bmp *pic = new bmp(argv[0], "pictures\\PandaNoise.bmp");
    pic->printInfo();
    picturefunctions::scale(pic, 255, 255, 255);
    pic->writeFile();
    return 0;
}