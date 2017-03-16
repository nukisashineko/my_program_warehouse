#include<stdio.h>
#define fun2(y,new_y,flag) \
	y=new_y;\
	printf("%s=%f\n",#y,y);\
	flag=1

#define fun(key_char,y,new_y,flag) \
if(key==key_char){\
	printf("key=%c,",key_char);\
	fun2(y,new_y,flag);\
}
