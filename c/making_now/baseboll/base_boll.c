#include<stdio.h>
#include<string.h>
int main(void){
int flag,grand,ten,out,i,j,n;
char str[10];


scanf("%d",&n);
while(n--){
	flag=1;grand=0;out=0;ten=0;
	while(flag){
	scanf("%s",str);
	if(strcmp("HIT",str)){
		printf("%s\n",str);
		grand<<=1;
		grand+=1;
		if((grand&0xf)!=grand){
			ten++;
			grand&=0x4;
		}
	}
	else if(strcmp("OUT",str)){
		printf("%s\n",str);
		out++;
		if(out>=3){
			flag=0;
		}
	}
	else if(strcmp("HOMERUN",str)){
		printf("%s\n",str);
		for(i=j=0;i<4;i++){
			ten+=(grand<<i)&0x1;
		}
		grand=0;
	}
	}
	printf("%d\n",ten);
}
	return(0);
}
