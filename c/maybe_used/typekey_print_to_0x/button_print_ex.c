#include<stdio.h>
int main(void){
	char c,count=0;
	printf("fin==(ctrl+z)\n");
	while((c=getchar())!=EOF){ (c=='\n')? printf("\n"):printf("0x%x ",c); count++; }
	printf("do=%d\n",count);
	return(0);
}