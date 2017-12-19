#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(a,b,tmp) {tmp=a; a=b; b=tmp;}

void InsertSort(int *num, int n)
{
  int i, j;
  int key;
  for(j=1; j<n; j++)
    {
      key = num[j];
      i = j-1;
      while(i>=0 && key<num[i])
	{
	  num[i+1] =num[i];
	  i--;
	}
      num[i+1] = key;
    }
}
void SelectSort(int *num, int n)
{
  int i, j;
  int MinIndex;
  int tmp;
  for(j=0; j<n; j++)
    {
      MinIndex = j;
      for(i=j+1; i<n; i++)
	  if(num[i]<num[MinIndex]) MinIndex = i;
      if(MinIndex != j)
	{
	  tmp = num[MinIndex];
	  num[MinIndex] = num[j];
	  num[j] = tmp;
	}
    }
}
void BubbleSort(int *num, int n)
{
  int i, j;
  int IsChange;
  int tmp;
  for(i=0; i<n; i++)
    {
      IsChange = 0;
      for(j=0; j<n-i; j++)
	{
	  if(num[j]>num[j+1])
	    {
	      tmp = num[j];
	      num[j] = num[j+1];
	      num[j+1] = tmp;
	      IsChange = 1;
	    }
	}
      if(IsChange==0) break;
    }
}
void MergeArray(int *num, int first, int mid, int last, int *tmp)
{
  int i=first, j=mid+1;
  int m=mid, n=last;
  int k=0;
  while(i<=m && j<=n)
    {
      if(num[i]<num[j]) tmp[k++]=num[i++];
      else tmp[k++]=num[j++];
    }
  while(i<=m)
    tmp[k++]=num[i++];
  while(j<=n)
    tmp[k++]=num[j++];
  for(i=0; i<k; i++)
    num[first+i] = tmp[i];
}
void _MergeSort(int *num, int first, int last, int *tmp)
{
  int mid;
  if(first<last)
    {
      mid = (first+last) / 2;
      _MergeSort(num, first, mid, tmp);
      _MergeSort(num, mid+1, last, tmp);
      MergeArray(num, first, mid, last, tmp);
    }
}
void MergeSort(int *num, int n)
{
  int tmp[n];
  _MergeSort(num, 0, n-1, tmp);
}
int Partition(int *num, int p, int r)
{
  int random;
  int x;
  int i = p-1;
  int j;
  int tmp;
  
  srand((unsigned)time(NULL));
  random = p+ ((rand()) % (p-r));
  
  swap(num[r], num[random], tmp);
  x = num[r];
  
  for(j=p; j<=r-1; j++)
    {
      if(num[j] <= x)
	{
	  i++;
	  swap(num[i], num[j], tmp);
	}
    }

  swap(num[i+1], num[r], tmp);
  
  return i+1;
}
void _QuickSort(int *num, int p, int r)
{
  int q;
  if(p<r)
    {
      q = Partition(num, p, r);
      _QuickSort(num, p, q-1);
      _QuickSort(num, q+1, r);
    }
}
void QuickSort(int *num, int n)
{
  _QuickSort(num, 0, n-1);
}
  
void Sort(void(*fun)(int *, int), int *num, int n)
{
  fun(num, n);
}
int main(void)
{
  int i;
  int num[7]={0,1,-2,4,3,-100,120};
  Sort(QuickSort, num, 7);
  for(i=0; i<7; i++)
    printf("%d ", num[i]);
  putchar('\n');
}
