#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HfTree{
  int weight;
  int parent;
  int left, right;
}HfNode;
typedef HfNode HfTree;

void Create(char ***Code, const int *SetOfWeight, const int NumOfLeafs);

int main(void)
{
  char **Code;
  int *SetOfWeight;
  int NumOfLeafs;
  int i;
  
  printf("Input the Size of the Weight Set:");
  scanf("%d", &NumOfLeafs);
  SetOfWeight = (int *)malloc((NumOfLeafs+1) * sizeof(int));
  SetOfWeight[0] = 100; 
  
  printf("Input the Weight Set:");
  for(i=1; i<=NumOfLeafs; i++)
    scanf("%d", &SetOfWeight[i]);
  
  Create(&Code, SetOfWeight, NumOfLeafs);
  
  for(i=1; i<=NumOfLeafs; i++)
    printf("\n%d:%s", SetOfWeight[i], Code[i]);
  
  free(Code);
  return 0;
}

void Create(char ***Code, const int *SetOfWeight, const int NumOfLeafs)
{
  int Start;
  const int NumOfNodes=2*NumOfLeafs-1;
  int IndexOfLeaf, IndexOfBranch, IndexOfFormer;
  int Index, Parent;
  int MinIndex1, MinIndex2;
  HfTree *T;
  char *tmp;

  T = (HfTree *)malloc( (NumOfNodes+1) * sizeof(HfNode)  );
  *Code = (char **)malloc( (NumOfLeafs+1) * sizeof(char *) );
  tmp = (char *)malloc( (NumOfLeafs) * sizeof(char) );
  tmp[NumOfLeafs-1] = '\0';

  for(IndexOfLeaf=0; IndexOfLeaf<=NumOfLeafs; IndexOfLeaf++)
    T[IndexOfLeaf] = (HfNode){SetOfWeight[IndexOfLeaf], 0, 0, 0};
  for(IndexOfBranch=NumOfLeafs+1; IndexOfBranch<=NumOfNodes; IndexOfBranch++)
    T[IndexOfBranch] = (HfNode){0, 0, 0, 0};
  
  for(IndexOfBranch=NumOfLeafs+1; IndexOfBranch<=NumOfNodes; IndexOfBranch++)
    {
      MinIndex1 = 0;
      MinIndex2 = 0;
      for(IndexOfFormer=1; IndexOfFormer<=IndexOfBranch-1; IndexOfFormer++)
	if( (T[IndexOfFormer].weight < T[MinIndex1].weight) && (T[IndexOfFormer].parent==0) ) MinIndex1 = IndexOfFormer;
      for(IndexOfFormer=1; IndexOfFormer<=IndexOfBranch-1; IndexOfFormer++)
	{
	  if(IndexOfFormer==MinIndex1) continue;
	  if( (T[IndexOfFormer].weight < T[MinIndex2].weight) && (T[IndexOfFormer].parent==0) ) MinIndex2 = IndexOfFormer;
	}
      //寻找未使用叶子结点中权重最小的两个
      
      T[MinIndex1].parent = T[MinIndex2].parent = IndexOfBranch;
      T[IndexOfBranch].left = MinIndex1;
      T[IndexOfBranch].right = MinIndex2;
      T[IndexOfBranch].weight = T[MinIndex1].weight + T[MinIndex2].weight;
    }
  for(IndexOfLeaf=1; IndexOfLeaf<=NumOfLeafs; IndexOfLeaf++)
    {
      Start = NumOfLeafs-1;
      for(Index=IndexOfLeaf, Parent=T[IndexOfLeaf].parent; Parent!=0; Index=Parent, Parent=T[Parent].parent)
	{
	  if(T[Parent].left == Index) tmp[--Start]='0';
	  else tmp[--Start]='1';
	}
      (*Code)[IndexOfLeaf] = (char *)malloc((NumOfLeafs-Start) * sizeof(char));
      strcpy((*Code)[IndexOfLeaf], &(tmp[Start]));
    }
  free(tmp);
  free(T);
}
	    
      
