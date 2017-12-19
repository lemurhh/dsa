#include <stdio.h>
#include <string.h>

void PopSeq( char *str, int index, int size) /*求所有出栈序列*/
{
  int i, u, v, w,flag; //v指要判断序列，w指入栈的序列
  char temp;

  if( index==size)
    {
      flag=1;
      for( u=0; u<=size - 2; u++)
	for( v=u+1; v<=size - 1; v++)
	  for(w=v+1; w<=size; w++)
	    if( ( str[v]<str[w])&&( str[w]<str[u]) ) flag=0;
      if(flag) /*判断序列是否为出栈序列, 若是则输出序列*/
	  printf( "%s\n",  str) ;
    }
  else
    for( i=index; i<=size; i++)
      {
	temp=str[index];
	str[index]=str[i];
	str[i]=temp;
	PopSeq( str, index+1, size) ;
	temp=str[index];
	str[index]=str[i];
	str[i]=temp;
      }
}

int main( )
{
  char str[10];
  printf( "请输入入栈序列( 如:123) ") ;
  scanf( "%s", str) ;
  printf( "所有出栈序列为: \n") ;
  PopSeq( str, 0, strlen( str) - 1) ;
  return 0;
}
