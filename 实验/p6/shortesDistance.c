#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXVEX 100
#define INFINITY 65535

typedef char VertexType[20];
typedef int EdgeType;
typedef int Path[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];

typedef struct
{
  VertexType vexs[MAXVEX];
  EdgeType arc[MAXVEX][MAXVEX];
  int NumOfVertexes;
  int NumOfEdges;
}MGraph;

void Menu(MGraph *G, Path *P, ShortPathTable *D);
void CreateGraph(MGraph *G);
void Floyd(MGraph *G, Path *P, ShortPathTable *D);
void Search(MGraph G, Path P, ShortPathTable D, char *Source, char *Dest);

int main(void)
{
  MGraph G;
  Path P;
  ShortPathTable D;
  Menu(&G, &P, &D);
  return 0;
}

void Menu(MGraph *G, Path *P, ShortPathTable *D)
{
  char cmd;
  char Source[20];
  char Dest[20];
  const char *legal = "cCsSqQ";
  do
    {
      putchar('\n');
      printf("c,C  创建\n");
      printf("s,S  查询\n");
      printf("q,Q  退出");
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
	  Floyd(G, P, D);
	  break;
	case 's':
	case 'S':
	    printf("Input the Source: ");
	    scanf("%s", Source);
	    printf("Input the Dest: ");
	    scanf("%s", Dest);
	    Search(*G, *P, *D, Source, Dest);
	    break;
	}
    }
  while( (cmd!='q') && (cmd!='Q')  );
}

void CreateGraph(MGraph *G)
{
  int i, j, k, w;
  printf("Input the Num of Vertexes and Edges: ");
  scanf("%d%d", &(G->NumOfVertexes), &(G->NumOfEdges));
  for(i=0; i<G->NumOfVertexes; i++)
    {
      printf("Input the Data of the %dth Vertex: ", i+1);
      scanf("%s", G->vexs[i]);
    }
  for(i=0; i<G->NumOfVertexes; i++)
    for(j=0; j<G->NumOfVertexes; j++)
      if(i!=j) G->arc[i][j] = INFINITY;
      else G->arc[i][j] = 0;
  for(k=0; k<G->NumOfEdges; k++)
    {
      printf("Input the %dth Edge and its weight: ", k+1);
      scanf("%d%d%d", &i, &j, &w);
      G->arc[i][j] = G->arc[j][i] = w;
    }
}

void Floyd(MGraph *G, Path *P, ShortPathTable *D)
{
  int v, w, k;
  for(v=0; v<G->NumOfVertexes; v++)
    {
      for(w=0; w<G->NumOfVertexes; w++)
	{
	  (*D)[v][w] = G->arc[v][w];
	  (*P)[v][w] = w;
	}
    }
  for(k=0; k<G->NumOfVertexes; k++)
    {
      for(v=0; v<G->NumOfVertexes; v++)
	{
	  for(w=0; w<G->NumOfVertexes; w++)
	    {
	      if( (*D)[v][w] > (*D)[v][k]+(*D)[k][w]  )
		{
		  (*D)[v][w] = (*D)[v][k]+(*D)[k][w];
		  (*P)[v][w] = (*P)[v][k];
		}
	    }
	}
    }
}
void Search(MGraph G, Path P, ShortPathTable D, char *Source, char *Dest)
{
  int v, w, k;
  for(v=0; v<G.NumOfVertexes; v++)
    if(strcmp(Source, G.vexs[v]) == 0) break;
  for(w=0; w<G.NumOfVertexes; w++)
    if(strcmp(Dest, G.vexs[w]) == 0) break;
  if(v==G.NumOfVertexes+1 || w==G.NumOfVertexes+1)
    {
      printf("The Source or Dest Doesn't Exist\n");
      return ;
    }
  printf("%s-%s length: %d\n", G.vexs[v], G.vexs[w], D[v][w]);
  k = P[v][w];
  printf("Path: %s", G.vexs[v]);
  while(k!=w)
    {
      printf("->%s", G.vexs[k]);
      k = P[k][w];
    }
  printf("->%s\n", G.vexs[w]);
  putchar('\n');
}
