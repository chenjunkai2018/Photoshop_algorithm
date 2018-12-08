/*
The program will access the pixel
of the image.
The image could be the gray or color image.
*/

#include "PS_Algorithm.h"
#include <time.h>

int main()
{
    string  Image_name("2.jpg");
    Mat Image=imread(Image_name.c_str());
    Mat Image_test(Image.size(),CV_32FC3);
    Image.convertTo(Image_test, CV_32FC3);

    srand((unsigned)time(NULL));
    float Table[255];
    for (int i=0; i<255; i++)
    {
        Table[i]=rand()%100/100.0;
    //    cout<<Table[i]<<endl;
    }

    /*
    //-----------------------------------------------------------------------
    // access the pixel by using the
    // pointer
    int nchannels=Image_test.channels();
    int nrows=Image_test.rows;
    int ncols=Image_test.cols*nchannels;

    if(Image_test.isContinuous())
    {
        // if the matrix elements are stored continuously
        // without gaps in the end of each row.
        // we could transform the matrix into a single one-dimention array.
        ncols=ncols*nrows;
        nrows=1;
    }
    float* p_pixel;
    for(int i=0; i<nrows; i++)
    {
        p_pixel=Image_test.ptr<float>(i);
        for(int j=0; j<ncols; j++)
        {
            p_pixel[j]=Table[(int)p_pixel[j]];
        }
    }
    //------------------------------------------------------------------------
    */

    /*
    //------------------------------------------------------------------------
    // access the pixel by using the iterator
    MatIterator_<Vec3f> pixel_begin, pixel_end;
    pixel_begin=Image_test.begin<Vec3f>();
    pixel_end =Image_test.end<Vec3f>();
    for(; pixel_begin!=pixel_end; pixel_begin++)
    {
        (*pixel_begin)[0]=Table[(int)(*pixel_begin)[0]];
        (*pixel_begin)[1]=Table[(int)(*pixel_begin)[1]];
        (*pixel_begin)[2]=Table[(int)(*pixel_begin)[2]];
    }
    //------------------------------------------------------------------------
    */

    //------------------------------------------------------------------------
    // access the pixel by using the random access
    // Mat::at
    int nrows=Image_test.rows;
    int ncols=Image_test.cols;
    int temp=0;
    for (int i=0; i<nrows; i++)
        for(int j=0; j<ncols; j++)
            for(int k=0; k<3; k++)
        {
            temp=Image_test.at<Vec3f>(i,j)[k];
            Image_test.at<Vec3f>(i,j)[k]=Table[temp];
        }

    //------------------------------------------------------------------------

    Show_Image(Image, Image_name);
    Show_Image(Image_test, "Image_test");
    waitKey();


}
