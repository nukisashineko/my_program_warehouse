#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char *argv[]){
	int n;
	char str[0xff];
	int count,j;
	char str2[0xff],temp[0xf],c;

while(fscanf(stdin,"%d",&n),n){
	fscanf(stdin,"%s",str);
	for(;n--;){
	str2[0]='\0';c='a';
	j=0;c=str[0];count=0;	
	do{
		if(c==str[j]){ count++; }
		else{ 
			sprintf(temp,"%d%c",count,c);
			strcat(str2,temp);
			c=str[j];
			count=1;
		}
		j++;
	}while(c!='\0');
	strcpy(str,str2);
	}
	fprintf(stdout,"%s\n",str);
}
	return(0);
}

