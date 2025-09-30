#include "Image_Class.h"
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
string newfilename;
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
void flipimage(string &filepath)
{
    Image image(filepath);
    cout << "Do you want to flip the photo?\n1-Vertically\n2-Horizontally"<<endl;
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

int main()
{
    int cont = 1;
    while (cont == 1)
    {
        cout << "#####################################################" << endl;
        cout << "##########Welcome to our filter Application##########" << endl;
        cout << "#####################################################" << endl;
        cout << "Please load the photo (enter the full path of image): " << endl;
        string filepath = "";
        int num;
        getline(cin >> ws, filepath);
        cout << "Which filter do you want?" << endl;
        cout << "1-Grey Scale\n2-Black and White\n3-Invert Image\n4-Merge Images\n5-Flip Image\n6-Rotate Image" << endl;
        cin >> num;
        if (num == 2)
        {
            blackandwhite(filepath);
        }
        if (num == 3)
        {
            Invert_Image(filepath);
        }
        if (num == 5)
        {
            flipimage(filepath);
        }
        if (num == 6)
        {
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
        cout << "Do you want to add another image?\n1-YES\n2-NO"<<endl;
        cin >> cont;
        if (cont == 2)
        {
            break;
        }
    }
}