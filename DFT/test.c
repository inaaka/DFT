#include "dft.h"

#include <math.h>
#include <time.h>

#define SMP_RATE 44100 /* sampling rate */
#define SMP_TIME 3.0   /* sampling time */
#define AMP1 3.0       /* Amplitude of waveform 1 */
#define AMP2 5.0       /* Amplitude of waveform 2 */
#define FREQ1 300      /* Frequency of waveform 1 */
#define FREQ2 1000     /* Frequency of waveform 2 */

int main(void)
{
    int i, datasize;
    double *sin1, *sin2, *sin_mix, *result;

    /* Calculation of data size */
    datasize = (int)(SMP_RATE * SMP_TIME);

    /* Dynamic memory allocation */
    sin1 = (double *)malloc(sizeof(double) * datasize);
    sin2 = (double *)malloc(sizeof(double) * datasize);
    sin_mix = (double *)malloc(sizeof(double) * datasize);
    result = (double *)malloc(sizeof(double) * datasize);

    /* Sine wave generation */
    for (i = 0; i < datasize; i++)
    {
        sin1[i] = AMP1 * sin(DFT_PI2 * FREQ1 * (double)i / (double)datasize);
        sin2[i] = AMP2 * sin(DFT_PI2 * FREQ2 * (double)i / (double)datasize);
        sin_mix[i] = sin1[i] + sin2[i];
    }

    /* Fourier transform */
    result = fft(sin_mix, datasize);
    // result = dft(sin_mix, datasize);

    /* Output Results */
    fft_print2(result, datasize);
    // dft_print2(result, datasize);

    /* Free up memory */
    free(sin1);
    free(sin2);
    free(sin_mix);
    free(result);

    return 0;
}