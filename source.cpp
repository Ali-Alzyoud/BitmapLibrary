#include "Bitmap.h"
#include<cmath>
int main(){
    Bitmap *bmp = new Bitmap(200, 200);
    bmp->FillRect(10,10,80,80,Pixel::RED);

    int xcenter = 100;
    int ycenter = 100;
    int radius = 30;
    for(float a = 0 ; a < M_PI*2 ; a += 0.01){
        int X = xcenter + radius * cos(a);
        int Y = ycenter + radius * sin(a);
        bmp->setPixel(X, Y, Pixel::GREEN);
    }

    for(float a = 0 ; a < 200 ; a += 0.01){
        bmp->setPixel(a, a, Pixel::BLACK);
    }

    bmp->save((char *)"a.ppm", PPM_TYPE::PPM_TYPE_P6);

    Bitmap *bmp2 = new Bitmap((char *)"samples/sample_p6.ppm");
    for(float a = 0 ; a < M_PI*2 ; a += 0.01){
        int X = xcenter + radius * cos(a);
        int Y = ycenter + radius * sin(a);
        bmp2->setPixel(X, Y, Pixel::BLUE);
    }

    bmp2->save((char *)"b.ppm", PPM_TYPE::PPM_TYPE_P3);
}