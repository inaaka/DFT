/*
離散フーリエ変換関数群
2023/01/21 更新
*/

/* ヘッダファイル */
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

/* マクロ定義 */
#define DFT_PI2 6.283185307179586

/* 離散フーリエ変換 */
double *dft(double *signal, int datasize);
/* 高速フーリエ変換（再帰用） */
void fft_re(double complex *signal, int datasize);
/* 高速フーリエ変換 */
double *fft(double *signal, int datasize);
/* 離散フーリエ変換後のデータを出力 */
void dft_print(double *data, int datasize);
/* 離散フーリエ変換後のデータ/(N/2) を出力 */
void dft_print2(double *data, int datasize);
/* 高速フーリエ変換後のデータを出力 */
void fft_print(double *data, int datasize, int smprate);
/* 高速フーリエ変換後のデータ/(N/2) を出力 */
void fft_print2(double *data, int datasize, int smprate);