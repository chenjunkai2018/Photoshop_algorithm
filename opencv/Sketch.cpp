/*
This program will generate
 "Sketch" effect.

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
    // Show_Image(Image_in, Img_name);

    Mat Image_out(Image_in.size(), CV_32FC3);
    Image_in.convertTo(Image_out, CV_32FC3);

    Mat I(Image_in.size(), CV_32FC1);

    cv::cvtColor(Image_out, I, CV_BGR2GRAY);
    I=I/255.0;
    // Show_Image(I, "gray");

    Mat I_invert;
    I_invert=-I+1.0;
    // Show_Image(I_invert, "Inv");

    Mat I_gau;
    GaussianBlur(I_invert, I_gau, Size(25,25), 0, 0);
    //Show_Image(I_gau, "gau1");

    float delta=0.01;
    I_gau=-I_gau+1.0+delta;
    //Show_Image(I_gau, "gau");

    Mat I_dst;
    cv::divide(I, I_gau, I_dst);
    I_dst=I_dst;
    Show_Image(I_dst, "dst");

    Mat b(Image_in.size(), CV_32FC1);
    Mat g(Image_in.size(), CV_32FC1);
    Mat r(Image_in.size(), CV_32FC1);

    Mat rgb[]={b,g,r};

    float alpha=0.75;

    r=alpha*I_dst+(1-alpha)*200.0/255.0;
    g=alpha*I_dst+(1-alpha)*205.0/255.0;
    b=alpha*I_dst+(1-alpha)*105.0/255.0;

    cv::merge(rgb, 3, Image_out);

    Show_Image(Image_out, "out");

    imwrite("out.jpg", Image_out*255);

    waitKey();
    cout<<"All is well."<<endl;

}
