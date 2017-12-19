#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 30

typedef struct BiTreeNode {
  char data;
  struct BiTreeNode *left;
  struct BiTreeNode *right;
}BiTreeNode, BiTree;

typedef struct {
  BiTreeNode *data[MAXSIZE];
  int front;
  int rear;
}Queue;

void CreateTree(BiTree **T)
{
  char ch;
  scanf("%c", &ch);
  if(ch == '#')
    (*T) = NULL;
  else
    {
      (*T) = (BiTree *)malloc(sizeof(BiTree));
      (*T)->data = ch;
      CreateTree(&((*T)->left));
      CreateTree(&((*T)->right));
    }
}
int GetLength(Queue *Q)
{
  return (Q->rear+MAXSIZE-Q->front) % MAXSIZE;
}
void EnQueue(Queue *Q, BiTreeNode *x)
{
  if((Q->rear+1)%MAXSIZE == Q->front)
    return ;
  Q->data[Q->rear] = x;
  Q->rear = (Q->rear+1) % MAXSIZE;
  return ;
}
void DeQueue(Queue *Q, BiTreeNode **x)
{
  if(Q->front == Q->rear)
    return ;
  *x = Q->data[Q->front];
  Q->front = (Q->front+1) % MAXSIZE;
  return ;
}
int IsEmpty(Queue *Q)
{
  return Q->front == Q->rear;
}
void LevelTraverse(BiTree *T)
{
  Queue Q;
  BiTree *tmp=NULL;
  Q.front = Q.rear = 0;
  EnQueue(&Q, T);
  while(!IsEmpty(&Q))
    {
      DeQueue(&Q, &tmp);
      printf("%c ", tmp->data);
      if(tmp->left)
	EnQueue(&Q, tmp->left);
      if(tmp->right)
	EnQueue(&Q, tmp->right);
    }
}


int main(void)
{
  BiTree *T;
  CreateTree(&T);
  LevelTraverse(T);
  return 0;
}
