#include<stdio.h>
#include<string.h>

int flag;

char my_getchar(void){
	static char a;
	a=getchar();
	if(a==EOF)
		flag=0;
	return(a);

}

int main(void){
	int i;
	char str[10]="Hashino",c;
	 flag=1;
	scanf("%d",&i);
	c=my_getchar();
	while(flag){
		for(;(c=my_getchar())!='H' && flag;){ putchar(c); };
		for(i=1;i<7 && flag;i++){ str[i]=my_getchar(); };
		if(!flag){ str[i]='\0'; }
		if(!strcmp("Hoshino",str))
			printf("Hoshina");
		else
			printf("%s",str);	
	}
	return(0);
}
 
