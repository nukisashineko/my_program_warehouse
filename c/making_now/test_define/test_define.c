#include<stdio.h>
#define fun(key_char,y,new_y,flag) \
if(key==key_char){\
	y=new_y;\
	printf("key=%c,%s=%f\n",key_char,#y,y);\
	flag=1;\
}

int main(int argc,char* argv[])
{
	double ex=0.0;
	fun('u',ex)
return(0);
}
