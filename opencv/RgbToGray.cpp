/*
The program will transfor the color
image to the gray image.
The image must be color image.
*/

#include "PS_Algorithm.h"

int main()
{
    string  Image_name("2.jpg");
    Mat Image=imread(Image_name.c_str());
    Mat Image_test(Image.size(),CV_32FC3);
    Image.convertTo(Image_test, CV_32FC3);

    Mat Gray_img(Image_test.size(), CV_32FC1);
    Mat r,g,b;
    Gray_img.copyTo(r);
    g=r;
    b=r;

    Mat bgr[]={b,g,r};

    split(Image_test, bgr);

    b=bgr[0];
    g=bgr[1];
    r=bgr[2];

    Mat I1,I2,I3;
    I1=r;
    I2=r;
    I3=r;

/*
    // I=0.299*R+0.587*G+0.144*B
    Gray_img=(0.299*r+0.587*g+0.144*b);
    I1=Gray_img/255;
    namedWindow("I1",CV_WINDOW_AUTOSIZE);
    imshow("I1", I1);
*/


    // I=(R+G+B)/3
    Gray_img=(0.333*r+0.333*g+0.333*b);
    I2=Gray_img/255;
    namedWindow("I2",CV_WINDOW_AUTOSIZE);
    imshow("I2", I2);


/*
    // I=max(R,G,B)
    float *p1,*p2,*p3,*p;
    p1=r.ptr<float>(0);
    p2=g.ptr<float>(0);
    p3=b.ptr<float>(0);
    p=I3.ptr<float>(0);
    int nums;
    nums=Gray_img.rows*Gray_img.cols;
    for (int i=0; i<nums; i++)
        p[i]=max(p1[i],max(p2[i],p3[i]))/255;
    namedWindow("I3",CV_WINDOW_AUTOSIZE);
    imshow("I3",I3);
*/

    cout<<"All is well."<<endl;
    waitKey();
}
