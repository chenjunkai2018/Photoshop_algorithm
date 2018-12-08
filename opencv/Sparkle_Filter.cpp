/*

*/

#include "PS_Algorithm.h"
#include <time.h>

using namespace std;
using namespace cv;

#define pi 3.1415926

int main()
{
    string Img_name("4.jpg");
    Mat Img;
    Img=imread(Img_name);

    Mat Img_out(Img.size(), CV_8UC3);

    int width=Img.cols;
    int height=Img.rows;

    float rNW=1.0;     float gNW=0.0;    float bNW=0.0;
    float rNE=1.0;     float gNE=1.0;    float bNE=0.0;
    float rSW=0.0;     float gSW=0;      float bSW=1.0;
    float rSE=0.0;     float gSE=1.0;    float bSE=0.0;

    float fx, fy;
    float p, q, r, g, b;

    for (int y=0; y<height; y++)
    {
        for (int x=0; x<width; x++)
        {
            fx=(float)(x)/width;
            fy=(float)(y)/height;

            p = rNW + (rNE - rNW) * fx;
            q = rSW + (rSE - rSW) * fx;
            r = ( p + (q - p) * fy );
            r = min(max(r, 0.0f), 1.0f);

            p = gNW + (gNE - gNW) * fx;
            q = gSW + (gSE - gSW) * fx;
            g = ( p + (q - p) * fy );
            g = min(max(g, 0.0f) ,1.0f);

            p = bNW + (bNE - bNW) * fx;
            q = bSW + (bSE - bSW) * fx;
            b = ( p + (q - p) * fy );
            b = min(max(b, 0.0f), 1.0f);

            Img_out.at<Vec3b>(y, x)[0]=b*255.0;
            Img_out.at<Vec3b>(y, x)[1]=g*255.0;
            Img_out.at<Vec3b>(y, x)[2]=r*255.0;

        }
    }

    Show_Image(Img_out, "out");
    cout<<"All is well"<<endl;

   // imwrite("Out.jpg", Img_out);

    waitKey();
}

