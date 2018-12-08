/*
The program will Divides multi-channel array
into several single-channel arrays.
We can get the single-channel from a multi-channel
image.
*/

#include "PS_Algorithm.h"

using namespace std;
using namespace cv;

int main()
{
    string Img_name("4.jpg");

    Mat Image_in;
    Image_in=imread(Img_name);
    Show_Image(Image_in, Img_name);

    // convert the type of the image.
    // from the uchar to the float.
    Mat Image_2(Image_in.size(), CV_32FC3);
    Image_in.convertTo( Image_2, CV_32FC3);

    Mat r(Image_in.rows, Image_in.cols, CV_32FC1);
    Mat g(Image_in.rows, Image_in.cols, CV_32FC1);
    Mat b(Image_in.rows, Image_in.cols, CV_32FC1);

    Mat out[]={b, g, r};

    split(Image_2, out);

    b=out[0]/255;
    g=out[1]/255;
    r=out[2]/255;

    Show_Image(g, "Img");
    b=b*255;
    Save_Image(b,"Blue.jpg");

    waitKey();

}
