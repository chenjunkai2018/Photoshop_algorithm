#include "PS_Algorithm.h"

void Transparent(Mat& src1, Mat& src2, Mat& dst, double alpha);
void Multiply(Mat& src1, Mat& src2, Mat& dst);
void Color_Burn(Mat& src1, Mat& src2, Mat& dst);
void Color_Dodge(Mat& src1, Mat& src2, Mat& dst);

void Linear_Burn(Mat& src1, Mat& src2, Mat& dst);
void Linear_Dodge(Mat& src1, Mat& src2, Mat& dst);
void Lighten(Mat& src1, Mat& src2, Mat& dst);
void Darken(Mat& src1, Mat& src2, Mat& dst);

void Screen(Mat& src1, Mat& src2, Mat& dst);
void Add_Color(Mat& src1, Mat& src2, Mat& dst);
void Soft_Lighten(Mat& src1, Mat& src2, Mat& dst);
void Strong_Lighten(Mat& src1, Mat& src2, Mat& dst);

void Vivid_Lighten(Mat& src1, Mat& src2, Mat& dst);
void Pin_Lighten(Mat& src1, Mat& src2, Mat& dst);
void Linear_Lighten(Mat& src1, Mat& src2, Mat& dst);
void Hard_mix(Mat& src1, Mat& src2, Mat& dst);

void Difference(Mat& src1, Mat& src2, Mat& dst);
void Exclusion(Mat& src1, Mat& src2, Mat& dst);
void Dissolve(Mat& src1, Mat& src2, Mat& dst, double alpha);
void HSV(Mat& src1, Mat& src2, Mat& dst);

int main(void)
{
    Mat Origin_Image1;
    Mat Origin_Image2;

    Origin_Image1=imread("2.jpg");
    Origin_Image2=imread("3.jpg");

    Mat Image_up(Origin_Image1.size(),CV_32FC3);
    Mat Image_down(Origin_Image2.size(), CV_32FC3);

    Origin_Image1.convertTo(Image_up,CV_32FC3);
    Origin_Image2.convertTo(Image_down,CV_32FC3);

    Image_up=Image_up/255;
    Image_down=Image_down/255;
    Mat Image_mix(Image_up);

    //double alpha=0.25;
    //Transparent(Image_up, Image_down, Image_mix, alpha);
    //Multiply(Image_up, Image_down, Image_mix);
    //Color_Burn(Image_up, Image_down, Image_mix);
    //Color_Dodge(Image_up, Image_down, Image_mix);

    //Linear_Burn(Image_up, Image_down, Image_mix);
    //Linear_Dodge(Image_up, Image_down, Image_mix);
    //Lighten(Image_up, Image_down, Image_mix);
    //Darken(Image_up, Image_down, Image_mix);

    //Screen(Image_up, Image_down, Image_mix);
    //Add_Color(Image_up, Image_down, Image_mix);
    //Soft_Lighten(Image_up, Image_down, Image_mix);
    //Strong_Lighten(Image_up, Image_down, Image_mix);

    //Vivid_Lighten(Image_up, Image_down, Image_mix);
    //Pin_Lighten(Image_up, Image_down, Image_mix);
    //Linear_Lighten(Image_up, Image_down, Image_mix);
    //Hard_mix(Image_up, Image_down, Image_mix);

    //Difference(Image_up, Image_down, Image_mix);
    //Exclusion(Image_up, Image_down, Image_mix);
    //Dissolve(Image_up, Image_down, Image_mix, 0.75);
    // HSV(Image_up, Image_down, Image_mix);

    namedWindow("Img", CV_WINDOW_AUTOSIZE);
    imshow("Img",Image_mix);

    waitKey();
    cvDestroyWindow("Img");
    cout<<"All is well."<<endl;

    return 0;
}


// Transparent
void Transparent(Mat& src1, Mat& src2, Mat& dst, double alpha)
{
    dst=alpha*src1+(1-alpha)*src2;
}

// Multiply
void Multiply(Mat& src1, Mat& src2, Mat& dst)
{
    for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
                dst.at<Vec3f>(index_row, index_col)[index_c]=
                         src1.at<Vec3f>(index_row, index_col)[index_c]*
                         src2.at<Vec3f>(index_row, index_col)[index_c];
        }

    }


}

