/*
This program will generate
 "diffuse or groundglass " effect.

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
    Mat Image_2(Image_in.size(), CV_32FC3);
    Image_in.convertTo( Image_2, CV_32FC3);

    Mat Image_Blur(Image_in.size(), CV_32FC3);
    GaussianBlur(Image_2, Image_Blur, Size (5, 5), 0);
    Image_Blur=Image_Blur/255;
    Show_Image(Image_Blur, "blur");


    int nrows=Image_Blur.rows;
    int ncols=Image_Blur.cols;

    cout<<"Rows: "<<nrows<<endl;
    cout<<"Cols: "<<ncols<<endl;

    Mat Image_Out(Image_Blur.size(), CV_32FC3);

    int P_size; P_size=3;
    float k1, k2;
    float m, n;
    int h, w;


    srand( (unsigned)time(NULL) );

    for (int i=0+P_size; i<nrows-P_size; i++ )
       for (int j=0+P_size; j<ncols-P_size; j++ )
      {

        k1=(double)((rand() % 100))/100.0-0.5;
        k2=(double)((rand() % 100))/100.0-0.5;

        m=(k1*(P_size*2-1));
        n=(k2*(P_size*2-1));

        h=(int)(i+m)% nrows;
        w=(int)(j+n)% ncols;

        Image_Out.at<Vec3f>(i,j)=Image_Blur.at<Vec3f>(h,w);

      }

    Show_Image(Image_Out, "out.jpg");

    imwrite( "Out.jpg",Image_Out*255);


    waitKey();
    cout<<"All is well."<<endl;

}
