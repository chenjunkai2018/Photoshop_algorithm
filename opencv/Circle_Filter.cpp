/*

generate the circle transform
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

    float angle = 0;
    float centreX = 0.5;
    float centreY = 1.0;
    float radius = 150;
    float high=200;
    float spreadAngle=pi;

    float icentreX=width*centreX;
    float icentreY=height*centreY;
    float radius2=radius*radius;

    float dx,dy,new_x,new_y;
    float p,q,x1,y1;
    float r, theta;

    for (int y=0; y<height; y++)
    {
        for (int x=0; x<width; x++)
        {

             dx=x-icentreX;
             dy=y-icentreY;

             theta=atan2(-dy, -dx)+angle;
             r=sqrt(dy*dy+dx*dx);

            theta=std::fmod(theta,(float)2*pi);

            new_x=width * theta/(spreadAngle+0.00001);
            new_y=height * (1-(r-radius)/(high+0.00001));

          //  if(new_x<0)         new_x=0;
          //  if(new_x>=width-1)  new_x=width-2;
          //  if(new_y<0)         new_y=0;
          //  if(new_y>=height-1) new_y=height-2;

            if (new_x<0)     continue;
            if (new_x>=width-1)   continue;
            if (new_y>=height-1)  continue;
            if (new_y<0)  continue;

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

    Show_Image(Img_out, "out");
    cout<<"All is well"<<endl;

   // imwrite("Out.jpg", Img_out);

    waitKey();
}


