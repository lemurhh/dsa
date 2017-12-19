#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define MAXVEX 100
#define MAXSIZE 100

int visited[MAXSIZE];

typedef int datatype;
typedef int Status;
typedef char VertexType;
typedef int EdgeType;

typedef struct SQueue{
  datatype data[MAXSIZE];
  int front;
  int rear;
}SQueue;

typedef struct EdgeNode {
  int adjvex;
  struct EdgeNode *next;
}EdgeNode;

typedef struct VertexNode {
  VertexType data;
  struct EdgeNode *firstedge;
}VertexNode;

typedef struct
{
  VertexNode AdjList[MAXVEX];
  int NumOfVertexes;
  int NumOfEdges;
}GraphAdjList;

void Menu(GraphAdjList *G);
void InitQueue(SQueue *Q);
int IsEmpty(SQueue *Q);
Status EnQueue(SQueue *Q, datatype x);
Status DeQueue(SQueue *Q, datatype *x);
void CreateGraph(GraphAdjList *G);
void DFS(GraphAdjList *G, int i);
void DFSTraverse(GraphAdjList *G);
void BFSTraverse(GraphAdjList *G);
Status DeleteEdge(GraphAdjList *G, int i, int j);
Status InsertEdge(GraphAdjList *G, int i, int j);

int main(void)
{
  GraphAdjList G;
  Menu(&G);
  return 0;
}

void Menu(GraphAdjList *G)
{
  char cmd;
  const char *legal="cCiIrRdDbBqQ";
  int i, j;
  do
    {
      putchar('\n');
      printf("c,C  创建\n");
      printf("i,I  插入边\n");
      printf("r,R  删除边\n");
      printf("d,D  深度优先遍历\n");
      printf("b,B  广度优先遍历\n");
      printf("q,Q  退出\n");
      putchar('\n');
      do
	{
	  printf("cmd: ");
	  fflush(stdin);
	  scanf("%c", &cmd);
	}
      while( strchr(legal, cmd)==NULL  );
      putchar('\n');
      switch(cmd)
	{
	case 'c':
	case 'C':
	  CreateGraph(G);
	  break;
	case 'i':
	case 'I':
	  printf("Input the Edge: ");
	  scanf("%d%d", &i, &j);
	  InsertEdge(G, i, j);
	  printf("DFS: ");
	  DFSTraverse(G);
	  printf("BFS: ");
	  BFSTraverse(G);
	  break;
	case 'r':
	case 'R':
	  printf("Input the Deleted Edge: ");
	  scanf("%d%d", &i, &j);
	  DeleteEdge(G, i, j);
	  printf("DFS: ");
	  DFSTraverse(G);
	  printf("BFS: ");
	  BFSTraverse(G);
	  break;
	case 'd':
	case 'D':
	  DFSTraverse(G);
	  break;
	case 'b':
	case 'B':
	  BFSTraverse(G);
	  break;
	}
    }
  while( (cmd!='q') && (cmd!='Q') );
}

void InitQueue(SQueue *Q)
{
  Q->front = 0;
  Q->rear = 0;
}

