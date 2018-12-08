
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
    Img.copyTo(Img_out);

    int width=Img.cols;
    int height=Img.rows;
    float A,B;
    A=7;
    B=2.5;

    Point Center(width/2, height/2);

    float r0,r1,new_x,new_y;
    float p,q,x1,y1,x0,y0;
    float theta;

    for (int y=0; y<height; y++)
    {
        for (int x=0; x<width; x++)
        {
            y0=Center.y-y;
            x0=x-Center.x;
            theta=atan(y0/(x0+0.00001));
            if(x0<0) theta=theta+pi;
            r0=sqrt(x0*x0+y0*y0);
            r1=r0+A*width*0.01*sin(B*0.1*r0);

            new_x=r1*cos(theta);
            new_y=r1*sin(theta);

            new_x=Center.x+new_x;
            new_y=Center.y-new_y;

            if(new_x<0)         new_x=0;
            if(new_x>=width-1)  new_x=width-2;
            if(new_y<0)         new_y=0;
            if(new_y>=height-1) new_y=height-2;

            x1=(int)new_x;
            y1=(int)new_y;

            p=new_x-x1;
            q=new_y-y1;

            for (int k=0; k<3; k++)
            {
                Img_out.at<Vec3b>(y, x)[k]=(1-p)*(1-q)*Img.at<Vec3b>(y1, x1)[k]+
                                        (p)*(1-q)*Img.at<Vec3b>(y1,x1+1)[k]+
                                        (1-p)*(q)*Img.at<Vec3b>(y1+1,x1)[k]+
                                        (p)*(q)*Img.at<Vec3b>(y1+1,x1+1)[k];
            }

        }
    }

    Img_out=Img_out;
    Show_Image(Img_out, "out");

    imwrite("Out.jpg", Img_out);


    waitKey();

}
