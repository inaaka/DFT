/*
set of functions for Discrete Fourier Transform
2023/01/23
*/

#include <stdio.h>
#include <stdlib.h>
#include "complex_dft.h"

#define DFT_PI2 6.283185307179586

/* Discrete Fourier Transform */
double *dft(double *signal, int datasize);
/* Fast Fourier Transform (recursion) */
int fft_re(dftComplex *signal, int datasize);
/* Fast Fourier Transform */
double *fft(double *signal, int datasize);
/* Output data after DFT */
void dft_print(double *data, int datasize);
/* Output data after DFT / (N/2) */
void dft_print2(double *data, int datasize);
/* Output data after FFT */
void fft_print(double *data, int datasize);
/* Output data after FFT /(N/2) */
void fft_print2(double *data, int datasize);