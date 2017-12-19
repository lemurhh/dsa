#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int n;
  scanf("%d", &n);
  
  printf("%d%d%d\n", n%10, n/10%10, n/100);
  
  system("Pause");
  return 0;
}
