#pragma once
#ifndef FFT_H
#define FFT_H

#include <QtGui/QMainWindow>
#include <QImage>
#include <QPixmap>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <cmath>
#include <cassert>
#include <algorithm>

using std::vector;
using std::complex;
using std::cout;
using std::endl;
using std::string;
using cv::Mat;
using cv::Vec3b;

typedef complex<double> MYComplex;
typedef vector<double> DArray;
typedef vector<MYComplex> ComArray;
typedef vector<ComArray> ComImg, ComArrayTwoDim;
typedef char Bit;

const double PI = 3.1415926535898;
const double MAX_SIZE = 4096;   //the max size that FFT can deal with

extern Mat Img;
extern Mat FFT_output;

void img_FFT(Mat& fft_out, const Mat& img);
inline Vec3b RGB_to_blackAndWhite(const Vec3b& Rgb);
void MatCopy(Mat &src, const Mat &img, bool turnToBlack);
bool findMaxSubSizeWithPowerOfTwo(const Mat& picture, int& size);
inline void swap(MYComplex& a, MYComplex& b);
void transpose(ComArrayTwoDim& array_two_dim);
void Two_Dim_FFT(ComImg& fft_out, const ComImg& picture);
ComArray FFT(const ComArray& a);
void initialArrayTwoDim(ComArrayTwoDim& array_two_dim, const int N, const Mat& img, bool initialValue);
void swapMatrix(ComArrayTwoDim& a);
#endif // FFT_H
