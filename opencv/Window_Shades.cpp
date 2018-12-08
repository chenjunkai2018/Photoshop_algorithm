/*
This program will generate
 "window shades" effect.

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
    // Show_Image(Image_in, Img_name);

    Mat Image_out(Image_in.size(), CV_32FC3);
    Image_in.convertTo(Image_out, CV_32FC3);

    Mat Map(Image_in.size(), CV_32FC3);

    float val;
    Mat temp;

    for (int i=0; i<Map.rows; i++)
    {
        val=i/255.0;
        temp=Map.row(i);
        temp.setTo(Scalar(val,val,val));
    }

    int H_shade=8;
    int Inter=5;

    int Num;

    Num=Map.rows/(H_shade+Inter);

    //cout<<Num;

    Mat Mask(Image_in.size(), CV_32FC3);
    Mask.setTo(Scalar(1.0,1.0,1.0));

    int row_begin=0;

    for (int i=0; i<=Num; i++)
    {
        if(i<Num)
        {
            row_begin=i*(H_shade+Inter);
            temp=Mask.rowRange(row_begin, row_begin+H_shade-1);
            temp.setTo(Scalar(0.0,0.0,0.0));
        }
        else
        {
            row_begin=i*(H_shade+Inter);
            temp=Mask.rowRange(row_begin, Image_in.rows-1);
            temp.setTo(Scalar(0.0,0.0,0.0));
        }
    }

    Mat M1, M2;
    Image_out=Image_out/255.0;
    cv::multiply(Image_out, -Mask+1, M1);
    cv::multiply(Map, Mask, M2);

    Image_out=M1+M2;

    Image_out=Image_out;

    Show_Image(Image_out, "out");

    imwrite("out.jpg", Image_out*255);

    waitKey();
    cout<<"All is well."<<endl;

}
