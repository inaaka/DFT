/*
ファイル読み書き関数群
*/

#include <stdio.h>
#include <stdlib.h>

/* 音声サンプリングデータの読み込み */
double **readSample(FILE *fp, int *data_size);