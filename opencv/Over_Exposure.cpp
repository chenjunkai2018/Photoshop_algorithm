/*
This program will generate
 "over exposure " effect.

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


    int nrows=Image_in.rows;
    int ncols=Image_in.cols;

    cout<<"Rows: "<<nrows<<endl;
    cout<<"Cols: "<<ncols<<endl;

    Image_out=-1*Image_in+255;

    cv::min(Image_in, Image_out, Image_out);

    Show_Image(Image_out, "out.jpg");

    imwrite( "Out.jpg",Image_out);


    waitKey();
    cout<<"All is well."<<endl;

}
