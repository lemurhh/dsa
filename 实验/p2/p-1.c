#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 100

#define OK 1
#define ERROR -1

#define PHY 0 //�±�
#define LOG 1 //λ��

#define NOTFOUND -1//δ�ҵ�

#define TRUE 1
#define FALSE -1

typedef struct {
  unsigned int id;
  char name[20];
  char numb[12];
} contact;

typedef struct {
  contact directory[MAXSIZE];
  int length;
} DirList;

typedef int Status;

int IsDigits(char *s);
void Print(DirList L);
void Create(DirList *L);
int PrivateFind(DirList L, char *name, int flag);
Status Find(DirList L, char *name);
Status Insert(DirList *L, int i);
Status Delete(DirList *L, char *name);
Status Modify(DirList *L, char *name);
void Reverse(DirList *L);

int main(void)
{
  DirList *L;
  char cmd;
  const char *legal="iIfFdDmMpPrRqQ";//�Ϸ�����

  unsigned int i;
  char name[20];

  L = (DirList *)malloc(sizeof(DirList));
  Create(L);
  Print(*L);
  
  do
    {
      putchar('\n');
      printf("i,I  ����\n");
      printf("f,F  ����\n");
      printf("d,D  ɾ��\n");
      printf("m,M  �޸�\n");
      printf("p,P  ���\n");
      printf("r,R  ����\n");
      printf("q,Q  �˳�\n");
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
	case 'i':
	case 'I':
	  printf("λ��: ");
	  fflush(stdin);
	  scanf("%d", &i);
	  Insert(L, i);
	  Print(*L);
	  break;
	case 'f':
	case 'F':
	  printf("Ҫ������ϵ�˵�����: ");
	  fflush(stdin);
	  scanf("%s", name);
	  Find(*L, name);
	  break;
	case 'd':
	case 'D':
	  printf("Ҫɾ����ϵ�˵�����: ");
	  fflush(stdin);
	  scanf("%s", name);
	  Delete(L, name);
	  Print(*L);
	  break;
	case 'm':
	case 'M':
	  printf("Ҫ�޸���ϵ�˵�����: ");
	  fflush(stdin);
	  scanf("%s", name);
	  Modify(L, name);
	  Print(*L);
	  break;
	case 'p':
	case 'P':
	  Print(*L);
	  break;
	case 'r':
	case 'R':
	  Reverse(L);
	  Print(*L);
	  break;
	default:
	  break;
	}
    }
  while((cmd!='q') && (cmd!='Q'));
  return 0;
}

