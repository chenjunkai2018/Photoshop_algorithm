#include "Public_Function.h"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

void Save_Image(Mat& Image, const string& str)
{

    imwrite(str.c_str(), Image);
    // waitKey();
    // cvDestroyWindow(str.c_str());
}
