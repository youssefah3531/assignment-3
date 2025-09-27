#include "Image_Class.h"
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
string newfilename;
void Invert_Image(string filepath )
{
    Image image(filepath);
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
    cout<<"Do you want to save the photo?\n1-YES\n2-NO"<<endl;
    int num;
    cin>>num;
    if (num==1)
    {
        cout<<"Enter the name of the new file with its extention: "<<endl;
        cin>>newfilename;
        image.saveImage(newfilename);
    }
    if (num=2)
    {
        cout<<"KOSOMK";
    }
    
}
void Rotate_Image(string filepath)
{
    int degree;
    cout<<"How many degree do you want to rotate the photo?"<<endl;
    cin>>degree;
    if (degree==90)
    {
    Image image(filepath);
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
    cout<<"Do you want to save the photo?\n1-YES\n2-NO"<<endl;
    int num;
    cin>>num;
    if (num==1)
    {
        cout<<"Enter the name of the new file with its extention: "<<endl;
        cin>>newfilename;
        image.saveImage(newfilename);
    }
    if (num=2)
    {
        cout<<"KOSOMK";
    }
    
    }
    
}



int main(){
    cout<<"#####################################################"<<endl;
    cout<<"##########Welcome to our filter Application##########"<<endl;
    cout<<"#####################################################"<<endl;
    cout<<"Please load the photo (enter the full path of image): "<<endl;
    string filepath;
    int num;
    getline(cin, filepath);
    cout<<"Which filter do you want?"<<endl;
    cout<<"1-Grey Scale\n2-Black and White\n3-Invert Image\n4-Merge Images\n5-Flip Image\n6-Rotate Image"<<endl;
    cin>>num;
    if (num==3)
    {
        Invert_Image(filepath);
    }
    if (num==6)
    {
        Rotate_Image(filepath);
    }
    
}