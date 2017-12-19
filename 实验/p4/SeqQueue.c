#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 20
#define OK 1
#define ERROR -1

typedef int Status;
typedef int datatype;

typedef struct SQueue{
  datatype data[MAXSIZE];
  int front;
  int rear;
}SQueue;

void InitQueue(SQueue *Q)
{
  Q->front = 0;
  Q->rear = 0;
}

void PrintQueue(SQueue *Q)
{
  int i;
  for(i=Q->front; i != Q->rear; i = (i+1)%MAXSIZE)
    printf("%d ", Q->data[i]);
  putchar('\n');
}

int GetFront(SQueue *Q)
{
  return Q->data[Q->front];
}

int IsEmpty(SQueue *Q)
{
  return Q->rear==Q->front;
}

int GetLength(SQueue *Q)
{
  return (Q->rear+MAXSIZE - Q->front) % MAXSIZE;
}

Status EnQueue(SQueue *Q, datatype x)
{
  if((Q->rear+1) % MAXSIZE == Q->front)
      return ERROR;
  
  Q->data[Q->rear] = x;
  Q->rear = (Q->rear+1) % MAXSIZE;
  
  return OK;  
}

Status DeQueue(SQueue *Q, datatype *x)
{
  if(Q->front==Q->rear)
    return ERROR;

  *x = Q->data[Q->front];
  Q->front = (Q->front+1) % MAXSIZE;

  return OK;
}

void Menu(SQueue *Q)
{
  char cmd;
  const char *legal="iIeEdDfFlLjJpPqQ";
  int i, len;
  datatype x;
  do
    {
      putchar('\n');
      printf("i,I  初始化空队列\n");
      printf("e,E  入队\n");
      printf("d,D  出队\n");
      printf("f,F 取队首元素\n");
      printf("l,L 队列长度\n");
      printf("j,J 判队空\n");
      printf("p,P  打印队列\n");
      printf("q,Q 退出\n");
      putchar('\n');
      do
	{
	  printf("请输入命令: ");
	  fflush(stdin);
	  scanf("%c", &cmd);
	}
      while( strchr(legal, cmd)==NULL );
      putchar('\n');
      switch(cmd)
	{
	case 'i':
	case 'I':
	  InitQueue(Q);
	  break;
	case 'e':
	case 'E':
	  printf("Data: ");
	  scanf("%d", &x);
	  if(EnQueue(Q, x) == ERROR)
	    printf("The Queue is FULL!\n");
	  PrintQueue(Q);
	  break;
	case 'd':
	case 'D':
	  if(DeQueue(Q, &x) == OK)
	    printf("Deleted Data: %d\n", x);
	  else
	    printf("The Queue is EMPTY!\n");
	  PrintQueue(Q);
	  break;
	case 'f':
	case 'F':
	  printf("The First Data: %d\n", GetFront(Q));
	  break;
	case 'l':
	case 'L':
	  printf("The Length of Queue: %d\n", GetLength(Q));
	  break;
	case 'j':
	case 'J':
	  (IsEmpty(Q)) ? (printf("The Queue is Empty.\n")) : (printf("The Queue is NOT Empty.\n"));
	  break;
	case 'p':
	case 'P':
	  PrintQueue(Q);
	  break;
	}
    }
  while( (cmd!='q') && (cmd!='Q') );
}

int main(void)
{
  SQueue Q;
  Menu(&Q);
  return 0;
}
  
