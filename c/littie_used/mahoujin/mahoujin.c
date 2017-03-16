#include<stdio.h>
#include<stdlib.h>
#define NDEBUG
#include "mahoujin.h"


void SwapStr(int str[],int n,int str_tail){
  int i,temp,k=str_tail-n;
  temp=str[k];
  for(i=k;i<str_tail;i++)
    str[i]=str[i+1];
  str[str_tail]=temp;
  return;
 }

void Sort(int str[],int n,int str_tail){
  int i,flag;
  if(n>1)
      for(i=0;i<n+1;i++){
      Sort(str,n-1,str_tail);
      SwapStr(str,n,str_tail-1);
    }
  else{
	LOG((stderr,"IsMagicSquare_mode_on n count=%d\n",count));
	flag=IsMagicSquare(str,str_tail);
	LOG((stderr,"flag==%d\n",flag));
	if(flag==(-2)) exit(0);
  }
  return;
}
int main(void){
  int str[]={1,2,3,4,5,6,7,8,9};
	LOG((stderr,"LOG_mode_on\n"));
    Sort(str,9-1,9);
  return(0);
}
