#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(float **matrix, int n)
{
  int i,  j, min;
  float tmp;
  float *sum;
  sum = (float *)malloc(sizeof(float) * n);
  memset(sum, 0.0, sizeof(float)*n);

  for(i=0; i<n; i++)
    for(j=0; j<n; j++)
	sum[i] += matrix[i][j];
  
  for(i=0; i<n; i++)
    {
      min = i;
      for(j=i+1; j<n; j++)
	{
	  if(sum[j] < sum[min])
	    min = j;
	}
      if(min != i)
	{
	  //交换矩阵的两行i和min，交换sum中的元素
	  for(j=0; j<n; j++)
	    {
	      tmp = matrix[i][j];
	      matrix[i][j] = matrix[min][j];
	      matrix[min][j] = tmp;
	    }
	  tmp = sum[i];
	  sum[i] = sum[min];
	  sum[min] = tmp;
	}
    }

    free(sum);
}

int main(void)
{
  float **matrix = (float **)malloc(sizeof(float) *4*4);
  matrix[0]=(float *)malloc(sizeof(float)*4);
  matrix[1]=(float *)malloc(sizeof(float)*4);
  matrix[2]=(float *)malloc(sizeof(float)*4);
  matrix[3]=(float *)malloc(sizeof(float)*4);
  int i, j;
  int n=4;
  for(i=0; i<n; i++)
    for(j=0; j<n; j++)
      scanf("%f", &matrix[i][j]);

  for(i=0; i<n; i++)
    {
      for(j=0; j<n; j++)
	printf("%.2f ", matrix[i][j]);
      putchar('\n');
    }
  putchar('\n');
  sort(matrix, 4);

  for(i=0; i<n; i++)
    {
      for(j=0; j<n; j++)
	printf("%.2f ", matrix[i][j]);
      putchar('\n');
    }

    return 0;
}
