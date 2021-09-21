#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <fstream>
#include <iostream>
#include "Bitmap.h"

#define DATA this->_data
#define DATASIZE this->_dataSize
#define IMAGE_WIDTH this->_width
#define IMAGE_HEIGHT this->_height
#define COLORSPACE this->_colorspace
#define GET_DATA_INDEX(x,y) (y * IMAGE_WIDTH * 3 + x * 3);


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
    IMAGE_WIDTH = width;
    IMAGE_HEIGHT = height;
    this->_colorspace = colorspace;
    DATA = (unsigned char *)malloc(DATASIZE);
    memset(DATA, 0xff, DATASIZE);
}

Bitmap::Bitmap(char *path){
    std::ifstream file(path);

    //ali.m skip comments
    //read p3 p6
    std::string type;
    UINT width;
    UINT height;
    UINT pixel_size;

    file>>type;
    file>>width>>height>>pixel_size;

    if(pixel_size == 255){
        COLORSPACE = COLOR_SPACE::COLOR_SPACE_RGB24;
    }

    IMAGE_WIDTH = width;
    IMAGE_HEIGHT = height;
    DATASIZE = width * height * colorSpaceSize(COLORSPACE);
    DATA = (unsigned char *)malloc(DATASIZE);
    file.read((char *)DATA, DATASIZE);

    file.close();
}

Pixel Bitmap::getPixel(UINT x, UINT y) const
{
    Pixel pixel;
    if (x >= IMAGE_WIDTH || y >= IMAGE_HEIGHT) return pixel;

    UINT index = GET_DATA_INDEX(x,y);
    pixel.r = DATA[index];
    pixel.g = DATA[index+1];
    pixel.b = DATA[index+2];

    return pixel;
}

void Bitmap::setPixel(UINT x, UINT y, Pixel pixel){
    if (x >= IMAGE_WIDTH || y >= IMAGE_HEIGHT) return;

    UINT index = GET_DATA_INDEX(x,y);
    DATA[index] = pixel.r;
    DATA[index+1] = pixel.g;
    DATA[index+2] = pixel.b;
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
            index = GET_DATA_INDEX(w,h);
            DATA[index] = color.r;
            DATA[index+1] = color.g;
            DATA[index+2] = color.b;
        }
    }
}
