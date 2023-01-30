/* discrete Fourier transform */

#include "dft.h"

/* calculation of rotation factor */
dftComplex dft_rotation(double angle)
{
    dftComplex cmplx;
    cmplx.real = cos(angle);
    cmplx.imag = sin(angle);

    return cmplx;
}

/* DFT main process */
/*
parameter1 : target signal
parameter2 : output array
parameter3 : sampling rate[Hz]
parameter4 : number of data
*/
void dft(dftComplex *f, dftComplex *f_F, double smp_rate, int datasize)
{
    double ang;
    dftComplex cmplx;

    int l, k;
    for (l = 0; l < datasize; l++)
    {
        f_F[l].real = 0;
        f_F[l].imag = 0;
        for (k = 0; k < datasize; k++)
        {
            ang = -DFT_PI2 * (double)k * (double)l / datasize;
            cmplx = dft_rotation(ang);
            f_F[l] = addComplex(f_F[l], mulComplex(f[k], cmplx));
        }
    }
}