#include "dft.h"
#include "IO.h"

#define FILE_NAME "sample-data2.txt" /* サンプリングデータファイル */
#define SMP_RATE 8000                /* サンプリングレート[Hz] */

int main(void)
{
    int i, j, data_size, smp_rate;
    double **data, half_rate;
    Complex *f_l, *f_F_l, *f_r, *f_F_r;
    FILE *fp;
    char filename[255];

    fp = fopen(FILE_NAME, "r");
    if (fp == NULL)
    {
        return 1;
    }

    /* input*/
    data = readSample(fp, &data_size);

    f_l = (Complex *)malloc(sizeof(Complex) * data_size);
    if (f_l == NULL)
    {
        fclose(fp);
        return 1;
    }
    f_F_l = (Complex *)malloc(sizeof(Complex) * data_size);
    if (f_F_l == NULL)
    {
        fclose(fp);
        free(f_l);
        return 1;
    }
    f_r = (Complex *)malloc(sizeof(Complex) * data_size);
    if (f_r == NULL)
    {
        fclose(fp);
        free(f_l);
        free(f_F_l);
        return 1;
    }
    f_F_r = (Complex *)malloc(sizeof(Complex) * data_size);
    if (f_F_r == NULL)
    {
        fclose(fp);
        free(f_l);
        free(f_F_l);
        free(f_r);
        return 1;
    }

    for (i = 0; i < data_size; i++)
    {
        f_l[i].real = data[0][i];
        f_r[i].real = data[1][i];
        f_l[i].imag = 0.0;
        f_r[i].imag = 0.0;
    }

    /* DFT */
    dft(f_l, f_F_l, SMP_RATE, data_size);
    dft(f_r, f_F_r, SMP_RATE, data_size);

    /* output */
    half_rate = SMP_RATE / 2;
    printf("Hz\tF.real\tF.imag\t|F|\n");
    for (i = 0; i < data_size; i++)
    {
        printf("%d\t%f\t%f\t%f\t%f\t%f\t%f\n", i, f_F_l[i].real, f_F_l[i].imag, cmplx_abs(f_F_l[i]), f_F_r[i].real, f_F_r[i].imag, cmplx_abs(f_F_r[i]));
    }

    /* end */
    fclose(fp);
    free(f_l);
    free(f_F_l);
    free(f_r);
    free(f_F_r);
    return EXIT_SUCCESS;
}