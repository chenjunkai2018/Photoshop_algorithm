/*
Image offset.
*/

#include "PS_Algorithm.h"

int main()
{
    string  Image_name("4.jpg");
    Mat Img=imread(Image_name.c_str());
    Mat Img_out(Img.size(), CV_8UC3);

    int warp, xOffset, yOffset;
    xOffset=150;
    yOffset=100;
    warp=1;

    int width=Img.cols;
    int height=Img.rows;

    if (warp)
    {
        while(xOffset<0)
        xOffset=xOffset+width;

        while(yOffset<0)
        yOffset=yOffset+height;

        xOffset=xOffset%width;
        yOffset=yOffset%height;
    }

    int new_x, new_y;

     for (int y=0; y<height; y++)
    {
        for (int x=0; x<width; x++)
        {
            if(warp)
            {
                new_x=(x+width-xOffset)%width;
                new_y=(y+height-yOffset)%height;
            }
            else
            {
                new_x=x-xOffset;
	            new_y=y-yOffset;
            }

            if(new_x<0)         new_x=0;
            if(new_x>=width-1)  new_x=width-2;
            if(new_y<0)         new_y=0;
            if(new_y>=height-1) new_y=height-2;


            for (int k=0; k<3; k++)
            {
                Img_out.at<Vec3b>(y, x)[k]=Img.at<Vec3b>(new_y, new_x)[k];

            }

        }

    }


    Show_Image(Img_out, "New_img");

   // cout<<"All is well."<<endl;
   // cout<<xOffset<<endl;
   // cout<<yOffset<<endl;
    waitKey();
}
