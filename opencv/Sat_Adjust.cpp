/*
This program adjust
the saturation.

*/

#include "PS_Algorithm.h"
#include <time.h>

using namespace std;
using namespace cv;

int main(void)
{
    string Img_name("4.jpg");
    Mat Img;
    Img=imread(Img_name);
    Show_Image(Img, Img_name);

    Mat Img_out(Img.size(), CV_32FC3);
    Img.convertTo(Img_out, CV_32FC3);

    Mat Img_in(Img.size(), CV_32FC3);
    Img.convertTo(Img_in, CV_32FC3);



    // define the iterator of the input image
    MatIterator_<Vec3f> inp_begin, inp_end;
    inp_begin=Img_in.begin<Vec3f>();
    inp_end =Img_in.end<Vec3f>();

    // define the iterator of the output image
    MatIterator_<Vec3f> out_begin, out_end;
    out_begin=Img_out.begin<Vec3f>();
    out_end =Img_out.end<Vec3f>();

    // increment (-100.0, 100.0)
    float Increment=-50.0/100.0;

    float delta=0;
    float minVal, maxVal;
    float t1, t2, t3;
    float L,S;
    float alpha;

    for(; inp_begin!=inp_end; inp_begin++, out_begin++)
    {
        t1=(*inp_begin)[0];
        t2=(*inp_begin)[1];
        t3=(*inp_begin)[2];

        minVal=std::min(std::min(t1,t2),t3);
        maxVal=std::max(std::max(t1,t2),t3);

        delta=(maxVal-minVal)/255.0;

        L=0.5*(maxVal+minVal)/255.0;

        S=std::max(0.5*delta/L, 0.5*delta/(1-L));

        if (Increment>0)
        {
            alpha=max(S, 1-Increment);
            alpha=1.0/alpha-1;
            (*out_begin)[0]=(*inp_begin)[0]+((*inp_begin)[0]-L*255.0)*alpha;
            (*out_begin)[1]=(*inp_begin)[1]+((*inp_begin)[1]-L*255.0)*alpha;
            (*out_begin)[2]=(*inp_begin)[2]+((*inp_begin)[2]-L*255.0)*alpha;
        }
        else
        {
            alpha=Increment;
            (*out_begin)[0]=L*255.0+((*inp_begin)[0]-L*255.0)*(1+alpha);
            (*out_begin)[1]=L*255.0+((*inp_begin)[1]-L*255.0)*(1+alpha);
            (*out_begin)[2]=L*255.0+((*inp_begin)[2]-L*255.0)*(1+alpha);

        }
    }

    Img_out=Img_out/255.0;
    Show_Image(Img_out, "out");

    imwrite("out.jpg", Img_out*255);

    waitKey();
    cout<<"All is well."<<endl;

}
