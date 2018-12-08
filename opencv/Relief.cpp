/*
This program will generate
 "Relief" effect.

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

     Mat K_1;

     K_1=Mat::zeros(kernel_size, kernel_size, CV_32F);

     float p;

     p=3;

     K_1.at<float>(0,2)=p;
     K_1.at<float>(2,0)=-p;


     Mat Image_x(Image_in.size(), CV_32FC3);

     cv::filter2D(Image_2, Image_x, ddepth, K_1);

     cv::add(Image_x, Scalar(128.0, 128.0, 128.0), Image_out);

    Image_out=Image_out/255;

    Show_Image(Image_out, "out.jpg");

    imwrite("out.jpg", Image_out*255);

    waitKey();
    cout<<"All is well."<<endl;

}
