/*
This program will generate
 "Glowing Edge" effect.

*/

#include "PS_Algorithm.h"
#include <time.h>

using namespace std;
using namespace cv;

int main(void)
{
    string Img_name("4.jpg");
    Mat Image_in;
    Image_in=imread(Img_name);
    Show_Image(Image_in, Img_name);
    Mat Image_out(Image_in.size(), CV_32FC3);
    Image_in.convertTo(Image_out, CV_32FC3);

    Mat Image_2(Image_in.size(), CV_32FC3);
    Image_in.convertTo( Image_2, CV_32FC3);


     Mat kernel;
     Point anchor;
     double delta;
     int ddepth;
     int kernel_size;

     ddepth=-1;
     anchor=Point(-1,-1);
     delta=0;

     kernel_size=3;

     Mat K_x;
     Mat K_y;

     K_x=Mat::zeros(kernel_size, kernel_size, CV_32F);
     K_y=Mat::zeros(kernel_size, kernel_size, CV_32F);

     float p,q;

     p=3; q=0;

     K_x.at<float>(0,0)=-1;  K_x.at<float>(0,1)=0; K_x.at<float>(0,2)=1;
     K_x.at<float>(1,0)=-p;  K_x.at<float>(1,1)=q;  K_x.at<float>(1,2)=p;
     K_x.at<float>(2,0)=-1;  K_x.at<float>(2,1)=0;  K_x.at<float>(2,2)=1;

     K_y.at<float>(0,0)=-1; K_y.at<float>(0,1)=-p; K_y.at<float>(0,2)=-1;
     K_y.at<float>(1,0)=0;  K_y.at<float>(1,1)=q;  K_y.at<float>(1,2)=0;
     K_y.at<float>(2,0)=1;  K_y.at<float>(2,1)=p;  K_y.at<float>(2,2)=1;


     Mat Image_x(Image_in.size(), CV_32FC3);
     Mat Image_y(Image_in.size(), CV_32FC3);

     cv::filter2D(Image_2, Image_x, ddepth, K_x);
     cv::filter2D(Image_2, Image_y, ddepth, K_y);

     float alpha=0.5;

     Image_out=alpha*abs(Image_x)+(1-alpha)*abs(Image_y);

    Image_out=Image_out/255;

    Show_Image(Image_out, "out.jpg");

    imwrite("out.jpg", Image_out*255);

    waitKey();
    cout<<"All is well."<<endl;

}
