/*
The program will mix the color channels.
*/

#include "PS_Algorithm.h"

int main()
{
    string  Image_name("4.jpg");
    Mat Image=imread(Image_name.c_str());
    Mat Image_test(Image.size(),CV_32FC3);
    Image.convertTo(Image_test, CV_32FC3);

    Mat New_img(Image_test.size(), CV_32FC3);
    Mat r, g, b;
    Mat bgr[]={b,g,r};

    split(Image_test, bgr);

    b=bgr[0];
    g=bgr[1];
    r=bgr[2];

    float blueGreen, redBlue, greenRed;
    blueGreen=0.5;
    redBlue=0.5;
    greenRed=0.5;

    float intoR, intoG, intoB;
    intoR=0.75;
    intoG=0.25,
    intoB=0.75;

    Mat N_R(r.size(), CV_32FC1);
    Mat N_G(r.size(), CV_32FC1);
    Mat N_B(r.size(), CV_32FC1);

    Mat new_bgr[]={N_B, N_G, N_R};

    N_R=(intoR * (blueGreen*g+(1-blueGreen)*b) + (1-intoR)*r);
    N_G=(intoG * (redBlue*b+(1-redBlue)*r) + (1-intoG)*g);
    N_B=(intoB * (greenRed*r+(1-greenRed)*g) + (1-intoB)*b);

    merge(new_bgr, 3, New_img);

    New_img=New_img/255.0;

    Show_Image(New_img, "New_img");

    cout<<"All is well."<<endl;
    waitKey();
}
