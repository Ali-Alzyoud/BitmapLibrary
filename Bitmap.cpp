#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <fstream>
#include <iostream>
#include "Bitmap.h"

#define DATA this->_data
#define DATASIZE this->_dataSize

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
    DATASIZE = width * height * colorSpaceSize(colorspace);
    this->_width = width;
    this->_height = height;
    this->_colorspace = colorspace;
    DATA = (unsigned char *)malloc(DATASIZE);
    memset(DATA, 0xff, DATASIZE);
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
void Bitmap::save(char *path){
    std::ofstream file(path);
    file<<"P6"<<std::endl;
    file<<this->_width<<" "<<this->_height<<std::endl;
    if(this->_colorspace == COLOR_SPACE::COLOR_SPACE_RGB24){
        file<<255<<std::endl;
    }
    file.write((const char*) DATA, DATASIZE);
    file.close();
}
