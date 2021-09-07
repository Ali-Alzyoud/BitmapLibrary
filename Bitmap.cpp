#include <cstdlib>
#include <cstdio>
#include <string.h>
#include "Bitmap.h"

#define DATA this->_data

unsigned int colorSpaceSize(COLOR_SPACE colorspace)
{
    switch (colorspace)
    {
    case COLOR_SPACE_RGB24:
        return 24;
    default:
        return 0;
    }
}

Bitmap::Bitmap(unsigned int width, unsigned int height, COLOR_SPACE colorspace)
{
    unsigned dataSize = width * height * colorSpaceSize(colorspace);
    DATA = (unsigned char *)malloc(dataSize);
    memset(DATA, 0, dataSize);
}

Pixel Bitmap::getPixel(UINT x, UINT y) const
{
    Pixel pixel={0};
    if (x >= this->_width || y >= this->_height) return pixel;

    //ali.m needs to add implementation;

}

UINT Bitmap::getWidth() const
{
    return this->_width;
}
UINT Bitmap::getHeight() const
{
    return this->_height;
}
