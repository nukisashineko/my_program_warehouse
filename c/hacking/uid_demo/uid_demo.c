/*  vim: set foldmethod=marker commentstring=//%s foldmarker={{{,}}} : */
#include<stdio.h>

/*------------func declare----------------*/
/*-------------------------------------*/
/*-----------nomal func----------------*/
/*-------------------------------------*/

int main(int argc,char* argv[])
{
printf("実 uid = %d\n",getuid());
printf("実行 uid = %d\n",geteuid());
return(0);
}
