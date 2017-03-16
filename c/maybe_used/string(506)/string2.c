#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NDEBUG 0

#if (NDEBUG==1)
#define LOG(arg) fprintf arg
#elif (NDEBUG==0)
#define LOG(arg) /*none*/
#endif

int henkan(char str[]);

int main(void){
	FILE *fp_w,*fp_r;
	int n,i;
	char str[0xffff];
	fp_r=fopen("input.txt","r");
	fp_w=fopen("output.txt","w");
	fscanf(fp_r,"%d",&n);
	fscanf(fp_r,"%s",str);
	for(i=0;i<n;i++){
	LOG((stderr,"%d:string=%s\n",i,str));
	henkan(str);
	}
	fprintf(fp_w,"%s\n",str);
	fclose(fp_w);
	fclose(fp_r);
	return(0);
}


int henkan(char str[]){
	int count,i;
	char str2[0xffff]="",temp[0xff],c='a';
	
	i=0;c=str[0];count=0;	
	do{
		if(c==str[i]){ count++; }
		else{ 
			sprintf(temp,"%d%c",count,c);
			strcat(str2,temp);
			LOG((stderr,"temp:%s\n",temp));
			c=str[i];
			count=1;
		}
		i++;
	}while(c!='\0');
	strcpy(str,str2);
	return (0);
}

