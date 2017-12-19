/*
 合并两单增有序链表为一个单增有序链表
*/

#include <stdio.h>
#include <stdlib.h>
typedef struct LNode{
  int data;
  struct LNode *next;
}LNode, * LinkList;

void MergeSort(LinkList A, LinkList B)
{
  LNode *PreA, *PreB, *CurA, *CurB;
  PreA = A;
  PreB = B;
  CurA = A->next;
  CurB = B->next;

  while(CurA && CurB)
    {
      if(CurB->data <= CurA->data)
	{
	  PreB = CurB;
	  CurB = CurB->next;
	  PreA->next = PreB;
	  PreB->next = CurA;
	  PreA = PreB;
	}
      /*
      else if(CurB->data >= PreA->data && CurB->data<=CurA->data)
	{
	  PreB = CurB;
	  CurB = CurB->next;
	  PreA->next = PreB;
	  PreB->next = CurA;
	  PreA = PreB;
	}
      */
      else
	{
	  PreA = CurA;
	  CurA = CurA->next;
	}
    }
  if(CurB) //B不空
      PreA->next = CurB;
}

int main(void)
{
  LinkList A, B;
  LNode *tmp;
  LNode *tail, *p;
  int i;
  A = (LinkList)malloc(sizeof(struct LNode));
  B = (LinkList)malloc(sizeof(struct LNode));
  A->next = NULL;
  B->next = NULL;
  
  tail = A;
  
  for(i=0;i<5;i++)
    {
      tmp = (LNode *)malloc(sizeof(struct LNode));
      scanf("%d",&(tmp->data));
      tail->next = tmp;
      tail = tmp;
    }

  tail = B;
  for(i=0;i<10;i++)
    {
      tmp = (LNode *)malloc(sizeof(struct LNode));
      scanf("%d",&(tmp->data));
      tail->next = tmp;
      tail = tmp;
    }

  MergeSort(A, B);

  p = A->next;
  while(p)
    {
      printf("%d ", p->data);
      p = p->next;
    }
  putchar('\n');
  return 0;
}
  
      
