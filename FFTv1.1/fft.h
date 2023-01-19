/*
高速フーリエ変換用関数群
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fft_define.h"

/* 複素数の加算 */
fftComplex cmplx_add(fftComplex cmplx1, fftComplex cmplx2);

/* 複素数の乗算 */
fftComplex cmplx_mul(fftComplex cmplx1, fftComplex cmplx2);

/* 複素数の大きさ */
double cmplx_abs(fftComplex cmplx);

/* 回転因子の計算 */
fftComplex fft_rotation(double angle);

/* 高速フーリエ変換 */
void fft(fftComplex *data, int data_size);

/* データ数を2のn乗数にする */
double *two_pwr(double *data, int *data_size);

/* フーリエ変換結果の表示 */
void printFFT(fftComplex *data, int data_size, int smp_rate);