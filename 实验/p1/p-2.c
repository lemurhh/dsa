#include <stdio.h>
#include <stdlib.h>
#define PI 3.14

float area(float);

int main(void)
{
  float r;
  scanf("%f", &r);
  printf("%.3f\n", area(r));
  
  system("Pause");
  return 0;
}

float area(float r)
{
  return PI * r * r;
}
