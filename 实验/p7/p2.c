#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int datatype;
typedef struct {
  datatype data[MAXSIZE];
  int length;
}SeqList;

int BinarySearch(SeqList L, datatype key)
{
  int Low, Mid, High;

  Low = 1;
  High = L.length-1;
  while(Low <= High)
    {
      Mid = (Low + High) / 2;
      if(L.data[Mid] < key)
	Low = Mid + 1;
      else if(L.data[Mid] > key)
	High = Mid - 1;
      else
	return Mid;
    }
  return 0;
}

int main(void)
{
  SeqList L;
  datatype key;
  int i;

  printf("Input the Num Of Data: ");
  scanf("%d", &(L.length));
  printf("Input the Sorted Data: ");
  for(i=1; i<=L.length; i++)
    scanf("%d", &(L.data[i]));
  
  printf("Input the Searched Data: ");
  scanf("%d", &key);
  if(i=BinarySearch(L, x))
    printf("Loc: %d\n", i);
  else
    printf("Not Found!\n");

  return 0;
}
