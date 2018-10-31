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
    fclose(file);
    memcpy_s(&header, 64, &data, 64);
    int x =2;
    printf(
            "\nMem Locs"
            "\n[%x] A : %x"
            "\n[%x] B : %x"
            "\n[%x] S : %x"
            "\n[%x] Z : %x"
            "\n[%x] 0 : %x",
            &header.a, header.a,
            &header.b, header.b,
            &header.size, header.size,
            &header.zeros, header.zeros,
            &header.offset, header.offset
    );
    printf("\n\n");
    //for(int i =0 ;i < 64;i++)
        //printf("")

    // Header
    //header = (bmp_header *) data;

    /*
    // And, now for the pixels
    pixeldata = (unsigned short *) calloc(header.width * header.height, 3);
    pixels = (Pixel *) calloc(header.width * header.height, sizeof(Pixel));
    fread(pixeldata, 3, header.width * header.height, file);
    for (unsigned long pixel = 0; pixel < header.width * header.height; pixel++)
        pixels[pixel] = Pixel(
                pixeldata[(pixel * 3) + 0],
                pixeldata[(pixel * 3) + 1],
                pixeldata[(pixel * 3) + 2]
        );

    // Close file
    */

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
    fwrite(pixeldata, 3, header.width * header.height, file);
    fclose(file);
}

void bmp::printInfo() {
    printf("\nFile Data [%lo bytes] %s", size, filepath);
    // Hdr
    printf("\nFiletype : %c%c", header.a, header.b);
    printf("\nZeros    : %lo", (long) header.size);

}


Pixel *bmp::PixelAt(unsigned long x, unsigned long y) {
    if (x < 0 || x > header.width || y < 0 || y > header.height) return pixels;
    return &pixels[(y * header.width) + x];
}

unsigned long bmp::getWidth() {
    return header.width;
}

unsigned long bmp::getHeight() {
    return header.width;
}

void bmp::printFile() {
    unsigned long maxwidth = 96, maxheight = 54;
    unsigned long skipX = header.width / maxwidth, skipY = header.height / maxheight;
    printf("\nData");
    for (unsigned long y = 0; y < header.height; y += skipY) {
        printf("\nLine : %3.lo  |  ", y);
        for (unsigned long x = 0; x < header.width; x += skipX) {
            printf("%c%c%c ", PixelAt(x, y)->Red(), PixelAt(x, y)->Green(), PixelAt(x, y)->Blue());
        }
    }
}