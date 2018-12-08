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

    int n_point=1;

    float angle=60;

    float w=angle*3.1415926/180;
    float w_2=w*w;

    int Num=3;
    int Num2=Num*Num;

    Point Center(width/2, height/2);
    float t1, t2, t3;
    int x1, y1;
    int x2, y2;
    int new_x, new_y;

    for (int y=0; y<height; y++)
    {
        for (int x=0; x<width; x++)
        {
            n_point=1;
            x1=x-Center.x;
            y1=Center.y-y;

            t1=Img_in.at<Vec3b>(y, x)[0];
            t2=Img_in.at<Vec3b>(y, x)[1];
            t3=Img_in.at<Vec3b>(y, x)[2];

            x2=x1; y2=y1;

            for (int mm=0; mm<Num; mm++)
            {
                x1=x2;
                y1=y2;

                // anticlockwise
                x2=x1-w*y1/Num-w_2*x1/Num2;
                y2=y1+w*x1/Num-w_2*y1/Num2;

                // clockwise
                //x2=x1+w*y1/Num-w_2*x1/Num2;
                //y2=y1-w*x1/Num-w_2*y1/Num2;

                new_x=x2+Center.x;
                new_y=Center.y-y2;

                if (new_x>0 && new_x<width-1 && new_y>0 && new_y<height-1)
                {
                    t1=t1+Img_in.at<Vec3b>(new_y, new_x)[0];
                    t2=t2+Img_in.at<Vec3b>(new_y, new_x)[1];
                    t3=t3+Img_in.at<Vec3b>(new_y, new_x)[2];
                    n_point++;
                }

            }

            Img_out.at<Vec3f>(y, x)[0]=t1/n_point;
            Img_out.at<Vec3f>(y, x)[1]=t2/n_point;
            Img_out.at<Vec3f>(y, x)[2]=t3/n_point;

        }
    }

    Img_out=Img_out/255.0;
    Show_Image(Img_out, "out");

    imwrite("Out.jpg", Img_out*255);

    waitKey();

}