// Color_Burn
void Color_Burn(Mat& src1, Mat& src2, Mat& dst)
{
    for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
                dst.at<Vec3f>(index_row, index_col)[index_c]=1-
                         (1-src1.at<Vec3f>(index_row, index_col)[index_c])/
                         src2.at<Vec3f>(index_row, index_col)[index_c];
        }

    }
}


// Color_Dodge
void Color_Dodge(Mat& src1, Mat& src2, Mat& dst)
{
    for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
                dst.at<Vec3f>(index_row, index_col)[index_c]=
                          src2.at<Vec3f>(index_row, index_col)[index_c]/
                         (1-src1.at<Vec3f>(index_row, index_col)[index_c]);
        }

    }

}


// linear burn
void Linear_Burn(Mat& src1, Mat& src2, Mat& dst)
{
    for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
                dst.at<Vec3f>(index_row, index_col)[index_c]=max(
                         src1.at<Vec3f>(index_row, index_col)[index_c]+
                         src2.at<Vec3f>(index_row, index_col)[index_c]-1, (float)0.0);
        }

    }

}

// linear dodge
void Linear_Dodge(Mat& src1, Mat& src2, Mat& dst)
{
    for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
                dst.at<Vec3f>(index_row, index_col)[index_c]=min(
                         src1.at<Vec3f>(index_row, index_col)[index_c]+
                         src2.at<Vec3f>(index_row, index_col)[index_c], (float)1.0);
        }

    }


}


// Lighten
void Lighten(Mat& src1, Mat& src2, Mat& dst)
{
    for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
                dst.at<Vec3f>(index_row, index_col)[index_c]=max(
                         src1.at<Vec3f>(index_row, index_col)[index_c],
                         src2.at<Vec3f>(index_row, index_col)[index_c]);
        }

    }

}


// Darken
void Darken(Mat& src1, Mat& src2, Mat& dst)
{
     for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
                dst.at<Vec3f>(index_row, index_col)[index_c]=min(
                         src1.at<Vec3f>(index_row, index_col)[index_c],
                         src2.at<Vec3f>(index_row, index_col)[index_c]);
        }

    }

}

// Screen
void Screen(Mat& src1, Mat& src2, Mat& dst)
{
     for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
                dst.at<Vec3f>(index_row, index_col)[index_c]=1-
                         (1-src1.at<Vec3f>(index_row, index_col)[index_c])*
                         (1-src2.at<Vec3f>(index_row, index_col)[index_c]);
        }

    }

}


// Add color
void Add_Color(Mat& src1, Mat& src2, Mat& dst)
{
    float a=0;
    float b=0;
     for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
            {
                a=src1.at<Vec3f>(index_row, index_col)[index_c];
                b=src2.at<Vec3f>(index_row, index_col)[index_c];
                if(b>0.5)
                {
                    dst.at<Vec3f>(index_row, index_col)[index_c]=2*a*b;

                }
                else
                {
                    dst.at<Vec3f>(index_row, index_col)[index_c]=1-2*(1-a)*(1-b);
                }
            }
        }
    }
}

// Soft Lighten
void Soft_Lighten(Mat& src1, Mat& src2, Mat& dst)
{
    float a=0;
    float b=0;
     for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
            {
                a=src1.at<Vec3f>(index_row, index_col)[index_c];
                b=src2.at<Vec3f>(index_row, index_col)[index_c];
                if(a<=0.5)
                {
                    dst.at<Vec3f>(index_row, index_col)[index_c]=(2*a-1)*(b-b*b)+b;

                }
                else
                {
                    dst.at<Vec3f>(index_row, index_col)[index_c]=(2*a-1)*(sqrt(b)-b)+b;
                }
            }
        }
    }

}


// Strong Lighten
void Strong_Lighten(Mat& src1, Mat& src2, Mat& dst)
{
    float a=0;
    float b=0;
     for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
            {
                a=src1.at<Vec3f>(index_row, index_col)[index_c];
                b=src2.at<Vec3f>(index_row, index_col)[index_c];
                if(a<=0.5)
                {
                    dst.at<Vec3f>(index_row, index_col)[index_c]=2*a*b;

                }
                else
                {
                    dst.at<Vec3f>(index_row, index_col)[index_c]=1-2*(1-a)*(1-b);
                }
            }
        }
    }

}


