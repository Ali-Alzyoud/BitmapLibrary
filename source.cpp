#include "Bitmap.h"
#include <cmath>
int main()
{
    BitmapBuffer *bmp = new BitmapBuffer(200, 200);

    Renderer render(bmp);
    render.setFillColor(Pixel::RED);
    render.fillRect(10, 10, 80, 80);
    render.fillRect(180, 180, 80, 80);

    int xcenter = 100;
    int ycenter = 100;
    int radius = 30;
    for (float a = 0; a < M_PI * 2; a += 0.01)
    {
        int X = xcenter + radius * cos(a);
        int Y = ycenter + radius * sin(a);
        bmp->setPixel(X, Y, Pixel::GREEN);
    }

    for (float a = 0; a < 200; a += 0.01)
    {
        bmp->setPixel(a, a, Pixel::BLACK);
    }

    ImageFile::save(bmp, (char *)"a.ppm", PPM_TYPE::PPM_TYPE_P6);

    // Try to Load and Save Image
    BitmapBuffer *bmp2 = ImageFile::load((char *)"samples/sample_p6.ppm");
    Renderer render2(bmp2);
    render2.fillBitmap(bmp,100,100);
    render2.fillBitmap(bmp->resize(50,50,BITMAP_RESIZE_OPTION::RESIZE_OPTION_NEAREST_NEIGHBOR),400,100);
    ImageFile::save(bmp2,(char *)"sample_converted.ppm", PPM_TYPE::PPM_TYPE_P3);


    BitmapBuffer *bmpReize = ImageFile::load((char *)"samples/sample_p6.ppm")->resize(100,100, BITMAP_RESIZE_OPTION::RESIZE_OPTION_NEAREST_NEIGHBOR);
    ImageFile::save(bmpReize,(char *)"sample_resize.ppm", PPM_TYPE::PPM_TYPE_P3);
}