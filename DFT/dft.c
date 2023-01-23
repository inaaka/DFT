/*
set of functions for Discrete Fourier Transform
2023/01/23
*/

#include "dft.h"

/*
Discrete Fourier Transform
  return:
    Data after DFT
  argument:
    *signal: Data before conversion
    datasize: Number of data
*/
double *dft(double *signal, int datasize)
{
    int i, j;
    double *result;
    dftComplex *cresult, csignal, angle;

    /* Dynamic memory allocation */
    cresult = (dftComplex *)malloc(sizeof(dftComplex) * datasize);
    if (cresult == NULL)
    {
        fprintf(stderr, "Failed to dynamic allocate memory.\n");
        return NULL;
    }
    result = (double *)malloc(sizeof(double) * datasize);
    if (result == NULL)
    {
        fprintf(stderr, "Failed to dynamic allocate memory.\n");
        free(cresult);
        return NULL;
    }

    /* DFT */
    for (i = 0; i < datasize; i++)
    {
        cresult[i] = newComplex(0.0, 0.0);
        for (j = 0; j < datasize; j++)
        {
            csignal = newComplex(signal[j], 0.0);
            angle = newComplex(0.0, -DFT_PI2 * (double)i * (double)j / (double)datasize);
            cresult[i] = addComplex(cresult[i], mulComplex(csignal, expComplex(angle)));
        }
        result[i] = absComplex(cresult[i]);
    }

    return result;
}

/*
Fast Fourier Transform (recursion)
  return:
    Success: 0, Failure: 1
  arguments:
    *signal: Data before FFT -> Data after FFT
    datasize: Number of data
*/
int fft_re(dftComplex *signal, int datasize)
{
    int i, halfsize, n;
    dftComplex *odd, *even, angle;

    /* When the number of data is 1 */
    if (datasize != 1)
    {
        /* Dynamic memory allocation */
        halfsize = datasize / 2;
        odd = (dftComplex *)malloc(sizeof(dftComplex) * halfsize);
        if (odd == NULL)
        {
            return 1;
        }
        even = (dftComplex *)malloc(sizeof(dftComplex) * halfsize);
        if (even == NULL)
        {
            free(odd);
            return 1;
        }

        /* Data Division */
        for (i = 0; i < halfsize; i++)
        {
            even[i] = signal[i * 2];
            odd[i] = signal[i * 2 + 1];
        }

        /* FFT recursion */
        n = fft_re(even, halfsize);
        n += fft_re(odd, halfsize);

        if (n)
        {
            free(even);
            free(odd);
            return 1;
        }

        /* Data Merging */
        for (i = 0; i < datasize; i++)
        {
            angle = newComplex(0.0, -DFT_PI2 * (double)i / (double)datasize);
            signal[i] = addComplex(even[i % halfsize], mulComplex(odd[i % halfsize], expComplex(angle)));
        }

        /* Free up memory */
        free(even);
        free(odd);
    }

    return 0;
}

/*
Fast Fourier Transform (recursion)
  return:
    Data after FFT
  arguments:
    *signal: Data before FFT
    datasize: Number of data
*/
double *fft(double *signal, int datasize)
{
    int i, datasize2, n;
    double *result;
    dftComplex *csignal;

    /* Match the number of data to the n-th power of 2 */
    datasize2 = 1;
    while (datasize2 < datasize)
    {
        datasize2 *= 2;
    }

    /* Dynamic memory allocation */
    csignal = (dftComplex *)malloc(sizeof(dftComplex) * datasize2);
    for (i = 0; i < datasize; i++)
    {
        csignal[i] = newComplex(signal[i], 0.0);
    }
    for (/* i = datasize */; i < datasize2; i++)
    {
        csignal[i] = newComplex(0.0, 0.0);
    }

    /* FFT */
    n = fft_re(csignal, datasize2);

    if (n)
    {
        free(csignal);
        return NULL;
    }

    /* Convert converted data to real numbers */
    result = (double *)malloc(sizeof(double) * datasize);
    for (i = 0; i < datasize; i++)
    {
        result[i] = absComplex(csignal[i]);
    }

    /* Free up memory */
    free(csignal);

    return result;
}

/*
Output data after DFT
  arguments:
    *data: Data after DFT
    datasize: Number of data
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
Output data after DFT /(N/2)
  arguments:
    *data: Data after DFT
    datasize: Number of data
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
Output data after FFT
  arguments:
    *data: Data after DFT
    datasize: Number of data
    smprate: sampling rate
*/
void fft_print(double *data, int datasize, int smprate)
{
    int i, datasize2;

    /* Match the number of data to the n-th power of 2 */
    datasize2 = 1;
    while (datasize2 < datasize)
    {
        datasize2 *= 2;
    }

    /* Output */
    for (i = 0; i < datasize; i++)
    {
        printf("%f,%f\n", (double)i * smprate / (double)datasize2, data[i]);
    }
}

/*
Output data after FFT /(N/2)
  arguments:
    *data: Data after DFT
    datasize: Number of data
    smprate: sampling rate
*/
void fft_print2(double *data, int datasize, int smprate)
{
    int i, datasize2;

    /* Match the number of data to the n-th power of 2 */
    datasize2 = 1;
    while (datasize2 < datasize)
    {
        datasize2 *= 2;
    }

    /* Output */
    for (i = 0; i < datasize; i++)
    {
        printf("%f,%f\n", (double)i * smprate / (double)datasize2, data[i] * 2.0 / datasize);
    }
}