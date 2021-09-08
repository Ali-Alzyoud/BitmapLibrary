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

const Pixel Pixel::RED = Pixel(0xff, 0, 0);
const Pixel Pixel::GREEN = Pixel(0, 0xff, 0);
const Pixel Pixel::BLUE = Pixel(0, 0, 0xff);
const Pixel Pixel::BLACK = Pixel(0, 0, 0);
const Pixel Pixel::WHITE = Pixel(0xff, 0xff, 0xff);

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
    Pixel pixel;
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

void Bitmap::FillRect(UINT x, UINT y, UINT width, UINT height, Pixel color)
{
    //ali.m outbounds check
    int index = 0;
    for (UINT h = y; h < (y + height); h++)
    {
        for (UINT w = x; w < (x + width); w++)
        {
            //ali.m replace with filling rows
            index = h*this->_width * 3 + w * 3;
            DATA[index] = color.r;
            DATA[index+1] = color.g;
            DATA[index+2] = color.b;
        }
    }
}
