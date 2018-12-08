
// define the show image
#include "PS_Algorithm.h"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

void Show_Image(Mat& Image, const string& str)
{
    namedWindow(str.c_str(),CV_WINDOW_AUTOSIZE);
    imshow(str.c_str(), Image);

}