int IsEmpty(SQueue *Q)
{
  return Q->rear==Q->front;
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

void CreateGraph(GraphAdjList *G)
{
  int i, j, k;
  EdgeNode *e;

  printf("Input the Num of Vertexes and Edges: ");
  scanf("%d%d", &(G->NumOfVertexes), &(G->NumOfEdges));
  for(i=0; i<G->NumOfVertexes; i++)
    {
      printf("Input the Data of the %dth Vertex: ", i+1);
      fflush(stdin);
      scanf("%c", &(G->AdjList[i].data));
      G->AdjList[i].firstedge = NULL;
    }
  for(k=0; k<G->NumOfEdges; k++)
    {
      printf("Input the %dth Edge: ", k+1);
      scanf("%d%d", &i, &j);

      e = (EdgeNode *)malloc(sizeof(EdgeNode));
      e->adjvex = j;
      e->next = G->AdjList[i].firstedge;
      G->AdjList[i].firstedge = e;

      e = (EdgeNode *)malloc(sizeof(EdgeNode));
      e->adjvex = i;
      e->next = G->AdjList[j].firstedge;
      G->AdjList[j].firstedge = e;
    }
}

void DFS(GraphAdjList *G, int i)
{
  EdgeNode *p;
  visited[i] = TRUE;
  printf("%c ", G->AdjList[i].data);
  p = G->AdjList[i].firstedge;
  while(p)
    {
      if(!visited[p->adjvex])
	DFS(G, p->adjvex);
      p = p->next;
    }
}
void DFSTraverse(GraphAdjList *G)
{
  int i;
  for(i=0; i<G->NumOfVertexes; i++)
    visited[i] = FALSE;
  for(i=0; i<G->NumOfVertexes; i++)
    if(!visited[i]) DFS(G, i);
  putchar('\n');
}

void BFSTraverse(GraphAdjList *G)
{
  int i;
  EdgeNode *p;
  SQueue Q;
  for(i=0; i<G->NumOfVertexes; i++)
    visited[i] = FALSE;
  InitQueue(&Q);
  for(i=0; i<G->NumOfVertexes; i++)
    {
      if(!visited[i])
	{
	  visited[i] = TRUE;
	  printf("%c ", G->AdjList[i].data);
	  EnQueue(&Q, i);
	  while(!IsEmpty(&Q))
	    {
	      DeQueue(&Q, &i);
	      p = G->AdjList[i].firstedge;
	      while(p)
		{
		  if(!visited[p->adjvex])
		    {
		      visited[p->adjvex] = TRUE;
		      printf("%c ", G->AdjList[p->adjvex].data);
		      EnQueue(&Q, p->adjvex);
		    }
		  p = p->next;
		}
	    }
	}
    }
  putchar('\n');
}
	      
Status DeleteEdge(GraphAdjList *G, int i, int j)
{
  EdgeNode *p=NULL;
  EdgeNode *tmp=NULL;
  
  if(i>=G->NumOfVertexes || j>=G->NumOfVertexes)
    {
      printf("At Least One Vertex Doesn't Exist!");
      return ERROR;
    }
  
  p = G->AdjList[i].firstedge;
  if(p->adjvex==j)
    {
      G->AdjList[i].firstedge = p->next;
      free(p);
      return OK;
    }
  while(p && (p->next) && ((p->next->adjvex)!=j))
    p = p->next;
  if(p==NULL || p->next==NULL)
    {
      printf("The Edge Doesn't Exist!\n");
      return ERROR;
    }
  tmp = p->next;
  p->next = tmp->next;
  free(tmp);

  p = G->AdjList[j].firstedge;
  if(p->adjvex==i)
    {
      G->AdjList[j].firstedge = p->next;
      free(p);
      return OK;
    }
  while(p && (p->next) && ((p->next->adjvex)!=i))
    p = p->next;
  if(p==NULL || p->next==NULL)
    {
      printf("The Edge Doesn't Exist!\n");
      return ERROR;
    }
  tmp = p->next;
  p->next = tmp->next;
  free(tmp);
  
  return OK;
}

Status InsertEdge(GraphAdjList *G, int i, int j)
{
  EdgeNode *tmp=NULL;
  if(i>=G->NumOfVertexes || j>=G->NumOfVertexes)
    {
      printf("At Least One Vertex Doesn't Exist!");
      return ERROR;
    }

  tmp = (EdgeNode *)malloc(sizeof(EdgeNode));
  tmp->adjvex = j;
  tmp->next = G->AdjList[i].firstedge;
  G->AdjList[i].firstedge = tmp;

  tmp = (EdgeNode *)malloc(sizeof(EdgeNode));
  tmp->adjvex = i;
  tmp->next = G->AdjList[j].firstedge;
  G->AdjList[j].firstedge = tmp;

  return OK;
}
      

