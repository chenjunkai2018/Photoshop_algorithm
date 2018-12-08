/*
The program will process the neighborhood of
a pixel in the image.
The image could be gray or color image.
*/

#include "PS_Algorithm.h"

int main()
{
    string  Image_name("2.jpg");
    Mat Image=imread(Image_name.c_str());
    Mat Image_test(Image.size(),CV_32FC3);
    Image.convertTo(Image_test, CV_32FC3);

    Mat sub_img;
    sub_img=Image_test.operator()(Range(100,200), Range(100,200))/255;

    Show_Image(Image, Image_name);
    Show_Image(sub_img, "sub_img");
    waitKey();
}

