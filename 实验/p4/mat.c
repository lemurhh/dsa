#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100
typedef int datatype;

typedef struct {
  int i, j;
  datatype v;
}TriTupleNode;
typedef struct {
  TriTupleNode data[MAXSIZE];
  int rown, coln; //m: ���� n: ����
  int len;//����Ԫ�ĸ���
}TriTupleTable;

void Create(TriTupleTable *T)
{
  int i;
  int len;
  printf("The Num of Rows: ");
  scanf("%d", &(T->rown));
  printf("The Num of Columns: ");
  scanf("%d", &(T->coln));
  printf("The Num of Nonzero Elements: ");
  scanf("%d", &(T->len));

  len = T->len;
  
  putchar('\n');
  
  for(i=0; i<len; i++)
    {
      printf("Row: ");
      scanf("%d", &((T->data[i]).i));
      printf("Column: ");
      scanf("%d", &((T->data[i]).j));
      printf("Data: ");
      scanf("%d", &((T->data[i]).v));
    }
}

void Print(TriTupleTable *T)
{
  int i;
  int len;
  len=T->len;
  for(i=0; i<len; i++)
    printf("%d, %d, %d\n", T->data[i].i, T->data[i].j, T->data[i].v);
}

void Trans(TriTupleTable *OldT, TriTupleTable *NewT)
{
  int *num;
  int *pos;
  int i;
  int len;
  int NewPos;
  TriTupleNode OldNode;
  TriTupleNode *NewNode;
  
  num = (int *)malloc(sizeof(int) * (OldT->coln));
  pos = (int *)malloc(sizeof(int) * (OldT->coln));

  memset(num, 0, sizeof(int) * (OldT->coln));
  memset(pos, 0, sizeof(int) * (OldT->coln));

  len = OldT->len;
  
  NewT->rown = OldT->coln;
  NewT->coln = OldT->rown;
  NewT->len = OldT->len;

  for(i=0; i<len; i++) //��������OldT�еĽ�㣬����ԭ�����и��еķ���Ԫ������
    {
      num[(OldT->data[i]).j]++;
    }
  for(i=1; i<OldT->coln; i++) //����ԭ�����и����׷���Ԫ�����¾����е�λ��
    {
      pos[i] = pos[i-1] + num[i-1];
    }
  for(i=0; i<len; i++) //��������OldT�еĽ�㣬���临�Ƶ�NewT�еĺ���λ��NewPos
    {
      OldNode = OldT->data[i];
      
      NewPos = pos[OldNode.j]; //����λ��
      NewNode = &(NewT->data[NewPos]);
      
      NewNode->i = OldNode.j;
      NewNode->j = OldNode.i;
      NewNode->v = OldNode.v;
      
      pos[OldNode.j]++;
    }
  free(num);
  free(pos);
}

void Add(TriTupleTable *A, TriTupleTable *B, TriTupleTable *C) //T1+T2->T3
{
  int i, j, k;
  if( (A->rown!=B->rown) || (A->coln!=B->coln) )
    {
      printf("The Shapes of Matrixs Are DIFFERENT!\n");
      return ;
    }
  C->rown = A->rown;
  C->coln = A->coln;
  C->len = 0;
  
  if((A->len==0) && (B->len==0))
    return ;

  i=0;
  j=0;
  k=0;

  while(i<A->len && j<B->len)
    {
      if(A->data[i].i < B->data[j].i)
	C->data[k++] = A->data[i++];
      else if(B->data[j].i < A->data[i].i)
	C->data[k++] = B->data[j++];
      else if(A->data[i].j < B->data[j].j)
	C->data[k++] = A->data[i++];
      else if(B->data[j].j < A->data[i].j)
	C->data[k++] = B->data[j++];
      else if( (A->data[i].v + B->data[j].v) != 0)
	{
	  C->data[k].i =A->data[i].i;
	  C->data[k].j = A->data[i].j;
	  C->data[k].v = A->data[i].v + B->data[j].v;
	  k++;i++;j++;
	}
      else
	{
	  i++;j++;
	}
    }

  while(i < A->len)
      C->data[k++] = A->data[i++];
  while(j < B->len)
    C->data[k++] = B->data[j++];

  C->len = k;
}

int main(void)
{
  //�������������ӡ�ת��
  TriTupleTable T;
  TriTupleTable T1, T2, T3;
  TriTupleTable NewT;
  char cmd;
  const char *legal="cCaAtTpPqQ";
  do
    {
      putchar('\n');
      printf("c,C  ����\n");
      printf("a,A  ���\n");
      printf("t,T  ת��\n");
      printf("p,P  ���\n");
      printf("q,Q �˳�\n");
      putchar('\n');
      do
	{
	  printf("����������: ");
	  fflush(stdin);
	  scanf("%c", &cmd);
	}
      while( strchr(legal, cmd)==NULL );
      putchar('\n');
      switch(cmd)
	{
	case 'c':
	case 'C':
	  Create(&T);
	  printf("\nThe Matrix:\n");
	  Print(&T);
	  break;
	case 'a':
	case 'A':
	  printf("The First Matrix:\n");
	  Create(&T1);
	  printf("\nThe Second Matrix:\n");
	  Create(&T2);
	  Add(&T1, &T2, &T3);
	  printf("\nThe Result:\n");
	  Print(&T3);
	  break;
	case 't':
	case 'T':
	  Trans(&T, &NewT);
	  printf("The Result:\n");
	  Print(&NewT);
	  break;
	case 'p':
	case 'P':
	  printf("The Matrix:\n");
	  Print(&T);
	  break;
	}
    }
  while( (cmd!='q') && (cmd!='Q')  );
  return 0;
}
  
  
