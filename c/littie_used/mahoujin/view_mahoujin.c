#include<stdio.h>
#include "mahoujin.h"

void view_mahoujin(int str[],int n){
   int i,j;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      fprintf(stdout,"%2d,",str[i*n+j]);
    }
    fprintf(stdout,"\n");
  }
    fprintf(stdout,"\n");
  return;
}
/*
int main(void){
int flag,n=9;
int str[]={4,9,2,3,5,7,8,1,6};
view_mahoujin(str,3);
return(0);
}
*/
