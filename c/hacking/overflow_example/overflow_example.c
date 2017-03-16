/*  vim: set foldmethod=marker commentstring=//%s foldmarker={{{,}}} : */
#include<stdio.h>
#include<string.h>
/*------------func declare----------------*/
/*-------------------------------------*/
/*-----------nomal func----------------*/
/*-------------------------------------*/

int main(int argc,char* argv[])
{
int value=5;
char buffer_one[8],buffer_two[8];
strcpy(buffer_one,"one");
strcpy(buffer_two,"two");

printf("[before] &buffer_one = %p, value = \'%s\' .\n",buffer_one,buffer_one);
printf("[before] &buffer_two = %p, value = \'%s\' .\n",buffer_two,buffer_two);
printf("[before] &value = %p, value = \'%d\' .\n",&value,value);

printf("\n[STRCPY]%d bite copy to buffer_two . \n\n",strlen(argv[1]));
strcpy(buffer_two,argv[1]);

printf("[after] &buffer_two = %p, value = \'%s\' .\n",buffer_two,buffer_two);
printf("[after] &buffer_one = %p, value = \'%s\' .\n",buffer_one,buffer_one);
printf("[after] &value = %p, value = \'%d\' .\n",&value,value);
return(0);
}
