#include<stdio.h>


int main(void){
	int i,a,b,r;
	a=3;
	b=8;
	r=10;
	printf("%d.",a/b);
	a%=b*10;
	for(i=0;i<r;i++){ 
	printf("%d",a/b);
	a%=b*10;
	}
}

