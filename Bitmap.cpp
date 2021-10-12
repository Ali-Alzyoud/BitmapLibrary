#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include "Bitmap.h"

#define PIXEL_SIZE 3

const Pixel Pixel::RED = Pixel(0xff, 0, 0);
const Pixel Pixel::GREEN = Pixel(0, 0xff, 0);
const Pixel Pixel::BLUE = Pixel(0, 0, 0xff);
const Pixel Pixel::BLACK = Pixel(0, 0, 0);
const Pixel Pixel::WHITE = Pixel(0xff, 0xff, 0xff);

BitmapBuffer::BitmapBuffer(unsigned int width, unsigned int height)
{
    _dataSize = width * height * PIXEL_SIZE;
    _width = width;
    _height = height;
    _data = (unsigned char *)malloc(_dataSize);
    memset(_data, 0xff, _dataSize);
}

UINT BitmapBuffer::getWidth() const
{
    return this->_width;
}

UINT BitmapBuffer::getHeight() const
{
    return this->_height;
}

BYTE *BitmapBuffer::getBuffer(){
    return this->_data;
}

const UINT BitmapBuffer::getBufferSize() const{
    return this->_dataSize;
}

BitmapBuffer* BitmapBuffer::clone(){
    BitmapBuffer * cloneImage = new BitmapBuffer(this->_width, this->_height);
    memcpy(cloneImage->getBuffer(), this->getBuffer(), this->getBufferSize());
    return cloneImage;
}

BitmapBuffer* BitmapBuffer::resize(UINT width, UINT height, BITMAP_RESIZE_OPTION option){
    if(option == RESIZE_OPTION_NEAREST_NEIGHBOR){

        BitmapBuffer * resizeImage = new BitmapBuffer(width, height);

        double x_ratio = this->_width / (double)width;
        double y_ratio = this->_height / (double)height;
        UINT px, py ;
        for (UINT i = 0; i < height; i++)
        {
            for (UINT j = 0; j < width; j++)
            {
                px = (UINT)floor(j * x_ratio);
                py = (UINT)floor(i * y_ratio);
                resizeImage->setPixel(j,i, this->getPixel(px, py));
            }
        }
        return resizeImage;
    }
}

UINT BitmapBuffer::getDataIndex(UINT x, UINT y) const{
   return (y * this->_width * PIXEL_SIZE + x * PIXEL_SIZE);
}

Pixel BitmapBuffer::getPixel(UINT x, UINT y) const
{
    Pixel pixel;
    if (x >= this->_width || y >= this->_height) return pixel;

    UINT index = this->getDataIndex(x,y);
    pixel.r = _data[index];
    pixel.g = _data[index+1];
    pixel.b = _data[index+2];

    return pixel;
}

void BitmapBuffer::setPixel(UINT x, UINT y, Pixel pixel){
    if (x >= this->_width || y >= this->_height) return;

    UINT index = this->getDataIndex(x,y);

    _data[index] = pixel.r;
    _data[index+1] = pixel.g;
    _data[index+2] = pixel.b;
}


//// Renderer

Renderer::Renderer(BitmapBuffer* buffer){
    this->_buffer = buffer;
}

void Renderer::setFillColor(Pixel color){
    this->_fillColor = color;
}


void Renderer::fillRect(UINT x, UINT y, UINT width, UINT height)
{
    int index = 0;
    BYTE *data = this->_buffer->getBuffer();

    UINT xmin = x = std::min(x, this->_buffer->getWidth());
    UINT xmax = x = std::min(x + width, this->_buffer->getWidth());

    UINT ymin = x = std::min(y, this->_buffer->getHeight());
    UINT ymax = x = std::min(y + height, this->_buffer->getHeight());


    for (UINT h = ymin; h < ymax; h++)
    {
        for (UINT w = xmin; w < xmax; w++)
        {
            //ali.m replace with filling rows
            index = this->_buffer->getDataIndex(w,h);
            data[index] = this->_fillColor.r;
            data[index+1] = this->_fillColor.g;
            data[index+2] = this->_fillColor.b;
        }
    }
}

void Renderer::fillBitmap(BitmapBuffer *bmp, UINT x, UINT y){

    UINT xmin = x = std::min(x, this->_buffer->getWidth());
    UINT xmax = x = std::min(x + bmp->getWidth(), this->_buffer->getWidth());

    UINT ymin = x = std::min(y, this->_buffer->getHeight());
    UINT ymax = x = std::min(y + bmp->getHeight(), this->_buffer->getHeight());

    for (UINT h = ymin; h < ymax; h++)
    {
        for (UINT w = xmin; w < xmax; w++)
        {
            //ali.m replace with filling rows
            this->_buffer->setPixel(w, h, bmp->getPixel(w-xmin, h-ymin));
        }
    }
}



//ImageFile
void ImageFile::save(BitmapBuffer *bmp, char *path, PPM_TYPE type){
    std::ofstream file(path,  std::ios_base::out | std::ios_base::binary);
    if(type == PPM_TYPE_P6){
        file<<"P6"<<'\n';
    }
    else if(type == PPM_TYPE_P3){
        file<<"P3"<<'\n';
    }
    file<<bmp->getWidth()<<" "<<bmp->getHeight()<<'\n';
    file<<255<<'\n';
    if(type == PPM_TYPE_P6){
       file.write((const char*) bmp->getBuffer(), bmp->getBufferSize());
    }
    else if(type == PPM_TYPE_P3){
       Pixel pixel;
        for (UINT h = 0; h < bmp->getHeight(); h++)
        {
            for (UINT w = 0; w < bmp->getWidth(); w++)
            {
                pixel = bmp->getPixel(w,h);
                file<<(int)pixel.r<<" "<<(int)pixel.g<<" "<<(int)pixel.b<<'\n';
            }
        }
    }
    file.close();
}

BitmapBuffer* ImageFile::load(char *path){
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
        return NULL;
    }

    if(file.peek() == '#'){
        //Skip comments
        file>>comment;
    }

    file>>width>>height>>pixel_size;
    file.ignore();

    UINT datasize = width * height * PIXEL_SIZE;
    BitmapBuffer *bmp = new BitmapBuffer(width, height);
    if(ppmType == PPM_TYPE_P6){
        file.read((char *)bmp->getBuffer(), datasize);
    }
    else if (ppmType == PPM_TYPE_P3){
        Pixel pixel;
        for (UINT h = 0; h < height; h++)
        {
            for (UINT w = 0; w < width; w++)
            {
                file>>pixel.r>>pixel.g>>pixel.b;
                bmp->setPixel(w,h,pixel);
            }
        }
    }

    file.close();
    return bmp;
}