//Vivid Lighten
void Vivid_Lighten(Mat& src1, Mat& src2, Mat& dst)
{
    float a=0;
    float b=0;
     for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
            {
                a=src1.at<Vec3f>(index_row, index_col)[index_c];
                b=src2.at<Vec3f>(index_row, index_col)[index_c];
                if(a<=0.5)
                {
                    dst.at<Vec3f>(index_row, index_col)[index_c]=1-(1-b)/(2*a);

                }
                else
                {
                    dst.at<Vec3f>(index_row, index_col)[index_c]=b/(2*(1-a));
                }
            }
        }
    }

}


// Pin lighten
void Pin_Lighten(Mat& src1, Mat& src2, Mat& dst)
{
    float a=0;
    float b=0;
     for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
            {
                a=src1.at<Vec3f>(index_row, index_col)[index_c];
                b=src2.at<Vec3f>(index_row, index_col)[index_c];
                if(b<=2*a-1)
                {
                    dst.at<Vec3f>(index_row, index_col)[index_c]=2*a-1;

                }
                else if(b<=2*a)
                {
                    dst.at<Vec3f>(index_row, index_col)[index_c]=b;
                }
                else
                {
                    dst.at<Vec3f>(index_row, index_col)[index_c]=2*a;
                }
            }
        }
    }
}


// Linear Lighten
void Linear_Lighten(Mat& src1, Mat& src2, Mat& dst)
{
    dst=src2+2*src1-1;

}


// Hard mix
void Hard_mix(Mat& src1, Mat& src2, Mat& dst)
{
    float a=0;
    float b=0;
     for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
            {
                a=src1.at<Vec3f>(index_row, index_col)[index_c];
                b=src2.at<Vec3f>(index_row, index_col)[index_c];
                if(a<1-b)
                {
                    dst.at<Vec3f>(index_row, index_col)[index_c]=0.0;

                }
                else
                {
                    dst.at<Vec3f>(index_row, index_col)[index_c]=1.0;
                }
            }
        }
    }
}


// Difference
void Difference(Mat& src1, Mat& src2, Mat& dst)
{
    float a=0;
    float b=0;
     for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
            {
                a=src1.at<Vec3f>(index_row, index_col)[index_c];
                b=src2.at<Vec3f>(index_row, index_col)[index_c];

                dst.at<Vec3f>(index_row, index_col)[index_c]=abs(a-b);
            }
        }
    }

}


// Exclusion
void Exclusion(Mat& src1, Mat& src2, Mat& dst)
{
    float a=0;
    float b=0;
     for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            for(int index_c=0; index_c<3; index_c++)
            {
                a=src1.at<Vec3f>(index_row, index_col)[index_c];
                b=src2.at<Vec3f>(index_row, index_col)[index_c];

                dst.at<Vec3f>(index_row, index_col)[index_c]=a+b-2*a*b;
            }
        }
    }

}


// Dissolve
void Dissolve(Mat& src1, Mat& src2, Mat& dst, double alpha)
{
    dst=src1;
    Mat Rand_mat(src1.size(), CV_32FC1);
    cv::randu(Rand_mat, 0,1);
    float a=0;
    float b=0;
     for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {

            b=Rand_mat.at<float>(index_row, index_col);
            if(b<alpha)
            {
                for(int index_c=0; index_c<3; index_c++)
               {
                   a=src2.at<Vec3f>(index_row, index_col)[index_c];
                   dst.at<Vec3f>(index_row, index_col)[index_c]=a;
               }

            }
        }
    }

}


// Saturation
void HSV(Mat& src1, Mat& src2, Mat& dst)
{
    Mat M1(src1.size(), CV_32FC3);
    Mat M2(src2.size(), CV_32FC3);

    cvtColor(src1, M1, CV_BGR2HSV);
    cvtColor(src2, M2, CV_BGR2HSV);

     for(int index_row=0; index_row<src1.rows; index_row++)
    {
        for(int index_col=0; index_col<src1.cols; index_col++)
        {
            dst.at<Vec3f>(index_row, index_col)[0]=
                          M2.at<Vec3f>(index_row, index_col)[0];

            dst.at<Vec3f>(index_row, index_col)[1]=
                          M2.at<Vec3f>(index_row, index_col)[1];

            dst.at<Vec3f>(index_row, index_col)[2]=
                          M1.at<Vec3f>(index_row, index_col)[2];
        }
    }

    cvtColor(dst, dst, CV_HSV2BGR);
}



