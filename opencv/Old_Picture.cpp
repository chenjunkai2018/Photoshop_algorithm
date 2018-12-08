/*
This program will generate
 "Old Picture" effect.

*/

#include "PS_Algorithm.h"
#include <time.h>

using namespace std;
using namespace cv;

int main(void)
{
    string Img_name("9.jpg");
    Mat Image_in;
    Image_in=imread(Img_name);
    Show_Image(Image_in, Img_name);
    Mat Image_out(Image_in.size(), CV_32FC3);
    Image_in.convertTo(Image_out, CV_32FC3);

    Mat Image_2(Image_in.size(), CV_32FC3);
    Image_in.convertTo( Image_2, CV_32FC3);

    Mat r(Image_in.rows, Image_in.cols, CV_32FC1);
    Mat g(Image_in.rows, Image_in.cols, CV_32FC1);
    Mat b(Image_in.rows, Image_in.cols, CV_32FC1);

    Mat out[]={b, g, r};

    split(Image_2, out);

    Mat r_new(Image_in.rows, Image_in.cols, CV_32FC1);
    Mat g_new(Image_in.rows, Image_in.cols, CV_32FC1);
    Mat b_new(Image_in.rows, Image_in.cols, CV_32FC1);

    r_new=0.393*r+0.769*g+0.189*b;
    g_new=0.349*r+0.686*g+0.168*b;
    b_new=0.272*r+0.534*g+0.131*b;

    Mat rgb[]={b_new, g_new, r_new};

    merge(rgb,3,Image_out);

    Image_out=Image_out/255;

    Show_Image(Image_out, "out.jpg");

    imwrite("out.jpg", Image_out*255);

    waitKey();
    cout<<"All is well."<<endl;

}
