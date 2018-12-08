/*
This program will generate
 "Paint" effect.

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


    Mat r(Image_in.size(), CV_32FC1);
    Mat g(Image_in.size(), CV_32FC1);
    Mat b(Image_in.size(), CV_32FC1);

    Mat rgb[]={b,g,r};

    split(Image_out, rgb);

    int P_size=3;
    Mat sub_mat;

    double min_val;

    for (int i=P_size; i<Image_in.rows-P_size-1; i++)
    {
        for (int j=P_size; j<Image_in.cols-1-P_size; j++)
        {
            for(int k=0; k<3; k++)
            {
                sub_mat=rgb[k].operator()(Range(i-P_size,i+P_size), Range(j-P_size,j+P_size));
                cv::minMaxLoc(sub_mat, &min_val);
                Image_out.at<Vec3f>(i,j)[k]=min_val;
            }
            /*
            sub_mat=b.operator()(Range(i-P_size,i+P_size), Range(j-P_size,j+P_size));
            cv::minMaxLoc(sub_mat, min_val);
            Image_out.at<Vec3f>(i,j)[0]=*min_val;

            sub_mat=g.operator()(Range(i-P_size,i+P_size), Range(j-P_size,j+P_size));
            cv::minMaxLoc(sub_mat, min_val);
            Image_out.at<Vec3f>(i,j)[1]=*min_val;

            sub_mat=r.operator()(Range(i-P_size,i+P_size), Range(j-P_size,j+P_size));
            cv::minMaxLoc(sub_mat, min_val);
            Image_out.at<Vec3f>(i,j)[2]=*min_val;
            */

        }
    }

    Image_out=Image_out/255.0;

    Show_Image(Image_out, "out");

    imwrite("out.jpg", Image_out*255);

    waitKey();
    cout<<"All is well."<<endl;

}
