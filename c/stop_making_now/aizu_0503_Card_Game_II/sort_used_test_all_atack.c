#include<stdio.h>
#include<stdlib.h>
FILE* fp;

void PrintStr(const int str[],const int str_tail){
  int i;
  for(i=0;i<str_tail;i++)
    fprintf(fp,"%d,",str[i]);
  putchar('\n');
  return;
}
void SwapStr(int str[],int n,int str_tail){
  int i,temp,k=str_tail-n;
  temp=str[k];
  for(i=k;i<str_tail;i++)
    str[i]=str[i+1];
  str[str_tail]=temp;
  return;
 }
void Sort(int str[],int n,int str_tail){
  int i;
  if(n>1)
      for(i=0;i<n+1;i++){
      Sort(str,n-1,str_tail);
      SwapStr(str,n,str_tail-1);
    }
  else{
    PrintStr(str,str_tail);
    /*done*/
  }
  return;
}

int main(int argc,char *argv[]){
  int str[]={0,1,2,3,4,5,6,7,8,9};
  fp=fopen("right_ans.txt","w");
  //SwapStr(str,8,10-1);
    Sort(str,9,10);
   //PrintStr(str,10);
  return(0);
}
