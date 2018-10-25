//
// Created by timun on 21/10/2018.
//

#include "bmp.h"

bmp::bmp(char *dir, char filename[128]) {
    // Clear Mems
    memset(data, '\0', 64);
    memset(filepath, '\0', 128);
    unsigned short dirend = 0; // Pointer to decide the end of the directory and start of filename
    for (unsigned short i = 0; i < 128 * dir[i] != '\0'; i++) { // Split dir
        memcpy(&filepath[i], &dir[i], 1);
        if (filepath[i] == '\\') dirend = i + 1;
    }
    // Add filename to dir
    memset(&filepath[dirend], '\0', 128 - dirend);
    memcpy(&filepath[dirend], filename, 128);
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