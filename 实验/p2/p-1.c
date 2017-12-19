#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 100

#define OK 1
#define ERROR -1

#define PHY 0 //下标
#define LOG 1 //位序

#define NOTFOUND -1//未找到

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
  const char *legal="iIfFdDmMpPrRqQ";//合法命令

  unsigned int i;
  char name[20];

  L = (DirList *)malloc(sizeof(DirList));
  Create(L);
  Print(*L);
  
  do
    {
      putchar('\n');
      printf("i,I  插入\n");
      printf("f,F  查找\n");
      printf("d,D  删除\n");
      printf("m,M  修改\n");
      printf("p,P  输出\n");
      printf("r,R  逆置\n");
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
	case 'i':
	case 'I':
	  printf("位置: ");
	  fflush(stdin);
	  scanf("%d", &i);
	  Insert(L, i);
	  Print(*L);
	  break;
	case 'f':
	case 'F':
	  printf("要查找联系人的姓名: ");
	  fflush(stdin);
	  scanf("%s", name);
	  Find(*L, name);
	  break;
	case 'd':
	case 'D':
	  printf("要删除联系人的姓名: ");
	  fflush(stdin);
	  scanf("%s", name);
	  Delete(L, name);
	  Print(*L);
	  break;
	case 'm':
	case 'M':
	  printf("要修改联系人的姓名: ");
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

//功能：字符串是否由纯数字组成
//返回值：是->TRUE 否->FALSE
int IsDigits(char *s) 
{
  int i;
  int n = strlen(s);
  for(i=0; i<n; i++)
    if(!isdigit(s[i])) return FALSE;
  return TRUE;
}
//功能：打印所有联系人
void Print(DirList L)
{
  int i;
  int n = L.length;
  putchar('\n');
  for(i=0; i<n; i++)
      printf("id:%d  姓名:%s  电话:%s\n", (L.directory[i]).id, (L.directory[i]).name, (L.directory[i]).numb);
}
//功能：创建电话簿
void Create(DirList *L)
{
  int i;
  printf("请输入联系人个数：");
  scanf("%d", &(L->length));
  for(i=0; i<L->length; i++)
    {
      L->directory[i].id = i+1;
      printf("\n联系人%d:\n", i+1);
      printf("\t姓名: ");
      fflush(stdin);
      scanf("%s", (L->directory[i]).name);
      do
	{
	  printf("\t电话: ");
	  fflush(stdin);
	  scanf("%s", (L->directory[i]).numb);
	}
      while(IsDigits( (L->directory[i]).numb ) == FALSE); //检查电话号码格式
    }
}
//功能：根据姓名查找联系人的位置
//返回值：flag==PHY->下标位置   falg==LOG->位序位置
int PrivateFind(DirList L, char *name, int flag) //flag==PHY返回下标，flag==LOG返回位序
{
  int i;
  int n = L.length;
  for(i=0; i<n; i++)
    {
      if(!strcmp((L.directory[i]).name, name)) //如果姓名匹配
	{
	  if(flag==PHY) return i; //返回下标
	  else return i+1;//返回位序
	}
    }
  return NOTFOUND;
}
//功能：根据姓名查找并显示联系人
Status Find(DirList L, char *name)
{
  int i;
  i = PrivateFind(L, name, PHY);//i为下标
  if(i == NOTFOUND)
    {
      printf("未找到该联系人\n");
      return ERROR;
    }
  printf("id: %d  姓名: %s  电话: %s\n", (L.directory[i]).id, (L.directory[i]).name, (L.directory[i]).numb);
  return OK;
}
//功能：在指定位序位置插入联系人
Status Insert(DirList *L, int i)
{
  int k;
  contact tmp;
  if(L->length == MAXSIZE)
    {
      printf("电话簿已满\n");
      return ERROR;
    }
  if(i<1 || i>L->length+1)
    {
      printf("位置输入错误\n");
      return ERROR;
    }
  if(i<=L->length) //若插入数据位置不在表尾
    {
      for(k = L->length; k >= i-1; k--)
	{
	  L->directory[k] = L->directory[k-1];
	  (L->directory[k]).id++;
	}
    }
  
  tmp.id = i;
  printf("姓名: ");
  fflush(stdin);
  scanf("%s", tmp.name);
  do
    {
      printf("电话: ");
      fflush(stdin);
      scanf("%s", tmp.numb);
    }
  while(IsDigits(tmp.numb) == FALSE);//检查电话号码格式
  
  L->directory[i-1] = tmp;
  L->length++;
  return OK;
}
//功能：根据姓名删除联系人
Status Delete(DirList *L, char *name)
{
  int k;
  int i;
  char sure;
  if(L->length == 0)
    {
      printf("空电话簿\n");
      return ERROR;
    }
  i = PrivateFind(*L, name, LOG);//i为位序
  if(i == NOTFOUND)
    {
      printf("未找到该联系人\n");
      return ERROR;
    }
  do
  {
    printf("确认删除?[y/Y][n/N]: ");
    fflush(stdin);
    scanf("%c",&sure);
  }
 while(sure!='y' && sure != 'Y' && sure != 'n' && sure != 'N');
  if(sure=='y' || sure=='Y')
    {
      if(i<L->length) //若不是删除最后一个元素
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
//功能：根据姓名修改联系人
Status Modify(DirList *L, char *name)
{
  int i;
  i = PrivateFind(*L, name, PHY);//i为下标
  if(i == NOTFOUND)
    {
      printf("未找到该联系人\n");
      return ERROR;
    }
  printf("姓名: ");
  fflush(stdin);
  scanf("%s", (L->directory[i]).name);
  do
    {
      printf("电话: ");
      fflush(stdin);
      scanf("%s", (L->directory[i]).numb);
    }
  while(IsDigits((L->directory[i]).numb)==FALSE);
  return OK;
}
//功能：逆置电话簿
void Reverse(DirList *L)
{
  int left, right;
  contact cTmp;
  unsigned int iTmp;
  left = 0;
  right = L->length-1;
  while(left<right)
    {
      //交换id
      iTmp = (L->directory[left]).id;
      (L->directory[left]).id = (L->directory[right]).id;
      (L->directory[right]).id = iTmp;
      //交换其余部分
      cTmp = L->directory[left];
      L->directory[left] = L->directory[right];
      L->directory[right] = cTmp;
      left++;
      right--;
    }
}


