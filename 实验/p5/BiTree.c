#include <stdio.h>
#include <stdlib.h>

typedef char datatype;
typedef struct BiTree{
  datatype data;
  struct BiTree *left;
  struct BiTree *right;
}BiTree;

void Create(BiTree **T);
void PreOrderTraverse(BiTree *T);
void InOrderTraverse(BiTree *T);
void PostOrderTraverse(BiTree *T);
int GetDeepth(BiTree *T);
void PrintLevel(BiTree *T, int level);
void LevelTraverse(BiTree *T);
int GetNumOfLeafs(BiTree *T);
int GetNumOfNodes(BiTree *T);

int main(void)
{
  BiTree *T;
  printf("前序创建二叉树: ");
  Create(&T);
  printf("\n前序: ");
  PreOrderTraverse(T);
  putchar('\n');
  printf("中序: ");
  InOrderTraverse(T);
  putchar('\n');
  printf("后序: ");
  PostOrderTraverse(T);
  putchar('\n');
  printf("层序: ");
  LevelTraverse(T);
  putchar('\n');
  printf("结点数: %d\n", GetNumOfNodes(T));
  printf("叶子数: %d\n", GetNumOfLeafs(T));
  return 0;
}

void Create(BiTree **T)
{
  datatype tmp;
  scanf("%c", &tmp);
  if(tmp=='#')
    *T = NULL;
  else
    {
      *T = (BiTree *)malloc(sizeof(BiTree));
      (*T)->data = tmp;
      (*T)->left=NULL;
      (*T)->right=NULL;
      Create(&(*T)->left);
      Create(&(*T)->right);
    }
}

void PreOrderTraverse(BiTree *T)
{
  if(T==NULL)
    return ;
  else
    {
      printf("%c ", T->data);
      PreOrderTraverse(T->left);
      PreOrderTraverse(T->right);
    }
}

void InOrderTraverse(BiTree *T)
{
  if(T==NULL)
    return ;
  else
    {
      InOrderTraverse(T->left);
      printf("%c ", T->data);
      InOrderTraverse(T->right);
    }
}

void PostOrderTraverse(BiTree *T)
{
  if(T==NULL)
    return ;
  else
    {
      PostOrderTraverse(T->left);
      PostOrderTraverse(T->right);
      printf("%c ", T->data);
    }
}

int GetDeepth(BiTree *T)
{
  int LeftDeepth, RightDeepth;
  if(T==NULL)
    return 0;
  else
    {
      LeftDeepth = GetDeepth(T->left);
      RightDeepth = GetDeepth(T->right);
      return (LeftDeepth>RightDeepth) ? (LeftDeepth+1) : (RightDeepth+1);
    }
}

void PrintLevel(BiTree *T, int level)
{
  if(T==NULL || level<1)
    return ;
  if(level==1)
    {
      printf("%c ", T->data);
      return ;
    }
  PrintLevel(T->left, level-1);
  PrintLevel(T->right, level-1);
}

void LevelTraverse(BiTree *T)
{
  int deepth = GetDeepth(T);
  int level;
  for(level=1; level<=deepth; level++)
      PrintLevel(T, level);
}

int GetNumOfLeafs(BiTree *T)
{
  static int count=0;
  if(T==NULL)
    ;
  else
    {
      GetNumOfLeafs(T->left);
      GetNumOfLeafs(T->right);
      if(T->left==NULL && T->right==NULL)
	count++;
    }
  return count;
}

int GetNumOfNodes(BiTree *T)
{
  static int count=0;
  if(T==NULL)
    ;
  else
    {
      count++;
      GetNumOfNodes(T->left);
      GetNumOfNodes(T->right);
    }
  return count;
}
  
