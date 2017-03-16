#include<stdio.h>

char str[4]="";

int main(void){
	FILE *fp;
	int i,t,temp,j,k;
	fp=fopen("get_pict.sh","w");
	for(i=0;i<175;i++){
		for(temp=i,j=0;j<3;j++){
			for(t=100,k=0;k<j;t/=10,k++);
			str[j]=temp/t+'0';
			temp%=t;
		}
				
		fprintf(fp,"wget http://blog-imgs-55.fc2.com/c/o/t/cottonlife777/201207008000%s.jpg\n",str);
	}
	return(0);
}
