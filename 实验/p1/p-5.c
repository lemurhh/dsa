#include <stdio.h>
#include <stdlib.h>

int  main(void)
{
  int i;
  float sum, min, n;
  scanf("%f", &n);
  
  sum = min = n;
  for(i=0; i<14; i++)
    {
      scanf("%f", &n);
      sum += n;
      min = (min<=n) ? min : n;
    }
  
  printf("Ave:%.3f Min:%.3f\n", sum/15, min);

  system("Pause");
  return 0;
}
  
