#include "Bitmap.h"
#include<cmath>
int main(){
    Bitmap *bmp = new Bitmap(200, 200, COLOR_SPACE::COLOR_SPACE_RGB24);
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

    bmp->save((char *)"a.ppm");

    Bitmap *bmp2 = new Bitmap((char *)"a.ppm");
    for(float a = 0 ; a < M_PI*2 ; a += 0.01){
        int X = xcenter + radius * cos(a);
        int Y = ycenter + radius * sin(a);
        bmp2->setPixel(X, Y, Pixel::BLUE);
    }

    bmp2->save((char *)"b.ppm");
}