#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int henkan(char str[]){
	int count;
	char str2[0xfff]="",temp[0xff],*p,c='a';
	
	p=str;c=*p;count=0;	
	do{
		if(c==*p){ count++; }
		else{ 
			sprintf(temp,"%d%c",count,c);
			strcat(str2,temp);
//			printf("temp:%s\n",temp);
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
	fp_r=fopen("input.txt","r");
	fp_w=fopen("output.txt","w");
	fscanf(fp_r,"%d",&n);
	fscanf(fp_r,"%s",str);
	for(;n--;){
//	printf("%d:string=%s\n",i,str);
	henkan(str);
	}
//	printf("%d",0xfffff+0xfff);
	fprintf(fp_w,"%s\n",str);
	return(0);
}
