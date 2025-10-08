#include "Image_Class.h"
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
int main()
{
    Image image("building.jpg");
    for (int i = 0; i < image.width / 50; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            unsigned int R = 0;
            unsigned int G = 0;
            unsigned int B = 0;
            image(i, j, 0) = 0;
            image(i, j, 1) = 0;
            image(i, j, 2) = 255;
        }
    }
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height / 70; j++)
        {
            unsigned int R = 0;
            unsigned int G = 0;
            unsigned int B = 0;
            image(i, j, 0) = 0;
            image(i, j, 1) = 0;
            image(i, j, 2) = 255;
        }
    }
    for (int i = image.width-1; i > image.width-70; i--)
    {
        for (int j = 0; j < image.height; j++)
        {
            unsigned int R = 0;
            unsigned int G = 0;
            unsigned int B = 0;
            image(i, j, 0) = 0;
            image(i, j, 1) = 0;
            image(i, j, 2) = 255;
        }
    }
    for (int j = image.height - 1; j >image.height-70 ; j--)
    {
        for (int i = image.width - 1; i > image.width / 100; i--)
        {
            unsigned int R = 0;
            unsigned int G = 0;
            unsigned int B = 0;
            image(i, j, 0) = 0;
            image(i, j, 1) = 0;
            image(i, j, 2) = 255;
        }
    }


    image.saveImage("iooi.png");
}