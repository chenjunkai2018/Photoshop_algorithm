
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

    float theta=pi/6;

    int width=Img.cols;
    int height=Img.rows;

    /*
    // horizontal skewing
    int new_height=height;
    int new_width=width+height*tan(theta)+1;
    Mat Img_H=Mat::zeros(new_height,new_width, CV_8UC3);

    float Dis;
    float new_x, new_y;
    float x1, y1, p;
    for (int y=0; y<new_height; y++)
    {
        Dis=(height-y)*tan(theta);
        for (int x=0; x<new_width; x++)
        {
            new_y=y;
           // right skew
           //  new_x=x-Dis;
           // left skew
             new_x=x+Dis-height*tan(theta);

          // if (new_x<0) new_x=0;
          // if (new_x>width-1) new_x=width-2;

          if (new_x>0 && new_x<width-1)
          {
                x1=int(new_x);
                y1=int(new_y);
                p=new_x-x1;

                Img_H.at<Vec3b>(y,x)[0]=(1-p)*Img.at<Vec3b>(y1,x1)[0]+p*Img.at<Vec3b>(y1,x1+1)[0];
                Img_H.at<Vec3b>(y,x)[1]=(1-p)*Img.at<Vec3b>(y1,x1)[1]+p*Img.at<Vec3b>(y1,x1+1)[1];
                Img_H.at<Vec3b>(y,x)[2]=(1-p)*Img.at<Vec3b>(y1,x1)[2]+p*Img.at<Vec3b>(y1,x1+1)[2];

          }

        }
    }
    Show_Image(Img_H, "out");
    imwrite("H.jpg", Img_H);
    */


    // vertical skewing
    int new_height=height+width*tan(theta)+1;
    int new_width=width;
    Mat Img_V=Mat::zeros(new_height,new_width, CV_8UC3);

    float Dis;
    float new_x, new_y;
    float x1, y1, p;
    for (int y=0; y<new_height; y++)
    {

        for (int x=0; x<new_width; x++)
        {
            Dis=x*tan(theta);
            new_x=x;
           // right skew
           new_y=y-Dis;
           // left skew
           //  new_y=y+Dis-width*tan(theta);

          if (new_y>0 && new_y<height-1)
          {
                x1=int(new_x);
                y1=int(new_y);
                p=new_y-y1;

                Img_V.at<Vec3b>(y,x)[0]=(1-p)*Img.at<Vec3b>(y1,x1)[0]+p*Img.at<Vec3b>(y1+1,x1)[0];
                Img_V.at<Vec3b>(y,x)[1]=(1-p)*Img.at<Vec3b>(y1,x1)[1]+p*Img.at<Vec3b>(y1+1,x1)[1];
                Img_V.at<Vec3b>(y,x)[2]=(1-p)*Img.at<Vec3b>(y1,x1)[2]+p*Img.at<Vec3b>(y1+1,x1)[2];

          }

        }
    }
    Show_Image(Img_V, "out");
    imwrite("V.jpg", Img_V);

    waitKey();

}
