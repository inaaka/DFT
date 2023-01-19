/*
高速フーリエ変換用関数群
*/

#include "fft.h"

/*
複素数の加算
return = cmplx1 + cmplx2
*/
fftComplex cmplx_add(fftComplex cmplx1, fftComplex cmplx2)
{
    fftComplex cmplx;
    cmplx.real = cmplx1.real + cmplx2.real;
    cmplx.imag = cmplx1.imag + cmplx2.imag;

    return cmplx;
}

/*
複素数の乗算
return = cmplx1 * cmplx2
*/
fftComplex cmplx_mul(fftComplex cmplx1, fftComplex cmplx2)
{
    fftComplex cmplx;
    cmplx.real = (cmplx1.real * cmplx2.real) - (cmplx1.imag * cmplx2.imag);
    cmplx.imag = (cmplx1.real * cmplx2.imag) + (cmplx1.imag * cmplx2.real);

    return cmplx;
}

/*
複素数の大きさ
return = |cmplx|
*/
double cmplx_abs(fftComplex cmplx)
{
    return sqrt(cmplx.real * cmplx.real + cmplx.imag * cmplx.imag);
}

/*
回転因子の計算
return = exp(j*angle)
*/
fftComplex fft_rotation(double angle)
{
    fftComplex cmplx;
    cmplx.real = cos(angle);
    cmplx.imag = sin(angle);

    return cmplx;
}

/*
データ数を2のn乗数にする
*/
double *two_pwr(double *data, int *data_size)
{
    int i, p;
    double *data2;

    /* データサイズが2の何乗か調べる */
    for (i = 0, p = 1; p < *data_size; i++, p *= 2)
    {
    }

    if (p != *data_size)
    {
        data2 = (double *)malloc(sizeof(double) * p);
        for (i = 0; i < *data_size; i++)
        {
            data2[i] = data[i];
        }
        for (; i < p; i++)
        {
            data2[i] = 0.0;
        }

        *data_size = p;

        return data2;
    }

    return data;
}

/*
高速フーリエ変換
*/
void fft(fftComplex *data, int data_size)
{
    int i, t, half_size;
    double angle;
    fftComplex *odd, *even;

    /* データ数が1以外の時 */
    if (data_size != 1)
    {
        /* 分割後のデータ用メモリ領域の確保 */
        half_size = data_size / 2;
        odd = (fftComplex *)malloc(sizeof(fftComplex) * half_size);
        if (odd == NULL)
        {
            fprintf(stderr, "Failed to dynamic allocate memory.\n");
            exit(1);
        }
        even = (fftComplex *)malloc(sizeof(fftComplex) * half_size);
        if (even == NULL)
        {
            fprintf(stderr, "Failed to dynamic allocate memory.\n");
            free(odd);
            exit(1);
        }

        /* データの分割 */
        for (i = 0; i < half_size; i++)
        {
            even[i] = data[i * 2];
            odd[i] = data[i * 2 + 1];
        }

        /* FFT再帰 */
        fft(even, half_size);
        fft(odd, half_size);

        /* 分割データの結合 */
        for (i = 0; i < data_size; i++)
        {
            angle = fftPI2 * (double)i / (double)data_size;
            data[i] = cmplx_add(even[i % half_size], cmplx_mul(odd[i % half_size], fft_rotation(angle)));
        }

        /* 分割後データのメモリの開放 */
        free(even);
        free(odd);
    }
}

/*
フーリエ変換結果の表示
*/
void printFFT(fftComplex *data, int data_size, int smp_rate)
{
    int i;
    double re_smp_time;

    re_smp_time = (double)smp_rate / (double)data_size;

    printf("Hz\tFFT\n");
    for (i = 0; i < data_size; i++)
    {
        printf("%f\t%f\n", (double)i * re_smp_time, cmplx_abs(data[i]) * 2.0 / data_size);
    }
}