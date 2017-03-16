#include<stdio.h>
#include<string.h>

int henkan(char str[]){
	int count;
	char str2[0xfff]="",temp[0xff],*p,c;
	
	p=str;c=*p;count=0;
	do{
		if(c==*p){ count++; }
		else{ 
			sprintf(temp,"%d%c",count,c);
			strcat(str2,temp);
			c=*p;
			count=1;
		}
		p++;
	}while(c!='\0');
	strcpy(str,str2);
	return (0);
}

int main(void){
	FILE *fp_w,*fp_r;
	int n;
	char str[0xfff];
	scanf("%d",&n);
	scanf("%s",str);
	for(;n--;){
	henkan(str);
	}
	printf("%s\n",str);
	return(0);
}
