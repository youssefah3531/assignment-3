#include "Image_Class.h"
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
int main() {
    Image image("mario.jpg");
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j <image.height ; j++)
        {
            unsigned int R=0;
            unsigned int G=0;
            unsigned int B=0;
            R=255-image(i,j,0);
            G=255-image(i,j,1);
            B=255-image(i,j,2);
            image(i,j,0)=R;
            image(i,j,1)=G;
            image(i,j,2)=B;
        }
        
    }
    image.saveImage("supermario.png");
    return 0;
}
