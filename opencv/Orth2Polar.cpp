/*
This program will transform from the
orthogonal to polar coordinate.

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
    Show_Image(Img, Img_name);

    Mat Img_in(Img.size(), CV_32FC3);
    Img.convertTo(Img_in, CV_32FC3);

    Mat Img_out(Img_in.size(), CV_32FC3);
    Img_in.convertTo(Img_out, CV_32FC3);

    int width=Img_in.cols;
    int height=Img_in.rows;

    float R;
    float e;

    e=(float)width/(float)height;
    R=(float)height/2.0;

    Point Center(width/2, height/2);

    float R1, new_x, new_y;
    float p,q,x1,y1;
    float theta;

    for (int y=0; y<height; y++)
    {
        for (int x=0; x<width; x++)
        {

            theta=atan2((float)((Center.y-y)*e), (float)(x-Center.x+0.0001));

            if ((Center.y-y)<0) theta=theta+2*pi;

            R1=((Center.y-y)/sin(theta));
            new_y=R1*height/R;
            new_x=theta*width/(2*pi);

            if(new_x<0)        new_x=0;
            if(new_x>width-1)  new_x=width-2;
            if(new_y<0)        new_y=0;
            if(new_y>height-1) new_y=height-2;

            x1=(int)new_x;
            y1=(int)new_y;

            p=new_x-x1;
            q=new_y-y1;

            for (int k=0; k<3; k++)
            {
                Img_out.at<Vec3f>(y, x)[k]=(1-p)*(1-q)*Img_in.at<Vec3f>(y1, x1)[k]+
                                            (p)*(1-q)*Img_in.at<Vec3f>(y1,x1+1)[k]+
                                            (1-p)*(q)*Img_in.at<Vec3f>(y1+1,x1)[k]+
                                            (p)*(q)*Img_in.at<Vec3f>(y1+1,x1+1)[k];
            }

        }
    }

    Img_out=Img_out/255.0;
    Show_Image(Img_out, "out");

    imwrite("Out.jpg", Img_out*255);


    waitKey();

}
