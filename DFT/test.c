#include "dft.h"

#include <math.h>
#include <time.h>

#define SMP_RATE 8000 /* サンプリングレート */
#define SMP_TIME 1.0  /* サンプリング時間 */
#define AMP1 3.0      /*波形1の振幅*/
#define AMP2 5.0      /*波形2の振幅*/
#define FREQ1 200     /* 波形1の周波数*/
#define FREQ2 1000    /* 波形2の周波数*/

int main(void)
{
    int i, datasize;
    double *sin1, *sin2, *sin_mix, *result;

    /* データサイズの計算 */
    datasize = (int)(SMP_RATE * SMP_TIME);

    /* 波形用・結果用配列 */
    sin1 = (double *)malloc(sizeof(double) * datasize);
    sin2 = (double *)malloc(sizeof(double) * datasize);
    sin_mix = (double *)malloc(sizeof(double) * datasize);
    result = (double *)malloc(sizeof(double) * datasize);

    /* 正弦波の生成 */
    for (i = 0; i < datasize; i++)
    {
        sin1[i] = AMP1 * sin(DFT_PI2 * FREQ1 * (double)i / (double)datasize);
        sin2[i] = AMP2 * sin(DFT_PI2 * FREQ2 * (double)i / (double)datasize);
        sin_mix[i] = sin1[i] + sin2[i];
    }

    /* フーリエ変換 */
    // result = fft(sin_mix, datasize);
    result = dft(sin_mix, datasize);

    /* 結果の出力 */
    // fft_print2(result, datasize, SMP_RATE);
    dft_print2(result, datasize);

    /* メモリの開放 */
    free(sin1);
    free(sin2);
    free(sin_mix);
    free(result);
}