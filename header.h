//
// Created by huang on 6/27/2024.
//

#pragma once

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;

    Header(char id, char color, char data, short mapori, short maplen, char mapdep, short xori, short yori, short wid, short hei, char bits, char descrip) {
        idLength = id;
        colorMapType = color;
        dataTypeCode = data;
        colorMapOrigin = mapori;
        colorMapLength = maplen;
        colorMapDepth = mapdep;
        xOrigin = xori;
        yOrigin = yori;
        width = wid;
        height = hei;
        bitsPerPixel = bits;
        imageDescriptor = descrip;
    }
};
