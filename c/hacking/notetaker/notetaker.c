/*  vim: set foldmethod=marker commentstring=//%s foldmarker={{{,}}} : */
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include "../hacking.h"

/*------------func declare----------------*/
void fatal(char *);
void *ec_malloc(unsigned int);
/*-------------------------------------*/
/*-----------nomal func----------------*/
void usage(char *prog_name,char filename){
  printf("Usage:%s <date to concatnation %s>\n",prog_name,filename);
}
/*-------------------------------------*/

int main(int argc,char* argv[])
{
  int userif,fd;
  char *buffer,*datafile;

buffer =(char *)ec_malloc(100);
datafile = (char *)ec_malloc(20);

return(0);
}
