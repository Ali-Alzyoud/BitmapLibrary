#ifndef BITMAP_H
#define BITMAP_H
enum COLOR_SPACE
{
    COLOR_SPACE_RGB24 = 0
};

typedef unsigned int UINT;
typedef unsigned char BYTE;

struct Pixel{
    BYTE r,g,b;
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



class Bitmap
{
public:
    Bitmap(UINT width, UINT height, COLOR_SPACE colorspace);
    Bitmap(char *path);
    Pixel getPixel(UINT x, UINT y) const;
    void setPixel(UINT x, UINT y, Pixel pixel);
    const BYTE *getRow(UINT row, UINT size) const;
    void setRow(UINT row, BYTE *data, UINT size);
    UINT getWidth() const;
    UINT getHeight() const;
    void save(char *path);

    //Render functions
    void FillRect(UINT x, UINT y, UINT width, UINT height, Pixel color);

private:
    UINT _width;
    UINT _height;
    COLOR_SPACE _colorspace;
    BYTE *_data;
    UINT _dataSize;
};
#endif//#ifndef BITMAP_H