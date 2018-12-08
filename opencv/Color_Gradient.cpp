/*
This program will generate
color gradient mapping

*/


#include "PS_Algorithm.h"
#include <time.h>

using namespace std;
using namespace cv;


int main(void)
{
    Mat Img(600, 800, CV_32FC3);

    Scalar a(255.0, 255.0, 255.0);
    Scalar b(0.0, 0.0, 0.0);

    Img.setTo(a);

    int width, height;
    width=Img.cols;
    height=Img.rows;

    Point2f origin(0.0, 0.0);
    Point2f Cen(Img.cols/2.0, Img.rows/2.0);

    float dis;

    if (origin.x<=Cen.x && origin.y<=Cen.y)
    {
        dis=sqrt((width-1-origin.x)*(width-1-origin.x)+
                        (height-1-origin.y)*(height-1-origin.y));
    }
    else if (origin.x<=Cen.x && origin.y>Cen.y)
    {
        dis=sqrt((width-1-origin.x)*(width-1-origin.x)+
                        origin.y*origin.y);

    }
    else if (origin.x>Cen.x && origin.y>Cen.y)
    {
        dis=sqrt(origin.x*origin.x+(origin.y)*(origin.y));
    }
    else
    {
       dis=sqrt(origin.x*origin.x+
                        (height-1-origin.y)*(height-1-origin.y));
    }

    float weightB=(b[0]-a[0])/dis;
    float weightG=(b[1]-a[1])/dis;
    float weightR=(b[2]-a[2])/dis;

    float dis2;
    for (int i=0; i<Img.rows; i++)
    {
        for (int j=0; j<Img.cols; j++)
        {
            dis2=sqrt((i-origin.x)*(i-origin.x)+(j-origin.y)*(j-origin.y));
            Img.at<Vec3f>(i,j)[0]=Img.at<Vec3f>(i,j)[0]+weightB*dis2;
            Img.at<Vec3f>(i,j)[1]=Img.at<Vec3f>(i,j)[1]+weightG*dis2;
            Img.at<Vec3f>(i,j)[2]=Img.at<Vec3f>(i,j)[2]+weightR*dis2;
        }
    }

    Img=Img/255.0;

    Show_Image(Img, "img");
   imwrite("Out.jpg", Img*255);

    waitKey();
    cout<<"All is well."<<endl;




}
