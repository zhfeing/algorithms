#include "FFT.h"

inline Vec3b RGB_to_blackAndWhite(const Vec3b& Rgb)
{
    Bit gray = Rgb[0]*0.299+Rgb[1]*0.587+Rgb[2]*0.114;
    Vec3b ans;
    for(int i = 0;i<3;i++)
        ans[i] = gray;
    return ans;
}

void MatCopy(Mat &src, const Mat &img, bool turnToBlack = false)
{
    for(int m = 0; m < src.rows; m++)
    {
        for(int n = 0; n < src.cols; n++)
        {
            for(int i = 0; i < 3; i++)
            {
                if(turnToBlack = false)
                {
                    if(m < img.rows && n < img.cols)
                        src.at<Vec3b>(m,n)[i] = img.at<Vec3b>(m,n)[i];
                    else
                        src.at<Vec3b>(m,n)[i] = 0;
                }
                else
                {
                    if(m < img.rows && n < img.cols)
                        src.at<Vec3b>(m,n) = RGB_to_blackAndWhite(img.at<Vec3b>(m,n));
                    else
                        src.at<Vec3b>(m,n)[i] = 0;
                }
            }
        }
    }
}

//if the size of picture is not the power of two: return false
bool findMaxSubSizeWithPowerOfTwo(const Mat& picture, int& size)
{
    int maxSize = std::max(picture.cols, picture.rows);
    double isPowOfTwo = std::log(double(maxSize))/log(2.0);
    int logSize = int(isPowOfTwo);
    size = int(std::pow(2, logSize));
    if((isPowOfTwo - logSize) > 1e-6)
        return false;
    else
        return true;
}

//for the transpose
inline void swap(MYComplex &a, MYComplex &b)
{
    MYComplex temp = b;
    b = a;
    a = temp;
}

//transpose the matrix
void transpose(ComArrayTwoDim& array_two_dim)
{
    assert(array_two_dim.size() == array_two_dim[0].size());
    const int n = array_two_dim.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            swap(array_two_dim[i][j], array_two_dim[j][i]);
}

//resize array with two dimension
void initialArrayTwoDim(ComArrayTwoDim& array_two_dim, const int N, const Mat* img, bool initialValue = false)
{
    array_two_dim.resize(N);
    for (int i = 0; i < N; i++)
    {
        array_two_dim[i].resize(N);
        if (true == initialValue)
            for (int j = 0; j < N; j++)
                array_two_dim[i][j] = img->at<Vec3b>(i,j)[0];
    }
}

//fft algorithm
ComArray FFT(const ComArray& a)
{
    int n = a.size();
    if (1 == n)		//base case
        return a;
    assert(n % 2 == 0);
    MYComplex Wn(cos(2 * PI / n), -sin(2 * PI / n));
    MYComplex W0(1, 0);
    ComArray a0(n / 2), a1(n / 2);
    for (int i = 0; i < n / 2; i++)
        a0[i] = a[2 * i];
    for (int i = 0; i < n / 2; i++)
        a1[i] = a[2 * i + 1];

    ComArray y0 = FFT(a0);
    ComArray y1 = FFT(a1);
    ComArray y(n);
    for (int k = 0; k < n / 2; k++)
    {
        y[k] = y0[k] + W0*y1[k];
        y[k + n / 2] = y0[k] - W0*y1[k];
        W0 *= Wn;
    }
    return y;
}

//only for n is a power of 2
void Two_Dim_FFT(ComImg& fft_out, const ComImg& picture)
{
    assert(picture.size() == picture[0].size());
    const int n = picture.size();
    for (int i = 0; i < n; i++)//row fft
    {
        fft_out[i] = FFT(picture[i]);
    }
    transpose(fft_out);
//    static ComArray temp(n);
    for (int i = 0; i < n; i++)//row fft
    {
        fft_out[i] = FFT(fft_out[i]);
    }
    transpose(fft_out);
}

void img_FFT(Mat& fft_out, const Mat& img)
{
    double re, im;
    double temp;
    const int N = img.rows;
    ComArrayTwoDim tempPic;
    ComArrayTwoDim tempOut;
    initialArrayTwoDim(tempPic, img.rows, &img, true);
    initialArrayTwoDim(tempOut, img.rows, 0, false);

    Two_Dim_FFT(tempOut, tempPic);

    swapMatrix(tempOut);//move the origin to the middle
    for(int m = 0; m < fft_out.rows; m++)
    {
        for(int n = 0; n < fft_out.cols; n++)
        {
            re = tempOut[m][n].real();
            im = tempOut[m][n].imag();
            //temp = sqrt(re*re + im*im);//to shink the difference
            temp = sqrt(re*re + im*im)/150;//to shink the difference
            if(temp>255)
                temp = 255;
            for(int i = 0; i < 3; i++)
            {
                fft_out.at<Vec3b>(m,n)[i] = temp;
            }
        }
    }
}
void swapMatrix(ComArrayTwoDim& a)
{
    const int N = a.size();
        int m = N / 2;
        int n = N / 2;
        for (int i = 0; i < N / 2; i++, m++)
        {
            for (int j = 0; j < N / 2; j++, n++)
            {
                swap(a[i][j], a[m][n]);
            }
            n = 0;
            for (int j = N / 2; j < N; j++, n++)
            {
                swap(a[i][j], a[m][n]);
            }
        }
}
