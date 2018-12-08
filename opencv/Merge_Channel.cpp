/*
The program will merge several single-channel arrays
into a multi-channel array.
*/

#include "PS_Algorithm.h"

using namespace std;
using namespace cv;

int main()
{
    Mat r(600,400, CV_32FC1);
    Mat g(r.size(),r.type());
    Mat b(r.size(),r.type());

    Mat Ones_matrix=Mat::ones(r.size(),r.type());

    g=g+Ones_matrix;

    Mat rgb[]={b,g,r};

    Mat Image(r.size(),CV_32FC3);

    merge(rgb,3,Image);

    Show_Image(Image, "Image");

    waitKey();
}
