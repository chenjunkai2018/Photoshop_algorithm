/*
This program will generate
 "Fragment" effect.

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

    Mat Image_2(Image_in.size(), CV_32FC3);
    Image_in.convertTo(Image_2, CV_32FC3);

    Mat Img_up(Image_in.rows, Image_in.cols, CV_32FC3);
    Mat Img_down(Image_in.rows, Image_in.cols, CV_32FC3);
    Mat Img_left(Image_in.rows, Image_in.cols, CV_32FC3);
    Mat Img_right(Image_in.rows, Image_in.cols, CV_32FC3);

    Image_2.copyTo(Img_up);
    Image_2.copyTo(Img_down);
    Image_2.copyTo(Img_left);
    Image_2.copyTo(Img_right);

    Mat temp1, temp2;

    int offset=5;

    int Rows=Image_in.rows;
    int Cols=Image_in.cols;

    // move downward
    temp1=Image_2.rowRange(0, Rows-1-offset);
    temp2=Img_up.rowRange(offset, Rows-1);
    temp1.copyTo(temp2);

    // move upward
    temp1=Image_2.rowRange(offset, Rows-1);
    temp2=Img_down.rowRange(0, Rows-1-offset);
    temp1.copyTo(temp2);

    // move left
    temp1=Image_2.colRange(offset, Cols-1);
    temp2=Img_left.colRange(0, Cols-1-offset);
    temp1.copyTo(temp2);

    // move right
    temp1=Image_2.colRange(0, Cols-1-offset);
    temp2=Img_right.colRange(offset, Cols-1);
    temp1.copyTo(temp2);

    Image_out=1/4.0*(Img_up+Img_down+Img_left+Img_right);

    Image_out=1/255.0*Image_out;

    Show_Image(Image_out, "out.jpg");

    imwrite("out.jpg", Image_out*255);

    waitKey();
    cout<<"All is well."<<endl;

}
