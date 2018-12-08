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
    string Img_name("9.jpg");
    Mat Image_in;
    Image_in=imread(Img_name);
    Show_Image(Image_in, Img_name);

    Mat Image_out(Image_in.size(), CV_32FC3);
    Image_in.convertTo(Image_out, CV_32FC3);

    Mat Image_2(Image_in.size(), CV_32FC3);
    Image_in.convertTo(Image_2, CV_32FC3);

    Mat Map(Image_in.size(), CV_32FC3);
    Mat temp;
    float val;

    // build the mapping table
    /*
    for (int i=0; i<Image_2.rows; i++)
    {
        temp=Map.row(i);
        val=(float)(i)/(float)Image_2.rows;
        temp.setTo(Scalar(val,val,val));
    }
    */

    // build the mapping talbe
    for (int i=0; i<Image_2.rows; i++)
    {
        temp=Map.row(i);
        val=1-std::abs((float)(i)/((float)Image_2.rows/2)-1);
        temp.setTo(Scalar(val,val,val));
    }

    Show_Image(Map, "Map");

    cv::multiply(Image_2, Map, Image_out);

    Image_out=Image_out/255.0;

    Show_Image(Image_out, "out");

    imwrite("out.jpg", Image_out*255);

    waitKey();
    cout<<"All is well."<<endl;

}
