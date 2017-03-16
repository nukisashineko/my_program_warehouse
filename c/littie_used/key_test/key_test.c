#include<stdio.h>
int main(int argc,char* argv[])
{
	char c;
	while((c=getchar())!=EOF)
		printf("key:%c==%x\n",c,c);
return(0);
}
