/*
This program will generate the garland.

*/

#include "PS_Algorithm.h"
#include <time.h>

using namespace std;
using namespace cv;

#define pi 3.1415926

int main()
{

    Mat Img(400,600, CV_32FC3);

    int width=Img.cols;
    int height=Img.rows;

    Point Center(width/2, height/2);

    int k=6;
    int N=720;
    float R=150.0;
    float dn;

    dn=360.0/N;
    float theta;
    float r;
    float x,y;
    float new_x, new_y;

    for (int i=0; i<=N; i++)
    {
        theta=(i*dn)*pi/180.0;
        r=R*sin(k*theta);
        x=(r*cos(theta));
        y=(r*sin(theta));
        new_y=(int)(Center.y-y);
        new_x=(int)(Center.x+x);
        Img.at<Vec3f>(new_y, new_x)[0]=1;
        Img.at<Vec3f>(new_y, new_x)[1]=1;
        Img.at<Vec3f>(new_y, new_x)[2]=1;

    }

    Show_Image(Img, "out");

    imwrite("Out.jpg", Img*255);

    waitKey();

}
