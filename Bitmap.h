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

class BitmapBuffer
{
public:
    BitmapBuffer(UINT width, UINT height);
    UINT getWidth() const;
    UINT getHeight() const;
    BYTE *getBuffer();
    const UINT getBufferSize() const;

private:
    UINT _width;
    UINT _height;
    BYTE *_data;
    UINT _dataSize;
};

class Renderer
{
public:
    Renderer(BitmapBuffer *); //ali.m pass by reference
    void setFillColor(Pixel color);
    void fillRect(UINT x, UINT y, UINT width, UINT height);
    Pixel getPixel(UINT x, UINT y) const;
    void setPixel(UINT x, UINT y, Pixel pixel);

private:
    UINT getDataIndex(UINT x, UINT y) const;
    BitmapBuffer *_buffer;
    Pixel _fillColor;
};

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