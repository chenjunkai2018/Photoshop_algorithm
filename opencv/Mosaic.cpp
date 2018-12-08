/*
This program will generate
 "Mosaic" effect.

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

    int P_size=9;
    float k1, k2;

    int n_row;
    int n_col;

    float m, n;

    int h,w;

    n_row=Image_in.rows;
    n_col=Image_in.cols;

    Mat sub_mat;

    srand( (unsigned)time(NULL) );

    for (int i=P_size; i<Image_in.rows-P_size-1; i=i+P_size)
    {
        for (int j=P_size; j<Image_in.cols-1-P_size; j=j+P_size)
        {
            k1=(double)((rand() % 100))/100.0-0.5;
            k2=(double)((rand() % 100))/100.0-0.5;

            m=(k1*(P_size*2-1));
            n=(k2*(P_size*2-1));

            h=(int)(i+m)% n_row;
            w=(int)(j+n)% n_col;

            sub_mat=Image_out.operator()(Range(i-P_size,i+P_size), Range(j-P_size,j+P_size));

            sub_mat.setTo(Scalar(Image_in.at<Vec3b>(h,w)));

        }
    }

    Image_out=Image_out/255.0;

    Show_Image(Image_out, "out");

    imwrite("out.jpg", Image_out*255);

    waitKey();
    cout<<"All is well."<<endl;

}
