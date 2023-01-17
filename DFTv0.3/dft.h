/* discrete Fourier transform */

#ifndef DFT_H
#define DFT_H

#include "dft_define.h"

/* include header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* addition of complex numbers */
Complex cmplx_add(Complex cmplx1, Complex cmplx2);

/* multiplication of complex numbers */
Complex cmplx_mul(Complex cmplx1, Complex cmplx2);

/* magnitude of complex */
double cmplx_abs(Complex cmplx);

/* output complex */
void cmplx_print(Complex cmplx);

/* calculation of rotation factor */
Complex dft_rotation(double angle);

/* dft main process */
void dft(Complex *f, Complex *f_F, double smp_rate, int datasize);

#endif