
#include "PS_Algorithm.h"

void Dark_Channel(Mat& src, Mat& dst, int Block_size);
double Atmosperic_Light(Mat& J_dark, Mat& Img);
void Recove_Img(Mat& src, Mat& dst, Mat& T, float Th, float A);

int main(void)
{

    Mat Img;
    Img=imread("5.jpg");
    Mat D_Img(Img.size(), CV_32FC3);
    Img.convertTo(D_Img, CV_32FC3);
    Mat Dark_Img(D_Img.size(), CV_32FC1);
    imshow("Img", Img);

    int Block_size=3;
    Dark_Channel(D_Img, Dark_Img, Block_size);

    float A=0;
    A=Atmosperic_Light(Dark_Img, D_Img);

    float W=0.9;
    Mat T(D_Img.size(), CV_32FC1);
    T=1-W/A*Dark_Img;
    //imshow("Img", T);

    float Th=0.35;
    Mat Img_out(D_Img.size(), CV_32FC3);
    Recove_Img(D_Img, Img_out, T, Th, A);
    Img_out/=255;
    imshow("Out",Img_out);

    cv::imwrite("out.jpg", Img_out*255);

    waitKey();
    cvDestroyAllWindows();

    cout<<"All is well."<<endl;
}

void Dark_Channel(Mat& src, Mat& dst, int Block_size)
{
    Mat R(src.size(), CV_32FC1);
    Mat G(src.size(), CV_32FC1);
    Mat B(src.size(), CV_32FC1);

    Mat m_array[]={R,G,B};
    cv::split(src, m_array);

    int t=0;
    t=(Block_size-1)/2;

    Mat a1(Block_size, Block_size, CV_32FC1);
    Mat a2(Block_size, Block_size, CV_32FC1);
    Mat a3(Block_size, Block_size, CV_32FC1);

    double min_a1=0;
    double min_a2=0;
    double min_a3=0;

    double min_value=0;

    for(int i=t; i<dst.rows-t; i++)
    {
        for(int j=t; j<dst.cols-t; j++)
        {
            a1=R(Range(i-t,i+t+1), Range(j-t,j+t+1));
            a2=G(Range(i-t,i+t+1), Range(j-t,j+t+1));
            a3=B(Range(i-t,i+t+1), Range(j-t,j+t+1));

            cv::minMaxLoc(a1, &min_a1,NULL,NULL,NULL);
            cv::minMaxLoc(a2, &min_a2,NULL,NULL,NULL);
            cv::minMaxLoc(a3, &min_a3,NULL,NULL,NULL);

            min_value=min(min_a1, min_a2);
            min_value=min(min_a3, min_value);

            dst.at<float>(i,j)=(float)min_value;
        }
    }


    dst(Range(0,t), Range::all())=dst(Range(t,2*t), Range::all());
    dst(Range(dst.rows-t,dst.rows), Range::all())=
                        dst(Range(dst.rows-(2*t),dst.rows-t), Range::all());

    dst(Range::all(), Range(0,t))=dst(Range::all(),Range(t,2*t));
    dst(Range::all(),Range(dst.cols-t,dst.cols))=
                        dst(Range::all(), Range(dst.cols-2*t,dst.cols-t));


}

double Atmosperic_Light(Mat& J_dark, Mat& Img)
{

    Mat M1(J_dark.size(), CV_32FC1);
    M1=J_dark;
    M1.reshape(0,1);
    Mat M2(1,J_dark.rows*J_dark.cols, CV_32FC1);
    cv::sort(M1,M2,CV_SORT_ASCENDING);

    int Index=J_dark.rows*J_dark.cols*0.9999;
    float T_value=M2.at<float>(0, Index);

    float value=0;
    float Temp_value;
    float r_temp, g_temp, b_temp;

    for(int i=0; i<Img.rows; i++)
    {
        for(int j=0; j<Img.cols; j++)
        {
            Temp_value=J_dark.at<float>(i,j);
            if(Temp_value>T_value)
            {
                r_temp=Img.at<Vec3f>(i,j)[0];
                g_temp=Img.at<Vec3f>(i,j)[1];
                b_temp=Img.at<Vec3f>(i,j)[2];

                Temp_value=(r_temp+g_temp+b_temp)/3.0;

                value=max(value, Temp_value);

            }

        }
    }

    return value;
}

void Recove_Img(Mat& src, Mat& dst, Mat& T, float Th, float A)
{

    float value=0;

    for(int i=0; i<src.rows; i++)
    {
        for(int j=0; j<src.cols; j++)
        {
            value=max(Th, T.at<float>(i,j));
            dst.at<Vec3f>(i,j)[0]=(src.at<Vec3f>(i,j)[0]-A)/value+A;
            dst.at<Vec3f>(i,j)[1]=(src.at<Vec3f>(i,j)[1]-A)/value+A;
            dst.at<Vec3f>(i,j)[2]=(src.at<Vec3f>(i,j)[2]-A)/value+A;
        }
    }

}

