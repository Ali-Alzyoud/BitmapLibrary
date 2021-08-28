#pragma once
#include "Bitmap.h"
enum IMAGE_FORMAT {
	IMAGE_FORMAT_PPM = 0
};
class Image
{
public:
	static void Save(Bitmap* bitmap, IMAGE_FORMAT format, char* path);
};

