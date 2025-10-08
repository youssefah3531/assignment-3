#include "Image_Class.h"
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    Image image("building.jpg");
    Image image2(image.width, image.height);
    for (int i = 20; i < image.width-20; i++)
    {
        for (int j = 20; j < image.height-20; j++)
        {
            int R=0;
            int G=0;
            int B=0;
            for (int k = i-20; k < i+20; k++)
            {
                for (int l = j-20; l < j+20; l++)
                {
                    R+=image(k,l,0);
                    G+=image(k,l,1);
                    B+=image(k,l,2);
                }
            }
            R/=1600;
            G/=1600;
            B/=1600;
            image2(i,j,0)=R;
            image2(i,j,1)=G;
            image2(i,j,2)=B;
        }
    }
    image2.saveImage("opopop.png");
}
