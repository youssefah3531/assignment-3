// #######################################################################################################################################
// Name                                                       id                                             Filters
// Youssef Ahmed Hussien                                      20240675                             Invert Image,Rotate Image,Add Frame,Blur Image
// Ahmed Ahmed Abdelmotelb                                    20240009                             Grey Scale,Merge Image,Darken and Lighten Image
// Moataz Mohamed Abdo                                        20240607                           Black and white,Flib Image,Crop Image,Resize Image
//                                                            Section 8
// ######################################################################################################################################
#include "Image_Class.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
string newfilename;
void Grayscale_Conversion(string &filepath)
{
    Image image(filepath);
    for (int i = 0; i < image.width; i++)
    {

        for (int j = 0; j < image.height; j++)
        {

            unsigned int avg = 0;
            for (int k = 0; k < 3; k++)
            {

                avg += image(i, j, k);
            }

            avg = avg / 3;

            for (int k = 0; k < 3; k++)
            {

                image(i, j, k) = avg;
            }
        }
    }
    cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
    int num;
    cin >> num;
    if (num == 1)
    {
        cout << "Enter the name of the new file with its extention: " << endl;
        cin >> newfilename;
        image.saveImage(newfilename);
        cout << "Image saved sucessfully\n";
    }
}
void blackandwhite(string &filepath)
{
    Image image(filepath);
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            unsigned int avg = 0;
            for (int k = 0; k < 3; k++)
            {
                avg += image(i, j, k);
            }
            avg /= 3;
            if (avg < 127)
            {
                for (int k = 0; k < 3; k++)
                    image(i, j, k) = 0;
            }
            else
                for (int k = 0; k < 3; k++)
                    image(i, j, k) = 255;
        }
    }
    cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
    int num;
    cin >> num;
    if (num == 1)
    {
        cout << "Enter the name of the new file with its extention: " << endl;
        cin >> newfilename;
        image.saveImage(newfilename);
        cout << "Image saved sucessfully\n";
    }
}
void Invert_Image(string &filepath)
{
    Image image(filepath);
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            unsigned int R = 0;
            unsigned int G = 0;
            unsigned int B = 0;
            R = 255 - image(i, j, 0);
            G = 255 - image(i, j, 1);
            B = 255 - image(i, j, 2);
            image(i, j, 0) = R;
            image(i, j, 1) = G;
            image(i, j, 2) = B;
        }
    }
    cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
    int num;
    cin >> num;
    if (num == 1)
    {
        cout << "Enter the name of the new file with its extention: " << endl;
        cin >> newfilename;
        image.saveImage(newfilename);
        cout << "Image saved sucessfully\n";
    }
}
void Merge_Images(string &filepath, string &filepath2)
{
    Image img1(filepath);

    Image img2(filepath2);

    int w = min(img1.width, img2.width);

    int h = min(img1.height, img2.height);

    Image img(w, h);

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            unsigned int R = 0;
            unsigned int G = 0;
            unsigned int B = 0;
            R = img1(i, j, 0) + img2(i, j, 0);
            R = R / 2;
            G = img1(i, j, 1) + img2(i, j, 1);
            G = G / 2;
            B = img1(i, j, 2) + img2(i, j, 2);
            B = B / 2;
            img(i, j, 0) = R;
            img(i, j, 1) = G;
            img(i, j, 2) = B;
        }
    }
    cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
    int num;
    cin >> num;
    if (num == 1)
    {
        cout << "Enter the name of the new file with its extention: " << endl;
        cin >> newfilename;
        img.saveImage(newfilename);
        cout << "Image saved sucessfully\n";
    }
}
void flipimage(string &filepath)
{
    Image image(filepath);
    cout << "Do you want to flip the photo?\n1-Vertically\n2-Horizontally" << endl;
    int num;
    cin >> num;
    if (num == 1)
    {

        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height / 2; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    unsigned int ref = image(i, j, k);
                    image(i, j, k) = image(i, image.height - j - 1, k);
                    image(i, image.height - j - 1, k) = ref;
                }
            }
        }
        cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
        int num;
        cin >> num;
        if (num == 1)
        {
            cout << "Enter the name of the new file with its extention: " << endl;
            cin >> newfilename;
            image.saveImage(newfilename);
            cout << "Image saved sucessfully\n";
        }
    }
    else
    {
        for (int i = 0; i < image.width / 2; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    unsigned int ref = image(i, j, k);
                    image(i, j, k) = image(image.width - i - 1, j, k);
                    image(image.width - i - 1, j, k) = ref;
                }
            }
        }
        cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
        int num;
        cin >> num;
        if (num == 1)
        {
            cout << "Enter the name of the new file with its extention: " << endl;
            cin >> newfilename;
            image.saveImage(newfilename);
            cout << "Image saved sucessfully\n";
        }
    }
}
void Rotate_Image_90(string &filepath)
{
    Image image(filepath);
    Image image2(image.height, image.width);
    int k = 0;
    int l = 0;
    for (int i = 0; i < image.width; i++)
    {
        for (int j = image.height - 1; j >= 0; j--)
        {
            image2(k, l, 0) = image(i, j, 0);
            image2(k, l, 1) = image(i, j, 1);
            image2(k, l, 2) = image(i, j, 2);
            k++;
        }
        k = 0;
        l++;
    }
    cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
    int num;
    cin >> num;
    if (num == 1)
    {
        cout << "Enter the name of the new file with its extention: " << endl;
        cin >> newfilename;
        image2.saveImage(newfilename);
        cout << "Image saved sucessfully\n";
    }
}
void Rotate_Image_180(string &filepath)

