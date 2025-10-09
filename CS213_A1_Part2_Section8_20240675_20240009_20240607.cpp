// #######################################################################################################################################
// Name                                                       id                                             Filters
// Youssef Ahmed Hussien                                      20240675                             Invert Image and Rotate Image
// Ahmed Ahmed Abdelmotelb                                    20240009                              Grey Scale and Merge Image
// Moataz Mohamed Abdo                                        20240607                             Black and white and Flib Image
//                                                            Section 8
// ######################################################################################################################################
#include "Image_Class.h"
#include <cmath>
#include <algorithm>
#include <iostream>
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
void Blur_Image(string &filepath)
{
    Image image(filepath);
    Image image2(image.width, image.height);
    for (int i = 20; i < image.width - 20; i++)
    {
        for (int j = 20; j < image.height - 20; j++)
        {
            int R = 0;
            int G = 0;
            int B = 0;
            for (int k = i - 20; k < i + 20; k++)
            {
                for (int l = j - 20; l < j + 20; l++)
                {
                    R += image(k, l, 0);
                    G += image(k, l, 1);
                    B += image(k, l, 2);
                }
            }
            R /= 1600;
            G /= 1600;
            B /= 1600;
            image2(i, j, 0) = R;
            image2(i, j, 1) = G;
            image2(i, j, 2) = B;
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
        cout << "1-Grey Scale\n2-Black and White\n3-Invert Image\n4-Merge Images\n5-Flip Image\n6-Rotate Image\n9-Add Frame\n12-Blur Image" << endl;
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
        if (num == 9)
        {
            getline(cin >> ws, filepath);
            Add_Frame(filepath);
        }
        if (num==12)
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