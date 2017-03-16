	#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int my_pow(int x,int y){
int i,ans=1;
for(i=0;i<y;i++){ ans*=x; }
return(ans);
}

bool subtraction_in_vector(int *data1,int *data2,int lenth1,int lenth2,int base){ 
	int i,j;// ,quotient,remainder;// 商、余
	bool more=false;
	for(i=0,j=0;!more && i<=lenth1 && j<=lenth2;i++,j++){ more=*(data1+i)>*(data2+j); printf("%d\n",more); }
	if(lenth1>lenth2 || more){// if(data1>data2)
			printf("case1:lenth1=%d,lenth2=%d\n",lenth1,lenth2);
			printf("case1:my_pow(10,base)=%d\n",my_pow(10,base));
		for(i=lenth1,j=lenth2;i>=0 && j>=0;i--,j--){
			*(data1+i)-=*(data2+j);
			if(0>*(data1+i)){
				(*(data1+i-1))--;  //   /* 繰り下がり */
				*(data1+i)+=my_pow(10,base);;//   /* 桁揃え */
			}
		}
		return(false);// +
	}
	else{	// if(data2>data1)
			printf("case2:lenth1=%d,lenth2=%d\n",lenth1,lenth2);
		for(i=lenth1,j=lenth2;i>=0 && j>=0;i--,j--){
			*(data2+j)-=*(data1+i);
			if(0>*(data2+j)){
				(*(data2+j-1))--;  //   /* 繰り下がり */
				*(data2+j)+=my_pow(10,base);//   /* 桁揃え */
			}
		}
		return(true);// -
	}
 }

int* get_big_num(char *str,int base,int *len){
	int i,*data,flag;
	char *p;

	scanf("%s",str);

	for(p=str;*p;p++);
	*len=(int)(p-str)/base;
	flag=((p-str)%base)?1:0;
	data=(int *)malloc(sizeof(int)*(*len+flag));
//	printf("(*len)=%d\n",(*len));
//	printf("(*len)+flag=%d\n",(*len)+flag);


	if( !flag ){ (*len)--; }// to error flag

	for(p-=base,i=*len;p>str;p-=base,i--){//四桁ずつ
//		printf("%d\n",atoi(p));
		*(data+i)=atoi(p);
		*p='\0';
	}

	if( i!=0 ){ i=0;  /* fprintf(stderr,"ok"); */ }// to error flag

//	printf("%d\n",atoi(str));
//	printf("i=%d\n",i);
	*(data+i)=atoi(str);
	return(data);
}


int main(void){
	int i,count,lenth1,lenth2,base=4;
	int *data1,*data2;
	char str[0xff];

//	printf("%d\n",(int)(p-str)); == strlen


	
	data1=get_big_num(str,base,&lenth1);
	data2=get_big_num(str,base,&lenth2);

	subtraction_in_vector(data1,data2,lenth1,lenth2,base);
	for(i=0;i<=lenth1;i++){ if(*(data1+i)){ printf("%d,",*(data1+i)); } } printf("\n");
//	for(i=0;i<=lenth2;i++){ printf("%d,",*(data2+i)); } printf("\n");

	free(data1);
	free(data2);
	
	return(0);
}
