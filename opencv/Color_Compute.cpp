/*
This program will generate
 "diffuse or groundglass " effect.

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

    Mat r(Image_in.rows, Image_in.cols, CV_32FC1);
    Mat g(Image_in.rows, Image_in.cols, CV_32FC1);
    Mat b(Image_in.rows, Image_in.cols, CV_32FC1);

    Mat inp[]={b, g, r};

    split(Image_2, inp);

    Mat r_new(Image_in.rows, Image_in.cols, CV_32FC1);
    Mat g_new(Image_in.rows, Image_in.cols, CV_32FC1);
    Mat b_new(Image_in.rows, Image_in.cols, CV_32FC1);

    cv::pow(g-b, 2, r_new);
    cv::pow(r-b, 2, g_new);
    cv::pow(r-g, 2, b_new);

    r_new=r_new/128;
    g_new=g_new/128;
    b_new=b_new/128;

    Mat out[]={b_new, g_new, r_new};

    merge(out,3,Image_out);

    Image_out=Image_out/255;

    Show_Image(Image_out, "out.jpg");

    imwrite("out.jpg", Image_out*255);

    waitKey();
    cout<<"All is well."<<endl;

}
