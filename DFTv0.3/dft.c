/* discrete Fourier transform */

#include "dft.h"

/* addition of complex numbers */
Complex cmplx_add(Complex cmplx1, Complex cmplx2)
{
    Complex cmplx;
    cmplx.real = cmplx1.real + cmplx2.real;
    cmplx.imag = cmplx1.imag + cmplx2.imag;

    return cmplx;
}

/* multiplication of complex numbers */
Complex cmplx_mul(Complex cmplx1, Complex cmplx2)
{
    Complex cmplx;
    cmplx.real = (cmplx1.real * cmplx2.real) - (cmplx1.imag * cmplx2.imag);
    cmplx.imag = (cmplx1.real * cmplx2.imag) + (cmplx1.imag * cmplx2.real);

    return cmplx;
}

/* magnitude of complex */
double cmplx_abs(Complex cmplx)
{
    return sqrt(cmplx.real * cmplx.real + cmplx.imag * cmplx.imag);
}

/* output complex */
void cmplx_print(Complex cmplx)
{
    if ((cmplx.real != 0) && (cmplx.imag < 0))
        printf("%f - j%f", cmplx.real, -cmplx.imag);
    else if ((cmplx.real != 0) && (cmplx.imag == 0))
        printf("%f", cmplx.real);
    else if ((cmplx.real != 0) && (cmplx.imag > 0))
        printf("%f + j%f", cmplx.real, cmplx.imag);
    else if ((cmplx.real == 0) && (cmplx.imag < 0))
        printf("-j%f", -cmplx.imag);
    else if ((cmplx.real == 0) && (cmplx.imag == 0))
        printf("0");
    else if ((cmplx.real == 0) && (cmplx.imag > 0))
        printf("j%f", cmplx.imag);
}

/* calculation of rotation factor */
Complex dft_rotation(double angle)
{
    Complex cmplx;
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
void dft(Complex *f, Complex *f_F, double smp_rate, int datasize)
{
    int halfsize;
    double ang;
    Complex cmplx;

    halfsize = datasize / 2;

    int x, t;
    for (t = 0; t < datasize; t++)
    {
        /* printf("%3.2f %%\n", (double)t * 100.0 / (double)datasize); */
        f_F[t].real = 0;
        f_F[t].imag = 0;
        for (x = 0; x < halfsize; x++)
        {
            ang = -PI2 * (double)x * (double)t / smp_rate;
            cmplx = dft_rotation(ang);
            f_F[t] = cmplx_add(f_F[t], cmplx_mul(f[x], cmplx));
        }
    }
}