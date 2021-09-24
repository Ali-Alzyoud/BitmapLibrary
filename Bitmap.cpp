#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <fstream>
#include <iostream>
#include "Bitmap.h"

#define PIXEL_SIZE 3
#define DATA this->_data
#define DATASIZE this->_dataSize
#define IMAGE_WIDTH this->_width
#define IMAGE_HEIGHT this->_height
#define GET_DATA_INDEX(x,y) (y * IMAGE_WIDTH * PIXEL_SIZE + x * PIXEL_SIZE);

const Pixel Pixel::RED = Pixel(0xff, 0, 0);
const Pixel Pixel::GREEN = Pixel(0, 0xff, 0);
const Pixel Pixel::BLUE = Pixel(0, 0, 0xff);
const Pixel Pixel::BLACK = Pixel(0, 0, 0);
const Pixel Pixel::WHITE = Pixel(0xff, 0xff, 0xff);

Bitmap::Bitmap(unsigned int width, unsigned int height)
{
    DATASIZE = width * height * PIXEL_SIZE;
    IMAGE_WIDTH = width;
    IMAGE_HEIGHT = height;
    DATA = (unsigned char *)malloc(DATASIZE);
    memset(DATA, 0xff, DATASIZE);
}

Bitmap::Bitmap(char *path){
    std::ifstream file(path);

    //read p3 p6
    std::string type;
    std::string comment;
    UINT width;
    UINT height;
    UINT pixel_size;
    PPM_TYPE ppmType = PPM_TYPE_NONE;

    file>>type;
     if(type == "P3"|| type == "p3")
    {
        ppmType = PPM_TYPE_P3;
    }
    else if(type == "P6" || type == "p6")
    {
        ppmType = PPM_TYPE_P6;
    }

    //Incase of not supported file
    if(ppmType == PPM_TYPE_NONE){
        return;
    }

    if(file.peek() == '#'){
        //Skip comments
        file>>comment;
    }

    file>>width>>height>>pixel_size;

    IMAGE_WIDTH = width;
    IMAGE_HEIGHT = height;
    DATASIZE = width * height * PIXEL_SIZE;
    DATA = (unsigned char *)malloc(DATASIZE);
    if(ppmType == PPM_TYPE_P6){
        file.read((char *)DATA, DATASIZE);
    }
    else if (ppmType == PPM_TYPE_P3){
        Pixel pixel;
        for (UINT h = 0; h < IMAGE_HEIGHT; h++)
        {
            for (UINT w = 0; w < IMAGE_WIDTH; w++)
            {
                file>>pixel.r>>pixel.g>>pixel.b;
                setPixel(w,h,pixel);
            }
        }
    }

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

void Bitmap::save(char *path, PPM_TYPE type){
    std::ofstream file(path);
    if(type == PPM_TYPE_P6){
        file<<"P6"<<std::endl;
    }
    else if(type == PPM_TYPE_P3){
        file<<"P3"<<std::endl;
    }
    file<<this->_width<<" "<<this->_height<<std::endl;
    file<<255<<std::endl;
    if(type == PPM_TYPE_P6){
       file.write((const char*) DATA, DATASIZE);
    }
    else if(type == PPM_TYPE_P3){
       Pixel pixel;
        for (UINT h = 0; h < IMAGE_HEIGHT; h++)
        {
            for (UINT w = 0; w < IMAGE_WIDTH; w++)
            {
                pixel = getPixel(w,h);
                file<<(int)pixel.r<<" "<<(int)pixel.g<<" "<<(int)pixel.b<<std::endl;
            }
        }
    }
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
