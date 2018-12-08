/*
This program will do the computation
on three channels respectively, and generate
the "cast" effect.

*/

#include "PS_Algorithm.h"

using namespace std;
using namespace cv;

int main(void)
{

    string Img_name("4.jpg");

    Mat Image_in;
    Image_in=imread(Img_name);
    Show_Image(Image_in, Img_name);

    // split the three channels
    Mat Image_2(Image_in.size(), CV_32FC3);
    Image_in.convertTo( Image_2, CV_32FC3);

    Mat r(Image_in.rows, Image_in.cols, CV_32FC1);
    Mat g(Image_in.rows, Image_in.cols, CV_32FC1);
    Mat b(Image_in.rows, Image_in.cols, CV_32FC1);

    Mat out[]={b, g, r};

    split(Image_2, out);

    b=out[0]/255;
    g=out[1]/255;
    r=out[2]/255;

    // generate the new image
    Mat Image_new(Image_in.size(), CV_32FC3);
    Image_in.convertTo( Image_new, CV_32FC3);

    // generate new channels
    Mat r_new(Image_in.rows, Image_in.cols, CV_32FC1);
    Mat g_new(Image_in.rows, Image_in.cols, CV_32FC1);
    Mat b_new(Image_in.rows, Image_in.cols, CV_32FC1);


    float alpha;
    alpha=0.15;
    // cv::divide(r,(b+g+0.001),r_new, alpha);
    // cv::divide(g,(b+r+0.001),g_new, alpha);
    // cv::divide(b,(r+g+0.001),b_new, alpha);

    r_new=r*alpha/(b+g+0.001);
    g_new=g*alpha/(r+b+0.001);
    b_new=b*alpha/(r+g+0.001);

    Mat out_new[]={b_new, g_new, r_new};

    cv::merge(out_new, 3, Image_new);

    Show_Image(Image_new, "Img_out");

    // opencv will change the float single data to unit8 data.
    cv::imwrite("Img_new.jpg", Image_new*255);

    waitKey();

    cout<<"All is well \n";

}