//���ܣ��ַ����Ƿ��ɴ��������
//����ֵ����->TRUE ��->FALSE
int IsDigits(char *s) 
{
  int i;
  int n = strlen(s);
  for(i=0; i<n; i++)
    if(!isdigit(s[i])) return FALSE;
  return TRUE;
}
//���ܣ���ӡ������ϵ��
void Print(DirList L)
{
  int i;
  int n = L.length;
  putchar('\n');
  for(i=0; i<n; i++)
      printf("id:%d  ����:%s  �绰:%s\n", (L.directory[i]).id, (L.directory[i]).name, (L.directory[i]).numb);
}
//���ܣ������绰��
void Create(DirList *L)
{
  int i;
  printf("��������ϵ�˸�����");
  scanf("%d", &(L->length));
  for(i=0; i<L->length; i++)
    {
      L->directory[i].id = i+1;
      printf("\n��ϵ��%d:\n", i+1);
      printf("\t����: ");
      fflush(stdin);
      scanf("%s", (L->directory[i]).name);
      do
	{
	  printf("\t�绰: ");
	  fflush(stdin);
	  scanf("%s", (L->directory[i]).numb);
	}
      while(IsDigits( (L->directory[i]).numb ) == FALSE); //���绰�����ʽ
    }
}
//���ܣ���������������ϵ�˵�λ��
//����ֵ��flag==PHY->�±�λ��   falg==LOG->λ��λ��
int PrivateFind(DirList L, char *name, int flag) //flag==PHY�����±꣬flag==LOG����λ��
{
  int i;
  int n = L.length;
  for(i=0; i<n; i++)
    {
      if(!strcmp((L.directory[i]).name, name)) //�������ƥ��
	{
	  if(flag==PHY) return i; //�����±�
	  else return i+1;//����λ��
	}
    }
  return NOTFOUND;
}
//���ܣ������������Ҳ���ʾ��ϵ��
Status Find(DirList L, char *name)
{
  int i;
  i = PrivateFind(L, name, PHY);//iΪ�±�
  if(i == NOTFOUND)
    {
      printf("δ�ҵ�����ϵ��\n");
      return ERROR;
    }
  printf("id: %d  ����: %s  �绰: %s\n", (L.directory[i]).id, (L.directory[i]).name, (L.directory[i]).numb);
  return OK;
}
//���ܣ���ָ��λ��λ�ò�����ϵ��
Status Insert(DirList *L, int i)
{
  int k;
  contact tmp;
  if(L->length == MAXSIZE)
    {
      printf("�绰������\n");
      return ERROR;
    }
  if(i<1 || i>L->length+1)
    {
      printf("λ���������\n");
      return ERROR;
    }
  if(i<=L->length) //����������λ�ò��ڱ�β
    {
      for(k = L->length; k >= i-1; k--)
	{
	  L->directory[k] = L->directory[k-1];
	  (L->directory[k]).id++;
	}
    }
  
  tmp.id = i;
  printf("����: ");
  fflush(stdin);
  scanf("%s", tmp.name);
  do
    {
      printf("�绰: ");
      fflush(stdin);
      scanf("%s", tmp.numb);
    }
  while(IsDigits(tmp.numb) == FALSE);//���绰�����ʽ
  
  L->directory[i-1] = tmp;
  L->length++;
  return OK;
}
//���ܣ���������ɾ����ϵ��
Status Delete(DirList *L, char *name)
{
  int k;
  int i;
  char sure;
  if(L->length == 0)
    {
      printf("�յ绰��\n");
      return ERROR;
    }
  i = PrivateFind(*L, name, LOG);//iΪλ��
  if(i == NOTFOUND)
    {
      printf("δ�ҵ�����ϵ��\n");
      return ERROR;
    }
  do
  {
    printf("ȷ��ɾ��?[y/Y][n/N]: ");
    fflush(stdin);
    scanf("%c",&sure);
  }
 while(sure!='y' && sure != 'Y' && sure != 'n' && sure != 'N');
  if(sure=='y' || sure=='Y')
    {
      if(i<L->length) //������ɾ�����һ��Ԫ��
	{
	  for(k=i; k<=L->length-1; k++)
	    {
	      L->directory[k-1] = L->directory[k];
	      (L->directory[k-1]).id--;
	    }
	}
      L->length--;
      return OK;
    }
  return OK;
}
//���ܣ����������޸���ϵ��
Status Modify(DirList *L, char *name)
{
  int i;
  i = PrivateFind(*L, name, PHY);//iΪ�±�
  if(i == NOTFOUND)
    {
      printf("δ�ҵ�����ϵ��\n");
      return ERROR;
    }
  printf("����: ");
  fflush(stdin);
  scanf("%s", (L->directory[i]).name);
  do
    {
      printf("�绰: ");
      fflush(stdin);
      scanf("%s", (L->directory[i]).numb);
    }
  while(IsDigits((L->directory[i]).numb)==FALSE);
  return OK;
}
//���ܣ����õ绰��
void Reverse(DirList *L)
{
  int left, right;
  contact cTmp;
  unsigned int iTmp;
  left = 0;
  right = L->length-1;
  while(left<right)
    {
      //����id
      iTmp = (L->directory[left]).id;
      (L->directory[left]).id = (L->directory[right]).id;
      (L->directory[right]).id = iTmp;
      //�������ಿ��
      cTmp = L->directory[left];
      L->directory[left] = L->directory[right];
      L->directory[right] = cTmp;
      left++;
      right--;
    }
}


