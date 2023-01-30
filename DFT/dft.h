/* discrete Fourier transform */

#ifndef DFT_H
#define DFT_H

#include "complex_dft.h"
#include "dft_define.h"

/* include header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* calculation of rotation factor */
dftComplex dft_rotation(double angle);

/* dft main process */
void dft(dftComplex *f, dftComplex *f_F, double smp_rate, int datasize);

#endif