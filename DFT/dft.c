/*
離散フーリエ変換関数群
2023/01/21 更新
*/

#include "dft.h"

/*
離散フーリエ変換
  戻り値:
    フーリエ変換後データ
  パラメータ:
    *signal: 変換前データ
    datasize: データ数
*/
double *dft(double *signal, int datasize)
{
    int i, j;
    double *result;
    double complex *cresult, csignal, angle;

    /* フーリエ変換後データ用配列 */
    cresult = (double _Complex *)malloc(sizeof(double _Complex) * datasize);
    result = (double *)malloc(sizeof(double) * datasize);

    for (i = 0; i < datasize; i++)
    {
        cresult[i] = 0.0 + 0.0 * _Complex_I;
        for (j = 0; j < datasize; j++)
        {
            csignal = signal[j] + 0.0 * _Complex_I;
            angle = -DFT_PI2 * (double)i * (double)j / (double)datasize * _Complex_I;
            cresult[i] += csignal * cexp(angle);
        }
        result[i] = cabs(cresult[i]);
    }

    return result;
}

/*
高速フーリエ変換（再帰用)
  パラメータ:
    *signal: 変換前データ -> 変換後データ
    datasize: データ数
*/
void fft_re(double complex *signal, int datasize)
{
    int i, halfsize;
    double complex *odd, *even, angle;

    /* データ数が1以外の時 */
    if (datasize != 1)
    {
        /* 分割後のデータ用配列 */
        halfsize = datasize / 2;
        odd = (double complex *)malloc(sizeof(double complex) * halfsize);
        even = (double complex *)malloc(sizeof(double complex) * halfsize);

        /* データの分割 */
        for (i = 0; i < halfsize; i++)
        {
            even[i] = signal[i * 2];
            odd[i] = signal[i * 2 + 1];
        }

        /* FFT再帰 */
        fft_re(even, halfsize);
        fft_re(odd, halfsize);

        /* 分割データの結合 */
        for (i = 0; i < datasize; i++)
        {
            angle = 0.0 + -DFT_PI2 * (double)i / (double)datasize * _Complex_I;
            signal[i] = even[i % halfsize] + odd[i % halfsize] * cexp(angle);
        }

        /* 分割後データのメモリの開放 */
        free(even);
        free(odd);
    }
}

/*
高速フーリエ変換
  戻り値:
    フーリエ変換後データ
  パラメータ:
    *signal: 変換前データ
    datasize: データ数
*/
double *fft(double *signal, int datasize)
{
    int i, datasize2;
    double *result;
    double complex *csignal;

    /* データ数を2のn乗個に合わせる */
    datasize2 = 1;
    while (datasize2 < datasize)
    {
        datasize2 *= 2;
    }

    /* データ用配列 */
    csignal = (double complex *)malloc(sizeof(double complex) * datasize2);
    for (i = 0; i < datasize; i++)
    {
        csignal[i] = signal[i] + 0.0 * _Complex_I;
    }
    for (/* i = datasize */; i < datasize2; i++)
    {
        csignal[i] = 0.0 + 0.0 * _Complex_I;
    }

    /* 高速フーリエ変換 */
    fft_re(csignal, datasize2);

    /* 変換後のデータを実数に変換 */
    result = (double *)malloc(sizeof(double) * datasize);
    for (i = 0; i < datasize; i++)
    {
        result[i] = cabs(csignal[i]);
    }

    /* メモリの開放 */
    free(csignal);

    /* 終了 */
    return result;
}

/*
離散フーリエ変換後のデータを出力
  パラメータ:
    *data: 変換後データ
    datasize: データ数
    smprate: サンプリングレート
*/
void dft_print(double *data, int datasize)
{
    int i;

    for (i = 0; i < datasize; i++)
    {
        printf("%f,%f\n", (double)i, data[i]);
    }
}

/*
離散フーリエ変換後のデータ/(N/2) を出力
  パラメータ:
    *data: 変換後データ
    datasize: データ数
    smprate: サンプリングレート
*/
void dft_print2(double *data, int datasize)
{
    int i;

    for (i = 0; i < datasize; i++)
    {
        printf("%f,%f\n", (double)i, data[i] * 2.0 / datasize);
    }
}

/*
高速フーリエ変換後のデータを出力
  パラメータ:
    *data: 変換後データ
    datasize: データ数
    smprate: サンプリングレート
*/
void fft_print(double *data, int datasize, int smprate)
{
    int i, datasize2;

    /* データ数を2のn乗個に合わせる */
    datasize2 = 1;
    while (datasize2 < datasize)
    {
        datasize2 *= 2;
    }

    for (i = 0; i < datasize; i++)
    {
        printf("%f,%f\n", (double)i * smprate / (double)datasize2, data[i]);
    }
}

/*
高速フーリエ変換後のデータ/(N/2) を出力
  パラメータ:
    *data: 変換後データ
    datasize: データ数
    smprate: サンプリングレート
*/
void fft_print2(double *data, int datasize, int smprate)
{
    int i, datasize2;

    /* データ数を2のn乗個に合わせる */
    datasize2 = 1;
    while (datasize2 < datasize)
    {
        datasize2 *= 2;
    }

    for (i = 0; i < datasize; i++)
    {
        printf("%f,%f\n", (double)i * smprate / (double)datasize2, data[i] * 2.0 / datasize);
    }
}