/*
This program will transform
the color image to Black-whithe
image.

*/

#include "PS_Algorithm.h"
#include <time.h>

using namespace std;
using namespace cv;

int main(void)
{
    string Img_name("9.jpg");
    Mat Img_in;
    Img_in=imread(Img_name);
    Show_Image(Img_in, Img_name);

    Mat Img_out(Img_in.size(), CV_32FC3);
    Img_in.convertTo(Img_out, CV_32FC3);

    Mat R(Img_in.size(),CV_32FC1);
    Mat G(Img_in.size(),CV_32FC1);
    Mat B(Img_in.size(),CV_32FC1);

    Mat I(Img_in.size(),CV_32FC1);

    Mat BW_out(Img_in.size(), CV_32FC1);

    Mat rgb[]={B, G, R};
    cv::split(Img_out, rgb);

    I=B+G+R;

    float maxVal, minVal, midVal;

    float color_ratio[6]={0.4,0.6,0.4,0.6,0.2,0.8};
    float r_max_mid, r_max;
    int Ind;

    for(int i=0; i<I.rows; i++)
    {
        for(int j=0; j<I.cols; j++)
        {
            maxVal=std::max(R.at<float>(i,j), std::max(G.at<float>(i,j),
                                                       B.at<float>(i,j)));
            minVal=std::min(R.at<float>(i,j), std::min(G.at<float>(i,j),
                                                       B.at<float>(i,j)));
            midVal=I.at<float>(i,j)-maxVal-minVal;

            if(minVal==R.at<float>(i,j))
            {
                Ind=0;
            }
            else if(minVal==G.at<float>(i,j))
            {
                Ind=2;
            }
            else
            {
                Ind=4;
            }
            r_max_mid=color_ratio[(Ind+3)%6+1];

            if(maxVal==R.at<float>(i,j))
            {
                Ind=1;
            }
            else if(maxVal==G.at<float>(i,j))
            {
                Ind=3;
            }
            else
            {
                Ind=5;
            }

            r_max=color_ratio[Ind];

            BW_out.at<float>(i,j)=(maxVal-midVal)*r_max+(midVal-minVal)
                      *r_max_mid+minVal;

        }
    }

    BW_out=BW_out/255;
    Show_Image(BW_out, "out");

    imwrite("out.jpg", BW_out*255);

    waitKey();
    cout<<"All is well."<<endl;

}
