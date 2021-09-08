#include "Bitmap.h"
int main(){
    Bitmap *bmp = new Bitmap(100, 100, COLOR_SPACE::COLOR_SPACE_RGB24);
    bmp->FillRect(10,10,80,80,Pixel(255,0,0));
    bmp->save("a.ppm");
}