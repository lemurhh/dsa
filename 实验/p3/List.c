#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR -1

typedef int Status;
typedef int datatype;

typedef struct LNode{
  datatype data;
  struct LNode *next;
}LNode, *LinkList;

void Menu(LinkList L);
int LocError(int i, LNode *p);
void CreateListHead(LinkList L, int n);
void CreateListTail(LinkList L, int n);
Status Insert(LinkList L, int i, datatype x);
Status Delete(LinkList L, int i, datatype *x);
Status Find(LinkList L, datatype x);
Status Modify(LinkList L, int i);
int GetLength(LinkList L);
void Reverse(LinkList L);
void Print(LinkList L);

int main(void)
{
  LinkList L;
  L = (LinkList)malloc(sizeof(struct LNode));
  Menu(L);
  return 0;
}
void Menu(LinkList L)
{
  char cmd;
  const char *legal="HhTtiIfFdDmMpPrRqQlL";
  int i, len;
  datatype x;
  do
    {
      putchar('\n');
      printf("h,H  头插创建\n");
      printf("t,T  尾插创建\n");
      printf("i,I  插入\n");
      printf("d,D  删除\n");
      printf("m,M  修改\n");
      printf("r,R  逆置\n");
      printf("f,F  查找\n");
      printf("l,L  表长\n");
      printf("p,P  输出\n");
      printf("q,Q  退出\n");
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
	case 'h':
	case 'H':
	  printf("Len: ");
	  scanf("%d", &len);
	  CreateListHead(L, len);
	  Print(L);
	  break;
	case 't':
	case 'T':
	  printf("Len: ");
	  scanf("%d", &len);
	  CreateListTail(L, len);
	  Print(L);
	  break;
	case 'i':
	case 'I':
	  printf("LOC: ");
	  scanf("%d", &i);
	  printf("Data: ");
	  scanf("%d", &x);
	  Insert(L, i, x);
	  Print(L);
	  break;
	case 'f':
	case 'F':
	  printf("Data: ");
	  scanf("%d", &x);
	  Find(L, x);
	  break;
	case 'd':
	case 'D':
	  printf("LOC: ");
	  scanf("%d", &i);
	  Delete(L, i, &x);
	  Print(L);
	  break;
	case 'm':
	case 'M':
	  printf("LOC: ");
	  scanf("%d", &i);
	  Modify(L, i);
	  Print(L);
	  break;
	case 'p':
	case 'P':
	  Print(L);
	  break;
	case 'r':
	case 'R':
	  Reverse(L);
	  Print(L);
	  break;
	case 'l':
	case 'L':
	  printf("Len: %d\n", GetLength(L));
	  break;
	}
    }
  while( (cmd!='q') && (cmd!='Q') );
}

void CreateListHead(LinkList L, int n)
{
  LNode *tmp;
  int i;

  L->next = NULL;
  for(i=0; i<n; i++)
    {
      tmp = (LNode *)malloc(sizeof(struct LNode));
      scanf("%d", &(tmp->data));
      tmp->next = L->next;
      L->next = tmp;
    }
}

void CreateListTail(LinkList L, int n)
{
  LNode *tmp, *tail;
  int i;

  tail = L;

  for(i=0; i<n; i++)
    {
      tmp = (LNode *)malloc(sizeof(struct LNode));
      scanf("%d", &(tmp->data));
      tail->next = tmp;
      tail = tmp;
    }
  tail->next =NULL;
}

Status Insert(LinkList L, int i, datatype x) //将元素插入第i个位置(位序)
{
  LNode *p, *tmp;
  int j;

  p = L;
  j = 0;

  while(p && j<=i-2) //查找原表中的第i-1个节点
    {
      p = p->next;
      j++;
    }

  if(i<=0 || p==NULL)
    {
      printf("LOC ERROR\n");
      return ERROR;
    }

  tmp = (LNode *)malloc(sizeof(struct LNode));
  tmp->data = x;

  tmp->next = p->next;
  p->next = tmp;
  return OK;
}

Status Delete(LinkList L, int i, datatype *x)
{
  LNode *p, *tmp;
  int j;

  p = L;
  j = 0;

  while(p && j<=i-2)
    {
      p = p->next;
      j++;
    }

  if(i<=0 || p==NULL || p->next==NULL)
    {
      printf("LOC ERROR\n");
      return ERROR;
    }

  tmp = p->next;
  p->next = tmp->next;
  *x = tmp->data;
  free(tmp);
  return OK;
}

Status Find(LinkList L, datatype x)
{
  LNode *p;
  int j;

  p = L->next;
  j = 1;

  while(p)
    {
      if( (p->data) == x )
	{
	  printf("LOC: %d\n", j);
	  return OK;
	}
      else
	{
	  p = p->next;
	  j++;
	}
    }

  if(p == NULL)
    {
      printf("NOT FOUND\n");
      return ERROR;
    }
}
Status Modify(LinkList L, int i)
{
  LNode *p;
  int j;

  p = L->next;
  j = 1;

  while(p && j<=i-1)
    {
      p = p->next;
      j++;
    }

    if(i<=0 || p==NULL)
    {
      printf("LOC ERROR\n");
      return ERROR;
    }

    printf("Input the new data: ");
    scanf("%d", &(p->data));
    return OK;
}

int GetLength(LinkList L)
{
  LNode *p;
  int len;

  p = L->next;
  len = 0;

  while(p)
    {
      len++;
      p = p->next;
    }

  return len;
}

void Reverse(LinkList L)
{
  LNode *Pre, *Cur, *Nxt;

  Pre = L;
  Cur = L->next;

  while(Cur)
    {
      Nxt = Cur->next;
      Cur->next = Pre;

      Pre = Cur;
      Cur = Nxt;
    }

  L->next->next = NULL;
  L->next = Pre;
}

void Print(LinkList L)
{
  LNode *p;

  p = L->next;

  printf("List: ");
  while(p)
    {
      printf("%d ", p->data);
      p = p->next;
    }

  putchar('\n');
}
