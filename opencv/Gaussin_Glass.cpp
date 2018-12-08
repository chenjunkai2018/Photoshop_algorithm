/*
This program will generate
gaussian blur and glass  effect

*/

#include "PS_Algorithm.h"
#include <time.h>

using namespace std;
using namespace cv;

int main()
{
    string Img_name("4.jpg");
    Mat Img_in;
    Img_in=imread(Img_name);
    Show_Image(Img_in, Img_name);

    Mat Img_out(Img_in.size(), CV_32FC3);
    Img_in.convertTo(Img_out, CV_32FC3);

    Mat temp;
    temp=Img_out.rowRange(150, 220);

    cv::GaussianBlur(temp, temp, Size(11,11), 0, 0);
    cv::GaussianBlur(temp, temp, Size(11,11), 0, 0);

    Img_out=Img_out/255.0;
    Show_Image(Img_out, "out");

    imwrite("Out.jpg", Img_out*255);

    waitKey();

}
