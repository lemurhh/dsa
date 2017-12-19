#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int datatype;
typedef struct {
  datatype data[MAXSIZE]; //0处不存放数据
  int length;
}SeqList;

int Search(SeqList L, datatype key)
{
  int i;
  L.data[0] = key;
  i = L.length;
  while(L.data[i] != key)
    i--;
  return i;
}

int main(void)
{
  SeqList L;
  datatype key;
  int i;
  
  printf("Input the Num Of Data: ");
  scanf("%d", &(L.length));
  printf("Input the Data: ");
  for(i=1; i<=L.length; i++)
    scanf("%d", &(L.data[i]));
  
  printf("Input the Searched Data: ");
  scanf("%d", &key);
  if(i=Search(L, key))
    printf("Loc: %d\n", i);
  else
    printf("Not Found!\n");

  return 0;
}
  
