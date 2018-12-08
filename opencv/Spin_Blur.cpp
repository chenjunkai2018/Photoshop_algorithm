/*
This program will generate
spin blur effect
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

    int width=Img_in.cols;
    int height=Img_in.rows;

    float R;
    float angle;

    Point Center(width/2, height/2);
    float t1, t2, t3;
    int new_x, new_y;

    int Num=20;

    for (int y=0; y<height; y++)
    {
        for (int x=0; x<width; x++)
        {
            t1=0; t2=0; t3=0;
            R=sqrt((y-Center.y)*(y-Center.y)+(x-Center.x)*(x-Center.x));
            angle=atan2((float)(y-Center.y), (float)(x-Center.x));

            for (int mm=0; mm<Num; mm++)
            {
                angle=angle+0.01;

                new_x=R*cos(angle)+Center.x;
                new_y=R*sin(angle)+Center.y;

                if(new_x<0)       new_x=0;
                if(new_x>width-1) new_x=width-1;
                if(new_y<0)       new_y=0;
                if(new_y>height-1)new_y=height-1;

                t1=t1+Img_in.at<Vec3b>(new_y, new_x)[0];
                t2=t2+Img_in.at<Vec3b>(new_y, new_x)[1];
                t3=t3+Img_in.at<Vec3b>(new_y, new_x)[2];

            }

            Img_out.at<Vec3f>(y, x)[0]=t1/Num;
            Img_out.at<Vec3f>(y, x)[1]=t2/Num;
            Img_out.at<Vec3f>(y, x)[2]=t3/Num;

        }
    }

    Img_out=Img_out/255.0;
    Show_Image(Img_out, "out");

    imwrite("Out.jpg", Img_out*255);

    waitKey();

}
