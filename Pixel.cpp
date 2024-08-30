//
// Created by huang on 6/27/2024.
//

#include "Pixel.h"

Pixel::Pixel(char paramB, char paramG, char paramR) {
    b = paramB;
    g = paramG;
    r = paramR;
    npb = (float) (unsigned char) b/255;
    npg = (float) (unsigned char) g/255;
    npr = (float) (unsigned char) r/255;
}
