//
// Created by timun on 26/10/2018.
//

#ifndef PIXELSMASHER_PIXEL_H
#define PIXELSMASHER_PIXEL_H


class Pixel {
private:
    unsigned short R, G, B;
public:
    Pixel(unsigned short &Red, unsigned short &Green, unsigned short &Blue);

    unsigned short Red();

    unsigned short Green();

    unsigned short Blue();

public :
    void scale(unsigned short dR, unsigned short dG, unsigned short dB);

    void invert();
};


#endif //PIXELSMASHER_PIXEL_H
