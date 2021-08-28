#pragma once
enum COLOR_SPACE {
	COLOR_SPACE_RGB24 = 0
};

typedef unsigned int UINT;
typedef unsigned char BYTE;

class Bitmap
{
public:
	Bitmap(UINT width, UINT height, COLOR_SPACE colorspace);
	BYTE* getPixel();
	void setPixel(BYTE* data);
	BYTE* getRow(UINT row, UINT size);
	void setRow(UINT row, BYTE *data, UINT size);
private:
	UINT _width;
	UINT _height;
	unsigned char *_data;
};

