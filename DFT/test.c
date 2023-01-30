#include "dft.h"

#include <math.h>
#include <time.h>

#define SMP_RATE 8000 /* sampling rate */
#define SMP_TIME 0.3  /* sampling time */
#define AMP1 2.0      /* Amplitude of waveform 1 */
#define AMP2 4.0      /* Amplitude of waveform 2 */
#define FREQ1 1000    /* Frequency of waveform 1 */
#define FREQ2 3000    /* Frequency of waveform 2 */

int main(void)
{
    int i, datasize;
    double *sin1, *sin2;
    dftComplex *sin_mix, *result;

    /* Calculation of data size */
    datasize = (int)(SMP_RATE * SMP_TIME);

    /* Dynamic memory allocation */
    if ((sin1 = (double *)malloc(sizeof(double) * datasize)) == NULL)
    {
        return EXIT_FAILURE;
    }
    if ((sin2 = (double *)malloc(sizeof(double) * datasize)) == NULL)
    {
        free(sin1);
        return EXIT_FAILURE;
    }
    if ((sin_mix = (dftComplex *)malloc(sizeof(dftComplex) * datasize)) == NULL)
    {
        free(sin1);
        free(sin2);
        return EXIT_FAILURE;
    }
    if ((result = (dftComplex *)malloc(sizeof(dftComplex) * datasize)) == NULL)
    {
        free(sin1);
        free(sin2);
        free(sin_mix);
        return EXIT_FAILURE;
    }

    /* Sine wave generation */
    for (i = 0; i < datasize; i++)
    {
        sin1[i] = AMP1 * sin(DFT_PI2 * FREQ1 * (double)i * SMP_TIME / datasize);
        sin2[i] = AMP2 * sin(DFT_PI2 * FREQ2 * (double)i * SMP_TIME / datasize);
        sin_mix[i] = newComplex(sin1[i] + sin2[i], 0.0);
    }

    /* Free up memory */
    free(sin1);
    free(sin2);

    /* Fourier transform */
    dft(sin_mix, result, SMP_RATE, datasize);

    /* Output Results */
    printf("t[s],data,f[Hz],dft\n");
    for (i = 0; i < datasize; i++)
    {
        printf("%f,%f,%f,%f\n", (double)i / SMP_RATE, sin_mix[i].real, (double)SMP_RATE * i / datasize, absComplex(result[i]));
    }

    /* Free up memory */
    free(sin_mix);
    free(result);

    return 0;
}
