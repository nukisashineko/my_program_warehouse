#include<stdio.h>
int main(int argc,char *argv[]){
	int i;
	for(i=0;argv[i];i++)
		puts(argv[i]);
	return(0);
}
