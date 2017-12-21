#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef struct {
  int data[MAXSIZE];
  int length;
}SeqList;

void Insert(SeqList *L, int num)
{
  int Low=0, Mid, High=L->length-1;
  int Flag=0, Pos;
  int i;
  while(Low <= High)
    {
      Mid = (Low + High) / 2;
      if(L->data[Mid] < num)
	Low = Mid + 1;
      else if(L->data[Mid] > num)
	High = Mid - 1;
      else
	{
	  Flag = 1;
	  break;
	}
    }
  if(Flag)
    Pos = num;
  else
    Pos = Low;
  for(i=L->length-1; i>=Pos; i--)
      L->data[i+1] = L->data[i];
  L->data[Pos] = num;
  L->length++;
}

int main(void)
{
  SeqList L;
  L.length = 10;
  int i;
  for(i=0; i<L.length; i++)
    scanf("%d", &(L.data[i]));
  scanf("%d", &i);
  Insert(&L, i);
  for(i=0; i<L.length; i++)
    printf("%d ", L.data[i]);
  putchar('\n');
  return 0;
}
