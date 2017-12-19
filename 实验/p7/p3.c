/*
 *二叉排序树
 *创建、查找、插入、删除、输出
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR 0
#define OK 1
#define MAXSIZE 100

typedef int Status;
typedef struct {
  int data[MAXSIZE];
  int length;
}SeqList;
typedef struct BiTNode{
  int data;
  struct BiTNode *left;
  struct BiTNode *right;
}BiTNode, *BiTree;

void InsertSort(SeqList *L);
int SeqSearch(SeqList L, int key);
int BinarySearch(SeqList L, int key);
Status SearchBST(BiTree T, int key, BiTree Par, BiTree *Pos);
Status InsertBST(BiTree *T, int key);
void CreateBST(BiTree *T, int *Num, int n);
Status Delete(BiTree *T);
Status DeleteBST(BiTree *T, int key);
void PrintBST(BiTree T);
void Menu();

void Menu()
{
  SeqList L, SL;
  BiTree T = NULL;
  BiTree Pos;
  int BNum[MAXSIZE];
  int key, n, i;
  
  char cmd,tmp;
  const char *legal="eEsSbBcCfFiIdDpPqQ";

  do
    {
      putchar('\n');
      printf("e,E  线性表创建\n");
      printf("s,S  顺序查找\n");
      printf("b,B  二分查找\n");
      printf("c,C  二叉排序树创建\n");
      printf("f,F  二叉排序树查找\n");
      printf("i,I  二叉排序插入\n");
      printf("d,D  二叉排序删除\n");
      printf("p,P  二叉排序输出\n");
      printf("q,Q  退出\n");
      putchar('\n');
  do
    {
      printf("cmd: ");
      while((tmp=getchar()) == '\n')
	;
      cmd = tmp;
    }
  while( strchr(legal, cmd)==NULL );
  putchar('\n');
  switch(cmd)
    {
    case 'e':
    case 'E':
        printf("Input the Num Of Data: ");
	scanf("%d", &(L.length));
	if(L.length>MAXSIZE || L.length<=0)
	  printf("The Data Is Too Long or Too Short!Retry!\n");
	else
	  {
	    printf("Input the Data: ");
	    for(i=1; i<=L.length; i++)
	      scanf("%d", &(L.data[i]));
	  }
	break;
    case 's':
    case 'S':
      printf("Input the Searched Data: ");
      scanf("%d", &key);
      if(i=SeqSearch(L, key))
	printf("Loc: %d\n", i);
      else
	printf("Not Found!\n");
      break;
    case 'b':
    case 'B':
      printf("Input the Searched Data: ");
      scanf("%d", &key);
      
      SL.length = L.length;
      memcpy(SL.data, L.data, (sizeof(int)*(L.length+1)));
      
      InsertSort(&SL);
      printf("Sorted Data: ");
      for(i=1; i<=SL.length; i++)
	printf("%d ", SL.data[i]);
      putchar('\n');

      if(i=BinarySearch(SL, key))
	printf("Loc: %d\n", i);
      else
	printf("Not Found!\n");
      break;
    case 'c':
    case 'C':
      printf("Input the Num Of Data: ");
      scanf("%d", &n);
      printf("Input the Data: ");
      for(i=0; i<n; i++)
	scanf("%d", &BNum[i]);
      CreateBST(&T, BNum, n);
      putchar('\n');
      PrintBST(T);
      break;
    case 'f':
    case 'F':
      printf("Input the Searched Data: ");
      scanf("%d", &key);
      if(SearchBST(T, key, NULL, &Pos))
	printf("Found!");
      else
	printf("Not Found!");
      break;
    case 'i':
    case 'I':
      printf("Input the Data: ");
      scanf("%d", &key);
      if(InsertBST(&T, key))
	{
	  putchar('\n');
	  PrintBST(T);
	}
      else
	  printf("The Data exists!\n");
      break;
    case 'd':
    case 'D':
      printf("Input the Data: ");
      scanf("%d", &key);
      DeleteBST(&T, key);
      putchar('\n');
      PrintBST(T);
      break;
    case 'p':
    case 'P':
      putchar('\n');
      PrintBST(T);
      break;
    }
    }
  while((cmd!='q') && (cmd!='Q'));
}

int main(void)
{
  Menu();
  return 0;
}

void InsertSort(SeqList *L)
{
  int i, j;
  int key;
  for(j=2; j<=L->length; j++)
    {
      key = L->data[j];
      i = j-1;
      while(i>=1 && key<L->data[i])
	{
	  L->data[i+1] = L->data[i];
	  i--;
	}
      L->data[i+1] = key;
    }
}

int SeqSearch(SeqList L, int key)
{
  int i;
  L.data[0] = key;
  i = L.length;
  while(L.data[i] != key)
    i--;
  return i;
}

int BinarySearch(SeqList L, int key)
{
  int Low, Mid, High;

  Low = 1;
  High = L.length;

  while(Low<=High)
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


/*
 *@T: Current Node
 *@Par: Current Node's Parent
 *@Pos: Successful ? Final Node : Former Node
 */
Status SearchBST(BiTree T, int key, BiTree Par, BiTree *Pos)
{
  if(!T)
    {
      *Pos = Par;
      return ERROR;
    }
  else if(T->data == key)
    {
      *Pos = T;
      return OK;
    }
  else if(key < T->data)
    SearchBST(T->left, key, T, Pos);
  else if(key > T->data)
    SearchBST(T->right, key, T, Pos);
}

Status InsertBST(BiTree *T, int key)
{
  BiTree Pos, tmp;
  if( !SearchBST(*T, key, NULL, &Pos) )
    {
      tmp = (BiTNode *)malloc(sizeof(BiTNode));
      tmp->data = key;
      tmp->left = tmp->right = NULL;

      if(!Pos)   //T为空树
	*T = tmp;
      else if(key < Pos->data)
	Pos->left = tmp;
      else
	Pos->right = tmp;

      return OK;
    }
  else
    return ERROR;
}

void CreateBST(BiTree *T, int *Num, int n)
{
  int i;
  for(i=0; i<n; i++)
    InsertBST(T, Num[i]);
}

Status Delete(BiTree *T)
{
  BiTree tmp, Prev;
  if((*T)->left == NULL)
    {
      tmp = *T;
      *T = (*T)->right;
      free(tmp);
    }
  else if((*T)->right == NULL)
    {
      tmp = *T;
      *T = (*T)->left;
      free(tmp);
    }
  else
    {
      tmp = *T;
      Prev = (*T)->left;
      while(Prev->right)
	{
	  tmp = Prev;
	  Prev = Prev->right;
	}
      (*T)->data = Prev->data;
      if(tmp!=(*T))
	  tmp->right = Prev->left;
      else
	(*T)->left = Prev->left;

      free(Prev);
    }
  return ERROR;
}

Status DeleteBST(BiTree *T, int key)
{
  if(!*T) //未找到
    return ERROR;
  else
    {
      if((*T)->data == key) //找到
	return Delete(T);
      else if(key < (*T)->data)
	return DeleteBST(&((*T)->left), key);
      else
	return DeleteBST(&((*T)->right), key);
    }
}

void PrintBST(BiTree T)
{
  if(T)
    {
      PrintBST(T->left);
      printf("%d ", T->data);
      PrintBST(T->right);
    }
}
	
