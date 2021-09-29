#include "Bitmap.h"
#include <cmath>
int main()
{
    BitmapBuffer *bmp = new BitmapBuffer(200, 200);

    Renderer render(bmp);
    render.setFillColor(Pixel::RED);
    render.fillRect(10, 10, 80, 80);

    int xcenter = 100;
    int ycenter = 100;
    int radius = 30;
    for (float a = 0; a < M_PI * 2; a += 0.01)
    {
        int X = xcenter + radius * cos(a);
        int Y = ycenter + radius * sin(a);
        render.setPixel(X, Y, Pixel::GREEN);
    }

    for (float a = 0; a < 200; a += 0.01)
    {
        render.setPixel(a, a, Pixel::BLACK);
    }

    ImageFile::save(bmp, (char *)"a.ppm", PPM_TYPE::PPM_TYPE_P6);

    // Try to Load and Save Image
    BitmapBuffer *bmp2 = ImageFile::load((char *)"samples/sample_p6.ppm");
    ImageFile::save(bmp2,(char *)"sample_converted.ppm", PPM_TYPE::PPM_TYPE_P6);
}