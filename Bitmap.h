#ifndef BITMAP_H
#define BITMAP_H

typedef unsigned int UINT;
typedef unsigned char BYTE;

struct Pixel
{
    BYTE r, g, b;
    Pixel(BYTE red, BYTE green, BYTE blue)
    {
        r = red;
        g = green;
        b = blue;
    }
    Pixel()
    {
        r = 0;
        g = 0;
        b = 0;
    }
    static const Pixel RED;
    static const Pixel GREEN;
    static const Pixel BLUE;
    static const Pixel BLACK;
    static const Pixel WHITE;
};

enum BITMAP_RESIZE_OPTION {
    RESIZE_OPTION_NEAREST_NEIGHBOR = 0,
    // BILINEAR,
    // BICUBIC, 
};

class BitmapBuffer
{
public:
    BitmapBuffer(UINT width, UINT height);
    UINT getWidth() const;
    UINT getHeight() const;
    BYTE *getBuffer();
    BitmapBuffer* resize(UINT width, UINT height, BITMAP_RESIZE_OPTION option);
    BitmapBuffer* clone();
    const UINT getBufferSize() const;
    Pixel getPixel(UINT x, UINT y) const;
    void setPixel(UINT x, UINT y, Pixel pixel);
    UINT getDataIndex(UINT x, UINT y) const;

private:
    UINT _width;
    UINT _height;
    BYTE *_data;
    UINT _dataSize;
};











//Responsible for drawing/rendering
class Renderer
{
public:
    Renderer(BitmapBuffer *); //ali.m pass by reference
    void setFillColor(Pixel color);
    Pixel getFillColor() const;
    void setStrokeColor(Pixel color);
    Pixel getStrokeColor() const;
    void fillRect(UINT x, UINT y, UINT width, UINT height);
    void fillBitmap(BitmapBuffer*, UINT x, UINT y);
    void drawLine(UINT x1, UINT y1, UINT x2, UINT y2);

private:
    BitmapBuffer *_buffer;
    Pixel _fillColor;
    Pixel _strokeColor;
};
















// HELPER CLASS
enum PPM_TYPE
{
    PPM_TYPE_NONE,
    PPM_TYPE_P3,
    PPM_TYPE_P6
};
class ImageFile
{
public:
    static void save(BitmapBuffer *bmp, char *path, PPM_TYPE type);
    static BitmapBuffer *load(char *path);
};

#endif //#ifndef BITMAP_H