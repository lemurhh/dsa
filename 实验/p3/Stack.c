#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 20
#define OK 1
#define ERROR -1

#define PAIR_ERROR 1
#define RIGHT_MORE 2
#define LEFT_MORE 3
#define PAIR_RIGHT 4


typedef int Status;
typedef char datatype;
typedef struct SeqSatack{
  datatype data[MAXSIZE];
  int top;
}SeqStack;

void InitStack(SeqStack *S);
int IsEmpty(SeqStack *S);
Status Push(SeqStack *S, datatype x);
Status Pop(SeqStack *S, datatype *x);
Status Judge(char *str, int len);

int main(void)
{
  char str[20];
  int status;
  printf("ÊäÈëÀ¨ºÅ±í´ïÊ½£º ");
  scanf("%s", str);
  status = Judge(str, strlen(str));
  if(status == PAIR_RIGHT)
    printf("×óÓÒÀ¨ºÅÆ¥ÅäÕýÈ·\n");
  else if(status == PAIR_ERROR)
    printf("×óÓÒÀ¨ºÅÅä¶Ô´ÎÐò²»ÕýÈ·\n");
  else if(status == RIGHT_MORE)
    printf("ÓÒÀ¨ºÅ¶àÓÚ×óÀ¨ºÅ\n");
  else if(status == LEFT_MORE)
    printf("×óÀ¨ºÅ¶àÓÚÓÒÀ¨ºÅ\n");
  return 0;
}
void InitStack(SeqStack *S)
{
  S->top = -1;
}
int IsEmpty(SeqStack *S)
{
  return (S->top==-1) ? 1 : 0;
}
Status Push(SeqStack *S, datatype x)
{
  if(S->top == MAXSIZE-1)
    {
      printf("Full\n");
      return ERROR;
    }
  S->top++;
  S->data[S->top] = x;
  return OK;
}

Status Pop(SeqStack *S, datatype *x)
{
  if(S->top == -1)
    {
      printf("Empty\n");
      return ERROR;
    }
  *x = S->data[S->top];
  S->top--;
  return OK;
}

Status Judge(char *str, int len)
{
  SeqStack S;
  int i;
  char tmp, x;

  InitStack(&S);

  for(i=0; i<len; i++)
    {
      tmp = str[i];
      if( tmp=='[' || tmp=='(' )
	Push(&S, tmp);
      else if( tmp==']')
	{
	  if(IsEmpty(&S))
	    return RIGHT_MORE;
	  Pop(&S, &x);
	  if(x != '[')
	    return PAIR_ERROR;
	}
      else if( tmp==')' )
	{
	  if(IsEmpty(&S))
	    return RIGHT_MORE;
	  Pop(&S, &x);
	  if(x != '(')
	    return PAIR_ERROR;
	}
    }
  if(!IsEmpty(&S))
    {
      Pop(&S, &x);
      if(x==']' || x==')')
	return RIGHT_MORE;
      else if(x=='[' || x=='(')
	return LEFT_MORE;
    }
  return PAIR_RIGHT;
}


