#include <iostream>
#include <string>
#include <windows.h>
#include "Public_Function.h"
#include "cv.h"
#include "highgui.h"
#include "cxmat.hpp"
#include "cxcore.hpp"

using namespace std;
using namespace cv;

int main()
{
    string Img_name("1.jpg");

    Mat Image_in;
    Image_in=imread(Img_name);
    Show_Image(Image_in, Img_name);

    double Height, Width;
    Height=Image_in.rows;
    Width =Image_in.cols;
    cout<<Image_in.rows<<endl;
    cout<<Image_in.cols<<endl;
    cout<<Image_in.depth()<<endl;

    Point2i p1(50,50), p2(200,200);

    rectangle(Image_in, p1, p2,
              (100,0,0),3);

   // Show_Image(Image_in, "Draw");
   //Show_Image(Image_out,"Image_out");
   waitKey();

}
