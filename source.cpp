#include "Bitmap.h"
#include <cmath>


void DrawImageInImage(){
    BitmapBuffer *background = ImageFile::load((char *)"samples/sample_p6.ppm");

    Renderer render(background);
    render.setFillColor(Pixel::RED);
    render.setStrokeColor(Pixel::GREEN);
    render.fillRect(0, 0, 100, 100);
    render.fillRect(background->getWidth()-100, background->getHeight()-100, 100, 100);
    render.fillBitmap(background->resize(background->getWidth()/3,background->getHeight()/3,BITMAP_RESIZE_OPTION::RESIZE_OPTION_NEAREST_NEIGHBOR),
                    background->getWidth()/3,
                    background->getHeight()/3);
    render.drawLine(0, 0, 200, 200);

    ImageFile::save(background, (char *)"a.ppm", PPM_TYPE::PPM_TYPE_P6);
}

void DrawLines(){
    BitmapBuffer *background = new BitmapBuffer(500, 500);

    Renderer render(background);
    render.setLineWidth(5);
    render.setStrokeColor(Pixel::GREEN);
    render.drawLine(0, 0, 500, 500);
    render.setStrokeColor(Pixel::RED);
    render.drawLine(500, 0, 0, 500);
    render.setStrokeColor(Pixel::BLUE);
    render.drawLine(0, 0, 500, 0);
    render.setLineWidth(10);
    render.setStrokeColor(Pixel::BLACK);
    render.drawLine(0, 0, 0, 500);


    render.setLineWidth(2);
    render.setStrokeColor(Pixel::GREEN);
    render.drawCircle(100, 100, 20);

    ImageFile::save(background, (char *)"a.ppm", PPM_TYPE::PPM_TYPE_P6);
}


int main()
{
    //DrawImageInImage();
    DrawLines();

    // // Try to Load and Save Image
    // BitmapBuffer *bmp2 = ImageFile::load((char *)"samples/sample_p6.ppm");
    // Renderer render2(bmp2);
    // render2.fillBitmap(bmp,100,100);
    // render2.fillBitmap(bmp->resize(50,50,BITMAP_RESIZE_OPTION::RESIZE_OPTION_NEAREST_NEIGHBOR),400,100);
    // ImageFile::save(bmp2,(char *)"sample_converted.ppm", PPM_TYPE::PPM_TYPE_P3);


    // BitmapBuffer *bmpReize = ImageFile::load((char *)"samples/sample_p6.ppm")->resize(100,100, BITMAP_RESIZE_OPTION::RESIZE_OPTION_NEAREST_NEIGHBOR);
    // ImageFile::save(bmpReize,(char *)"sample_resize.ppm", PPM_TYPE::PPM_TYPE_P3);
}