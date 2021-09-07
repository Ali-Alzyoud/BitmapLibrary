#include "Bitmap.h"
int main(){
    Bitmap *bmp = new Bitmap(100, 100, COLOR_SPACE::COLOR_SPACE_RGB24);
    bmp->save("a.ppm");
}