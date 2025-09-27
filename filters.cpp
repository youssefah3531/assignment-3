#include "Image_Class.h"
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    Image image("building.jpg");
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            unsigned char R = image(x,y,0);
            unsigned char G = image(x,y,1);
            unsigned char B = image(x,y,2);

            int gray_i = lround(0.299 * R + 0.587 * G + 0.114 * B);
            if (gray_i < 0) gray_i = 0;
            if (gray_i > 255) gray_i = 255;
            unsigned char gray = static_cast<unsigned char>(gray_i);

            image(x,y,0) = gray;
            image(x,y,1) = gray;
            image(x,y,2) = gray;
        }
    }

    image.saveImage("building_gray.png");
    return 0;
}
