/*
 *判断是否为中心对称字符串
*/

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef struct LNode{
  char data;
  struct LNode *next;
}LNode, *LinkList;

typedef struct SeqStack{
  char stack[MAXSIZE];
  int top;
}SeqStack;

void Push(SeqStack *S, char x)
{
  if(S->top == MAXSIZE-1)
    return ;
  S->top++;
  S->stack[S->top] = x;
}
char Pop(SeqStack *S)
{
  if(S->top==-1)
    return -1;
  return S->stack[S->top--];
}

int Judge(LinkList L)
{
  SeqStack S;
  LNode *p;

  S.top = -1;
  p = L->next;

  while(p)
    {
      Push(&S, p->data);
      p = p->next;
    }

  p = L->next;
  while(p)
    {
      if(p->data!=Pop(&S))
	return -1;
      else
	p = p->next;
    }
  return 1;
}
int  main(void)
{
  LinkList L;
  LNode *tmp, *tail;
  int i;
  L = (LinkList)malloc(sizeof(struct LNode));

  tail = L;
  for(i=0;i<6;i++)
    {
      tmp = (LNode *)malloc(sizeof(struct LNode));
      fflush(stdin);
      scanf("%c",&(tmp->data));
      tail->next = tmp;
      tail=tmp;
    }
  if(Judge(L)==1)
    printf("yes\n");
  else
    printf("no\n");

  return 0;
}
