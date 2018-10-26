//
// Created by timun on 21/10/2018.
//

#include "bmp.h"

bmp::bmp(char *dir, char filename[128]) {
    // Clear Mems
    memset(data, '\0', 64);
    memset(filepath, '\0', 128);
    memset(filepathout, '\0', 132);
    unsigned short dirend = 0, filenamelen = 0; // Pointer to decide the end of the directory and start of filename
    for (unsigned short i = 0; i < 128 * dir[i] != '\0'; i++) // Split dir
        if (dir[i] == '\\') dirend = i;
    while (filename[filenamelen++] != '\0'); // Find filename
    // Add filename to dir
    memcpy(&filepath, dir, dirend + 1);
    memcpy(&filepath[dirend + 1], filename, filenamelen);
    memcpy(filepathout, filepath, dirend + 1 + filenamelen);
    memcpy(&filepathout[dirend + filenamelen], ".out", 4);

    printf("\nFiles\nIn  : %s\nOut : %s\n", filepath, filepathout);

    // Open File
    int err = fopen_s(&file, filepath, "r");
    if (err != 0) {
        // If file doesn't exist, Error
        printf("Error Reading File %d", err);
        return;
    }
    // Find end of file to determine length
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Read Data In
    fread(data, 1, 64, file);

    // Header
    memcpy(filetype, &data[0], 2);
    filetype[2] = '\0';
    memcpy(&filesize, &data[2], 4);
    memcpy(&zeros, &data[6], 4);
    memcpy(&offset, &data[10], 4);
    memcpy(&hdrsize, &data[14], 4);

    // Meta
    memcpy(&width, &data[18], 4);
    memcpy(&height, &data[22], 4);
    memcpy(&planes, &data[26], 2);
    memcpy(&bpp, &data[28], 2);
    memcpy(&compression, &data[30], 4);
    memcpy(&imagesize, &data[34], 4);
    memcpy(&ppmx, &data[38], 4);
    memcpy(&ppmy, &data[42], 4);
    memcpy(&noofcolours, &data[46], 4);

    // And, now for the pixels
    pixeldata = (unsigned short *) calloc(width * height, 3);
    pixels = (Pixel *) calloc(width * height, sizeof(Pixel));
    fread(pixeldata, 3, width * height, file);
    for (unsigned long pixel = 0; pixel < width * height; pixel++)
        pixels[pixel] = Pixel(
                pixeldata[(pixel * 3) + 0],
                pixeldata[(pixel * 3) + 1],
                pixeldata[(pixel * 3) + 2]
        );

    // Close file
    fclose(file);
}

void bmp::writeFile() {
    // Open File
    int err = fopen_s(&file, filepathout, "w");
    if (err != 0) {
        // If file doesn't exist, Error
        printf("Error Reading File %d", err);
        return;
    }
    fwrite(data, 1, 64, file);
    fwrite(pixeldata, 3, width * height, file);
    fclose(file);
}

void bmp::printInfo() {
    printf("\nFile Data [%lo bytes] %s", size, filepath);
    printf("\nFile Type          : %s", filetype);
    printf("\nFile Size          : %lo", filesize);
    printf("\nZeros              : %08x", zeros);
    printf("\nOffset             : %lo", offset);
    printf("\nHeader Size        : %lo", hdrsize);
    printf("\nWidth              : %lo", width);
    printf("\nHeight             : %lo", height);
    printf("\nPlanes             : %lo", planes);
    printf("\nBits Per Pixel     : %lo", bpp);
    printf("\nCompression        : %lo", compression);
    printf("\nImage Size         : %lo", imagesize);
    printf("\nPixel Per Meter X  : %lo", ppmx);
    printf("\nPixel Per Meter Y  : %lo", ppmy);
    printf("\nNumber of Colours  : %lo", noofcolours);

}


Pixel *bmp::PixelAt(unsigned long x, unsigned long y) {
    if (x < 0 || x > width || y < 0 || y > height) return pixels;
    return &pixels[(y * width) + x];
}

unsigned long bmp::getWidth() {
    return width;
}

unsigned long bmp::getHeight() {
    return height;
}

void bmp::printFile() {
    unsigned long maxwidth = 96, maxheight = 54;
    unsigned long skipX = width / maxwidth, skipY = height / maxheight;
    printf("\nData");
    for (unsigned long y = 0; y < height; y += skipY) {
        printf("\nLine : %3.lo  |  ", y);
        for (unsigned long x = 0; x < width; x += skipX) {
            printf("%c%c%c ", PixelAt(x, y)->Red(), PixelAt(x, y)->Green(), PixelAt(x, y)->Blue());
        }
    }
}