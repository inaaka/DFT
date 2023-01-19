#include "IO.h"
#include "fft.h"
#include "fft_define.h"

#define LR 1 /* 音声のチャンネル 0-1 */

/* *.exe filename sampling_rate */
int main(int argc, char *argv[])
{
    int i, data_size, half_size;
    double **wave, *data;
    FILE *fp;
    fftComplex *datac;

    /* 引数のチェック */
    if (argc != 3)
    {
        fprintf(stderr, "argc != 2\n");
        return 1;
    }

    /* ファイルのオープン */
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        fprintf(stderr, "fopen == NULL\n");
        return 1;
    }

    /* データの読み込み */
    wave = readSample(fp, &data_size);
    data = two_pwr(wave[LR], &data_size);
    free(wave[0]);
    free(wave[1]);
    free(wave);
    datac = (fftComplex *)malloc(sizeof(fftComplex) * data_size);
    for (i = 0; i < data_size; i++)
    {
        datac[i].real = data[i];
        datac[i].imag = 0.0;
    }

    /* fft */
    fft(datac, data_size);
    printFFT(datac, data_size, atoi(argv[2]));

    free(datac);
    fclose(fp);
    return 0;
}