{
    Image image(filepath);
    Image image2(image.height, image.width);
    Image image3(image.width, image.height);
    int k = 0;
    int l = 0;
    for (int i = 0; i < image.width; i++)
    {
        for (int j = image.height - 1; j >= 0; j--)
        {
            image2(k, l, 0) = image(i, j, 0);
            image2(k, l, 1) = image(i, j, 1);
            image2(k, l, 2) = image(i, j, 2);
            k++;
        }
        k = 0;
        l++;
    }
    k = 0;
    l = 0;
    for (int i = 0; i < image2.width; i++)
    {
        for (int j = image2.height - 1; j >= 0; j--)
        {
            image3(k, l, 0) = image2(i, j, 0);
            image3(k, l, 1) = image2(i, j, 1);
            image3(k, l, 2) = image2(i, j, 2);
            k++;
        }
        k = 0;
        l++;
    }
    cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
    int num;
    cin >> num;
    if (num == 1)
    {
        cout << "Enter the name of the new file with its extention: " << endl;
        cin >> newfilename;
        image3.saveImage(newfilename);
        cout << "Image saved sucessfully\n";
    }
}
void Rotate_Image_270(string &filepath)
{
    Image image(filepath);
    Image image2(image.height, image.width);
    Image image3(image.width, image.height);
    Image image4(image.height, image.width);
    int k = 0;
    int l = 0;
    for (int i = 0; i < image.width; i++)
    {
        for (int j = image.height - 1; j >= 0; j--)
        {
            image2(k, l, 0) = image(i, j, 0);
            image2(k, l, 1) = image(i, j, 1);
            image2(k, l, 2) = image(i, j, 2);
            k++;
        }
        k = 0;
        l++;
    }
    k = 0;
    l = 0;
    for (int i = 0; i < image2.width; i++)
    {
        for (int j = image2.height - 1; j >= 0; j--)
        {
            image3(k, l, 0) = image2(i, j, 0);
            image3(k, l, 1) = image2(i, j, 1);
            image3(k, l, 2) = image2(i, j, 2);
            k++;
        }
        k = 0;
        l++;
    }
    k = 0;
    l = 0;
    for (int i = 0; i < image3.width; i++)
    {
        for (int j = image3.height - 1; j >= 0; j--)
        {
            image4(k, l, 0) = image3(i, j, 0);
            image4(k, l, 1) = image3(i, j, 1);
            image4(k, l, 2) = image3(i, j, 2);
            k++;
        }
        k = 0;
        l++;
    }
    cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
    int num;
    cin >> num;
    if (num == 1)
    {
        cout << "Enter the name of the new file with its extention: " << endl;
        cin >> newfilename;
        image4.saveImage(newfilename);
        cout << "Image saved sucessfully\n";
    }
}
void Darken_Image(string &filepath)
{
    Image image(filepath);

    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                image(i, j, k) = image(i, j, k) * 0.5;
            }
        }
    }

    cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
    int num;
    cin >> num;
    if (num == 1)
    {
        cout << "Enter the name of the new file with its extention: " << endl;
        cin >> newfilename;
        image.saveImage(newfilename);
        cout << "Image saved sucessfully\n";
    }
}
void Lighten_Image(string &filepath)
{
    Image image(filepath);

    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                int new_value = image(i, j, k) * 1.5;
                if (new_value > 255)
                    new_value = 255;

                image(i, j, k) = new_value;
            }
        }
    }
    cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
    int num;
    cin >> num;
    if (num == 1)
    {
        cout << "Enter the name of the new file with its extention: " << endl;
        cin >> newfilename;
        image.saveImage(newfilename);
        cout << "Image saved sucessfully\n";
    }
}
void Crop(string &filepath, int x, int y, int w, int h)
{
    Image image(filepath);
    if (x + w > image.width)
        w = image.width - x;
    if (y + h > image.height)
        h = image.height - y;
    Image Cropedimg(w, h);
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                Cropedimg(i, j, k) = image(x + i, y + j, k);
            }
        }
    }
    cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
    int num;
    cin >> num;
    if (num == 1)
    {
        cout << "Enter the name of the new file with its extention: " << endl;
        cin >> newfilename;
        Cropedimg.saveImage(newfilename);
        cout << "Image saved sucessfully\n";
    }
}
void Add_Frame(string &filepath)
{
    Image image(filepath);
    for (int i = 0; i < image.width / 35; i++)
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
        for (int j = 0; j < image.height / 45; j++)
        {
            unsigned int R = 0;
            unsigned int G = 0;
            unsigned int B = 0;
            image(i, j, 0) = 0;
            image(i, j, 1) = 0;
            image(i, j, 2) = 255;
        }
    }
    for (int i = image.width - 1; i > image.width / 1.03; i--)
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
    for (int j = image.height - 1; j > image.height / 1.026; j--)
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
    cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
    int num;
    cin >> num;
    if (num == 1)
    {
        cout << "Enter the name of the new file with its extention: " << endl;
        cin >> newfilename;
        image.saveImage(newfilename);
        cout << "Image saved sucessfully\n";
    }
}
void Detect_Image_Edges(string &filepath)
{
    Image image(filepath);
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            unsigned char avg = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
    Image edgeImage = image;
    for (int i = 0; i < image.width - 1; i++)
    {
        for (int j = 0; j < image.height - 1; j++)
        {
            int current = image(i, j, 0);
            int right = image(i + 1, j, 0);
            int bottom = image(i, j + 1, 0);
            int edge_strength = abs(current - right) + abs(current - bottom);
            edge_strength *= 2;
            if (edge_strength > 255)
                edge_strength = 255;
            int inverted = 255 - edge_strength;
            edgeImage(i, j, 0) = inverted;
            edgeImage(i, j, 1) = inverted;
            edgeImage(i, j, 2) = inverted;
        }
    }
    cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
    int num;
    cin >> num;
    if (num == 1)
    {
        cout << "Enter the name of the new file with its extention: " << endl;
        cin >> newfilename;
        edgeImage.saveImage(newfilename);
        cout << "Image saved sucessfully\n";
    }
}
void resize_func(string &filepath, float w, float h)
{
    Image image(filepath);
    Image Resizedimg(w, h);
    float ratio_x = image.width / w;
    float ratio_y = image.height / h;
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                Resizedimg(i, j, k) = image(i * ratio_x, j * ratio_y, k);
            }
        }
    }
    cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
    int num;
    cin >> num;
    if (num == 1)
    {
        cout << "Enter the name of the new file with its extention: " << endl;
        cin >> newfilename;
        Resizedimg.saveImage(newfilename);
        cout << "Image saved sucessfully\n";
    }
}
void Blur_Image(string &filepath)
{   
    Image image(filepath);
    Image image2(image.width, image.height);
    int width = image.width;
    int height = image.height;
    int size = 70;
    int half = size / 2;
    vector<vector<long long>> integralR(height + 1, vector<long long>(width + 1, 0));
    vector<vector<long long>> integralG(height + 1, vector<long long>(width + 1, 0));
    vector<vector<long long>> integralB(height + 1, vector<long long>(width + 1, 0));
    for (int y = 1; y <= height; y++)
    {
        for (int x = 1; x <= width; x++)
        {
            int px = x - 1;
            int py = y - 1;
            long long vR = image(px, py, 0);
            long long vG = image(px, py, 1);
            long long vB = image(px, py, 2);
            integralR[y][x] = vR + integralR[y - 1][x] + integralR[y][x - 1] - integralR[y - 1][x - 1];
            integralG[y][x] = vG + integralG[y - 1][x] + integralG[y][x - 1] - integralG[y - 1][x - 1];
            integralB[y][x] = vB + integralB[y - 1][x] + integralB[y][x - 1] - integralB[y - 1][x - 1];
        }
    }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
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
            image2(x, y, 0) = (totalR / area);
            image2(x, y, 1) = (totalG / area);
            image2(x, y, 2) = (totalB / area);
        }
    }
    cout << "Do you want to save the photo?\n1-YES\n2-NO" << endl;
    int num;
    cin >> num;
    if (num == 1)
    {
        cout << "Enter the name of the new file with its extention: " << endl;
        cin >> newfilename;
        image2.saveImage(newfilename);
        cout << "Image saved sucessfully\n";
    }
}
int main()
{
    int cont = 1;
    while (cont == 1)
    {
        cout << "#####################################################" << endl;
        cout << "##########Welcome to our filter Application##########" << endl;
        cout << "#####################################################" << endl;
        cout << "Which filter do you want?" << endl;
        cout << "1-Grey Scale\n2-Black and White\n3-Invert Image\n4-Merge Images\n5-Flip Image\n6-Rotate Image\n7-Darken and Lighten Image\n8-Crop Images\n9-Add Frame\n10-Detect Image Edges\n11-Resizing Images\n12-Blur Image" << endl;
        string filepath = "";
        string filepath2 = "";
        int num;
        cin >> num;
        cout << "Please load the photo (enter the full path of image): " << endl;
        if (num == 1)
        {
            getline(cin >> ws, filepath);
            Grayscale_Conversion(filepath);
        }
        if (num == 2)
        {
            getline(cin >> ws, filepath);
            blackandwhite(filepath);
        }
        if (num == 3)
        {
            getline(cin >> ws, filepath);
            Invert_Image(filepath);
        }
        if (num == 4)
        {
            getline(cin >> ws, filepath);
            getline(cin >> ws, filepath2);
            Merge_Images(filepath, filepath2);
        }
        if (num == 5)
        {
            getline(cin >> ws, filepath);
            flipimage(filepath);
        }
        if (num == 6)
        {
            getline(cin >> ws, filepath);
            int degree_rotation;
            cout << "How many degrees do you want to rotate the image?\n";
            cin >> degree_rotation;
            if (degree_rotation == 90)
            {
                Rotate_Image_90(filepath);
            }
            if (degree_rotation == 180)
            {
                Rotate_Image_180(filepath);
            }
            if (degree_rotation == 270)
            {
                Rotate_Image_270(filepath);
            }
        }
        if (num == 7)
        {
            getline(cin >> ws, filepath);
            int Darker_Or_Lighter;
            cout << "Do You Want The Image Darker Or Lighter?\n1-Darker\n2-Lighter" << endl;
            cin >> Darker_Or_Lighter;
            if (Darker_Or_Lighter == 1)
            {
                Darken_Image(filepath);
            }
            if (Darker_Or_Lighter == 2)
            {
                Lighten_Image(filepath);
            }
        }

        if (num == 8)
        {
            getline(cin >> ws, filepath);
            int x, y, w, h;
            cout << "Enter starting points (x,y)\nx = ";
            cin >> x;
            cout << "y = ";
            cin >> y;
            cout << "Enter the width and the height of the croped photo\nW = ";
            cin >> w;
            cout << "H = ";
            cin >> h;
            Crop(filepath, x, y, w, h);
        }
        if (num == 9)
        {
            getline(cin >> ws, filepath);
            Add_Frame(filepath);
        }
        if (num == 10)
        {
            getline(cin >> ws, filepath);
            Detect_Image_Edges(filepath);
        }

        if (num == 11)
        {
            getline(cin >> ws, filepath);
            float w, h;
            cout << "Enter the width and the height to the new dimentions photo\nW = ";
            cin >> w;
            cout << "H = ";
            cin >> h;
            resize_func(filepath, w, h);
        }
        if (num == 12)
        {
            getline(cin >> ws, filepath);
            Blur_Image(filepath);
        }
        cout << "Do you want to add another image?\n1-YES\n2-NO" << endl;
        cin >> cont;
        if (cont == 2)
        {
            break;
        }
    }
}