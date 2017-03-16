#ifndef HACKING_H
#define  HACKING_H

#include<stdlib.h>
#include<string.h>

void fatal(char *message){
  char error_message[100];

  strcpy(error_message,"[!!]fatal error:");
  strcpy(error_message,message);
  perror(error_message);
  exit(-1);
}
void *ec_malloc(unsigned int size){
  void *ptr;
  ptr = malloc(size);
  if (ptr == NULL)
    fatal("Can't get memory in ec_malloc()");
  return(ptr);
}

#endif
