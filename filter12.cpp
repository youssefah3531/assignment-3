#include "Image_Class.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    Image image("building.jpg");
    Image image2(image.width, image.height);
    int width = image.width;
    int height = image.height;
    int size = 70;
    int half = size / 2;
    vector<vector<long long>> integralR(height + 1, vector<long long>(width + 1, 0));
    vector<vector<long long>> integralG(height + 1, vector<long long>(width + 1, 0));
    vector<vector<long long>> integralB(height + 1, vector<long long>(width + 1, 0));
    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            int px = x - 1; 
            int py = y - 1;
            long long vR = image(px, py, 0);
            long long vG = image(px, py, 1);
            long long vB = image(px, py, 2);
            integralR[y][x] = vR + integralR[y-1][x] + integralR[y][x-1] - integralR[y-1][x-1];
            integralG[y][x] = vG + integralG[y-1][x] + integralG[y][x-1] - integralG[y-1][x-1];
            integralB[y][x] = vB + integralB[y-1][x] + integralB[y][x-1] - integralB[y-1][x-1];
        }
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int x0 = max(0, x - half);
            int y0 = max(0, y - half);
            int x1 = min(width - 1, x + half);
            int y1 = min(height - 1, y + half);
            int X0 = x0;   
            int Y0 = y0;    
            int X1 = x1 + 1; 
            int Y1 = y1 + 1;
            long long totalR = integralR[Y1][X1] - integralR[Y0][X1] - integralR[Y1][X0] + integralR[Y0][X0];
            long long totalG = integralG[Y1][X1] - integralG[Y0][X1] - integralG[Y1][X0] + integralG[Y0][X0];
            long long totalB = integralB[Y1][X1] - integralB[Y0][X1] - integralB[Y1][X0] + integralB[Y0][X0];
            int area = (x1 - x0 + 1) * (y1 - y0 + 1);
            image2(x, y, 0) =(totalR / area);
            image2(x, y, 1) =(totalG / area);
            image2(x, y, 2) =(totalB / area);
        }
    }
    image2.saveImage("opopop.png");
    return 0;
}
