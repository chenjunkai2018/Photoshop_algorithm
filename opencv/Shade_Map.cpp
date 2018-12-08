/*
This program will generate
 "Shade" effect.

*/

#include "PS_Algorithm.h"
#include <time.h>

using namespace std;
using namespace cv;

int main(void)
{
    string Img_name("4.jpg");
    Mat Image_in;
    Image_in=imread(Img_name);
    Show_Image(Image_in, Img_name);

    Mat Image_out(Image_in.size(), CV_32FC3);
    Image_in.convertTo(Image_out, CV_32FC3);

    Mat Map(50, 255, CV_32FC3);

    float val;

    Mat temp;

    // build the mapping talbe
    for (int i=0; i<Map.cols; i++)
    {
        val=i/255.0;
        temp=Map.col(i);
        temp.setTo(Scalar(3*val,3*val-1,3*val-2));
    }

    Show_Image(Map, "Map");

    MatIterator_<Vec3f> pixel_begin, pixel_end;
    pixel_begin=Image_out.begin<Vec3f>();
    pixel_end =Image_out.end<Vec3f>();

    // I=0.299*R+0.587*G+0.144*B

    for( ; pixel_begin!=pixel_end; pixel_begin++)
    {
        val=(*pixel_begin)[0]*0.144;
        val=val+(*pixel_begin)[1]*0.587;
        val=val+(*pixel_begin)[2]*0.299;
        val=val/255.0;
        (*pixel_begin)[0]=3*val;
        (*pixel_begin)[1]=3*val-1;
        (*pixel_begin)[2]=3*val-2;
    }

    Show_Image(Image_out, "out");

    imwrite("out.jpg", Image_out*255);

    waitKey();
    cout<<"All is well."<<endl;

}
