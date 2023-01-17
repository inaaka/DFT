/*
ファイル読み書き関数群
*/

#include "IO.h"

/*
Audacityで出力した音声サンプリングデータの読み込み
  戻り値
    サンプリングデータ
  パラメータ
    *fp: ファイルポインタ（モード:"r"）
    *data: データ数保存用

  ※注意
    サンプリングデータの出力は次のように設定してください.
      音声数：ステレオ
      計測スケール: リニア
      インデックス（テキストファイル時のみ）: 無し
      ヘッダ情報を含める : 無し
      ヘッダー追記文:
      ステレオチャンネル記述欄: 左右を同じ行に
*/
double **readSample(FILE *fp, int *data_size)
{
  double **smp_data;
  int i, data_num;
  char c;

  /* データ数のカウント */
  fseek(fp, 0L, SEEK_SET);
  data_num = 0;
  while ((c = fgetc(fp)) != EOF)
  {
    if (c == '\n')
    {
      data_num++;
    }
  }
  *data_size = data_num;
  fseek(fp, 0L, SEEK_SET);

  /* 出力データ用領域の確保 */
  smp_data = (double **)malloc(sizeof(double *) * 2);
  for (i = 0; i < 2; i++)
  {
    smp_data[i] = (double *)malloc(sizeof(double) * data_num);
  }

  /* 出力データの読み込み */
  for (i = 0; i < data_num; i++)
  {
    fscanf(fp, "%lf %lf\n", &smp_data[0][i], &smp_data[1][i]);
  }

  return smp_data;
}