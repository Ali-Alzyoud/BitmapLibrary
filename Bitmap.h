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
};



class Bitmap
{
public:
    Bitmap(UINT width, UINT height, COLOR_SPACE colorspace);
    Pixel getPixel(UINT x, UINT y) const;
    void setPixel(Pixel);
    const BYTE *getRow(UINT row, UINT size) const;
    void setRow(UINT row, BYTE *data, UINT size);
    UINT getWidth() const;
    UINT getHeight() const;

private:
    UINT _width;
    UINT _height;
    unsigned char *_data;
};
#endif//#ifndef BITMAP_H