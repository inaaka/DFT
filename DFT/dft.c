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
離散フーリエ変換後のデータを出力
  パラメータ:
    *data: 変換後データ
    datasize: データ数
    smprate: サンプリングレート
*/
void dft_print(double *data, int datasize, int smprate)
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
void dft_print2(double *data, int datasize, int smprate)
{
    int i;

    for (i = 0; i < datasize; i++)
    {
        printf("%f,%f\n", (double)i, data[i] * 2.0 / datasize);
    }
}