#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  int a[8] = {1,2,3,4,5,6,7,8};
  int b[8];
  int left = 0, right = 7;
  int i, t;
  //����a��4��λ��
  for(i=0; i<8; i++)
      if(a[i]==4) {printf("4��λ�ã�%d\n", i); break;}
  //���ƣ�a->b
  memcpy(b, a, sizeof(a));
  //����a
  while(left < right)
    {
      t=a[left]; a[left]=a[right]; a[right]=t; left++; right--;
    }
  //���a, b
  for(i=0; i<8; i++)
    printf("a[%d]==%d\n", i, a[i]);
  for(i=0; i<8; i++)
    printf("b[%d]==%d\n", i, b[i]);
  
  system("Pause");
  return 0;
}
