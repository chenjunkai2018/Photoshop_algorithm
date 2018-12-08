/*

perlin noise.

*/

#include "PS_Algorithm.h"
#include <time.h>

using namespace std;
using namespace cv;

void Generate_smoothnoise(Mat& src, Mat& std, int octave);
float Cosine_Interpolate(float x1, float x2, float alpha);
float Linear_Interpolate(float x1, float x2, float alpha);

#define pi 3.1415926

int main()
{
    string Img_name("4.jpg");
    Mat Img;
    Img=imread(Img_name);

    Mat Cloud(Img.size(), CV_32FC1);
    Mat Cloud_Temp(Img.size(), CV_32FC1);
    Mat Base_Noise(Img.size(), CV_32FC1);

    cv::randn(Base_Noise, 0.0, 1.0);
    Show_Image(Base_Noise, "N1");

    float persistance = 0.75;
    float totalAmplitude = 0.0;
    float amplitude;
    int octaveCount=5;

    for (int i=4; i<octaveCount; i++)
    {
        amplitude=std::pow(persistance,(octaveCount-i));
        totalAmplitude=totalAmplitude+amplitude;
        Generate_smoothnoise(Base_Noise, Cloud_Temp, i);
        Cloud=Cloud+Cloud_Temp*amplitude;
    }

    Cloud=Cloud/totalAmplitude;

    Show_Image(Cloud, "out.jpg");
    imwrite("Out.jpg", Cloud*255);

    waitKey();

}

void Generate_smoothnoise(Mat& src, Mat& dst, int octave)
{
    src.copyTo(dst);

    int width=src.cols;
    int height=src.rows;
    float samplePeriod=pow(2,octave);
    float sampleFrequency=1/samplePeriod;

    int sample_i0, sample_i1;
    float vertical_blend, horizontal_blend;
    int sample_j0, sample_j1;
    float top, bottom;


    for (int i=0; i<height-1; i++)
    {
        sample_i0=(int)(i/samplePeriod)*samplePeriod;
        sample_i1=(int)(sample_i0+samplePeriod)%height;
        vertical_blend = (i - sample_i0) * sampleFrequency;
        for (int j=0; j<width-1; j++)
        {
            sample_j0 = (int)(j / samplePeriod) * samplePeriod;
            sample_j1 = (int)(sample_j0 + samplePeriod) % width;
            horizontal_blend = (j - sample_j0) * sampleFrequency;

//            if (sample_i0<0)  sample_i0=0;
//            if (sample_j0<0)  sample_j0=0;
//            if (sample_i1<0)  sample_i1=0;
//            if (sample_j1<0)  sample_j1=0;

            // blend the top two corners
            top = Linear_Interpolate(src.at<float>(sample_i0,sample_j0),
                    src.at<float>(sample_i0,sample_j1), horizontal_blend);

            // blend the bottom two corners
            bottom = Linear_Interpolate(src.at<float>(sample_i1,sample_j0),
                    src.at<float>(sample_i1,sample_j1), horizontal_blend);

            // dst.at<float>(i,j) = sample_j1/255.0 ;

            // final blend
            dst.at<float>(i,j) = Linear_Interpolate(top, bottom, vertical_blend);

        }

    }

}


float Cosine_Interpolate(float x1,float x2,float alpha)
{
    float ft, f;
    float y;

    ft = alpha * pi;
    f = (1 - cos(ft)) * .5;
    y=x1*(1-f)+x2*f;

    return y;
}

float Linear_Interpolate(float x1, float x2, float alpha)
{
    return (1-alpha)*x1 + alpha*x2;
}

