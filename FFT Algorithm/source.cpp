#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <random>
#include <cassert>
using std::vector;
using std::complex;
using std::cout;
using std::endl;
typedef complex<double> Complex;
typedef vector<double> DArray;
typedef vector<Complex> ComArray;
typedef vector<ComArray> ComImg, ComArrayTwoDim;
const double PI = 3.1415926535898;
long long int count0 = 0;

inline void swap(Complex& a, Complex& b);
void transpose(ComArrayTwoDim& array_two_dim);
void picture_FFT(ComImg& fft_out, const ComImg& picture);
ComArray FFT(const ComArray& a);
void testFFT();
void initialArrayTwoDim(ComArrayTwoDim& array_two_dim, const int N, bool initialValue);
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
void print(const ComArrayTwoDim& array_two_dim)
{
	const int N = array_two_dim.size();
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << array_two_dim[i][j] << "   \t";
		cout << endl;
	}
}
inline void swap(Complex& a, Complex& b)
{
	Complex temp = b;
	b = a;
	a = temp;
}

//resize array with two dimension
void initialArrayTwoDim(ComArrayTwoDim& array_two_dim, const int N, bool initialValue = false)
{
	array_two_dim.resize(N);
	for (int i = 0; i < N; i++)
	{
		array_two_dim[i].resize(N);
		if (true == initialValue)
			for (int j = 0; j < N; j++)
				array_two_dim[i][j] = rand()%10;
	}
}

//only for n is a power of 2
void transpose(ComArrayTwoDim& array_two_dim)
{
	assert(array_two_dim.size() == array_two_dim[0].size());
	const int n = array_two_dim.size();
	for (int i = 0; i < n; i++, count0++)
		for (int j = i + 1; j < n; j++, count0++)
			swap(array_two_dim[i][j], array_two_dim[j][i]);
}
void picture_FFT(ComImg& fft_out, const ComImg& picture)
{
	assert(picture.size() == picture[0].size());
	const int n = picture.size();
	for (int i = 0; i < n; i++, count0++)//row fft
	{
		fft_out[i] = FFT(picture[i]);
	}
	transpose(fft_out);
	static ComArray temp(n);
	for (int i = 0; i < n; i++, count0++)//row fft
	{
		fft_out[i] = FFT(fft_out[i]);
	}
	transpose(fft_out);
}
ComArray FFT(const ComArray& a)
{
	int n = a.size();
	if (1 == n)		//base case
		return a;
	assert(n % 2 == 0);
	Complex Wn(cos(2 * PI / n), -sin(2 * PI / n));
	Complex W0(1, 0);
	ComArray a0(n / 2), a1(n / 2);
	for (int i = 0; i < n / 2; i++, count0++)
		a0[i] = a[2 * i];
	for (int i = 0; i < n / 2; i++, count0++)
		a1[i] = a[2 * i + 1];
		
	ComArray y0 = FFT(a0);
	ComArray y1 = FFT(a1);
	ComArray y(n);
	for (int k = 0; k < n / 2; k++, count0++)
	{
		y[k] = y0[k] + W0*y1[k];
		y[k + n / 2] = y0[k] - W0*y1[k];
		W0 *= Wn;
	}
	return y;
}
void testFFT()
{
	const int N = 4;
	ComImg testData;
	initialArrayTwoDim(testData, N, true);
	print(testData);
	cout << endl;
	swapMatrix(testData);
	print(testData);
	//print(testData);
	//ComImg FFTData;
	//initialArrayTwoDim(FFTData, N, false);
	//picture_FFT(FFTData, testData);
	//cout << "total running times is " << count0 << endl;	
	//cout << endl;
	//getchar(); getchar();
	//print(FFTData);
}
int main()
{
	testFFT();
	return 0;
}