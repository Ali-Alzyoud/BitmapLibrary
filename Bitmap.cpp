#include <cstdlib>
#include <cstdio>
#include <string.h>
#include "Bitmap.h"

#define DATA this->_data

unsigned int colorSpaceSize(COLOR_SPACE colorspace) {
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
	unsigned dataSize = width * height * colorSpaceSize(colorspace);
	DATA = (unsigned char *)malloc(dataSize);
	memset(DATA, 0, dataSize);
}
