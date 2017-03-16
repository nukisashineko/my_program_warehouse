#include<stdio.h>
#include<stdlib.h>
int main(void){
int n,i,d;
char onpu[256],str[256],*temp;
FILE *fp,*fp2,*fp3,*fp4;
	fp=fopen("data1.txt","r");
	fp2=fopen("data2.txt","r");
	fp3=fopen("n.txt","r");
	fp4=fopen("ans.txt","w");
	if(!(fp&&fp2&&fp3&&fp4)){ fprintf(stderr,"error\n"); exit(1); }
	fscanf(fp3,"%d",&n);
	for(i=0;i<n;i++){
		fscanf(fp,"%s %s",str,onpu);
		fscanf(fp2,"%d",&d);
		 fprintf(fp4,"buzzer_%s_%s();\n",str,onpu);
	}
	return(0);
}