#include "Image_Class.h"
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
int main() {
    // //90 degree
    Image image("mario90.png");
    Image image2(image.height,image.width);
    int k=0;
    int l=0;
    for (int i = 0; i < image.width; i++)
    {
        for (int j = image.height-1; j >=0; j--)
        {
            image2(k,l,0)=image(i,j,0);
            image2(k,l,1)=image(i,j,1);
            image2(k,l,2)=image(i,j,2);
            k++;
        }
        k=0;
        l++;
    }
    image2.saveImage("image2.png");
    // //###############################################
    // //180degree
    // Image image("building.jpg");
    // Image image2(image.height,image.width);
    // Image image3(image.width,image.height);
    // int k=0;
    // int l=0;
    // for (int i = 0; i < image.width; i++)
    // {
    //     for (int j = image.height-1; j >=0; j--)
    //     {
    //         image2(k,l,0)=image(i,j,0);
    //         image2(k,l,1)=image(i,j,1);
    //         image2(k,l,2)=image(i,j,2);
    //         k++;
    //     }
    //     k=0;
    //     l++;
    // }
    // k=0;
    // l=0;
    // for (int i = 0; i < image2.width; i++)
    // {
    //     for (int j = image2.height-1; j >=0; j--)
    //     {
    //         image3(k,l,0)=image2(i,j,0);
    //         image3(k,l,1)=image2(i,j,1);
    //         image3(k,l,2)=image2(i,j,2);
    //         k++;
    //     }
    //     k=0;
    //     l++;
    // }
    // image3.saveImage("image3.png");
    // //############################################################
    // //270 degree
    // Image image("building.jpg");
    // Image image2(image.height,image.width);
    // Image image3(image.width,image.height);
    // Image image4(image.height,image.width);
    // int k=0;
    // int l=0;
    // for (int i = 0; i < image.width; i++)
    // {
    //     for (int j = image.height-1; j >=0; j--)
    //     {
    //         image2(k,l,0)=image(i,j,0);
    //         image2(k,l,1)=image(i,j,1);
    //         image2(k,l,2)=image(i,j,2);
    //         k++;
    //     }
    //     k=0;
    //     l++;
    // }
    // k=0;
    // l=0;
    // for (int i = 0; i < image2.width; i++)
    // {
    //     for (int j = image2.height-1; j >=0; j--)
    //     {
    //         image3(k,l,0)=image2(i,j,0);
    //         image3(k,l,1)=image2(i,j,1);
    //         image3(k,l,2)=image2(i,j,2);
    //         k++;
    //     }
    //     k=0;
    //     l++;
    // }
    // k=0;
    // l=0;
    //     for (int i = 0; i < image3.width; i++)
    // {
    //     for (int j = image3.height-1; j >=0; j--)
    //     {
    //         image4(k,l,0)=image3(i,j,0);
    //         image4(k,l,1)=image3(i,j,1);
    //         image4(k,l,2)=image3(i,j,2);
    //         k++;
    //     }
    //     k=0;
    //     l++;
    // }
    // image4.saveImage("image4.png");
    // return 0;
}
