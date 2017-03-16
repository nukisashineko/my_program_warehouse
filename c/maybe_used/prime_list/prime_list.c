#include<stdio.h>
#include<stdlib.h>

typedef struct _prime_{
	int value;
	struct _prime_ *next;
} PRIME;

PRIME* make_prime_p(void){
	PRIME *new; 
	new=(PRIME*)malloc(sizeof(PRIME));
	new->next=NULL;
	new->value=0;
	return(new);
}

void print_prime(PRIME *prime_list_head){
	PRIME *temp;
	for(temp=prime_list_head;temp->value!=0;temp=temp->next)
		printf("%d,",temp->value);
}

int main(int argc,char *argv[]){
	PRIME *new_p,*temp,*prime_list_head,*prime_list_tail;
	int i,n;

	sscanf(argv[1],"%d",&n);

	prime_list_head=make_prime_p();
	prime_list_head->value=2;
	new_p=make_prime_p();
	prime_list_head->next=new_p;
	prime_list_tail=prime_list_head;

	for(i=2;i<n;i++){
		for(temp=prime_list_head;temp->value!=0;temp=temp->next)
			if(i%temp->value==0){ break; }
		if(temp->next==NULL){
			new_p=make_prime_p();
			new_p->value=i;
			new_p->next=prime_list_tail->next;
			prime_list_tail->next=new_p;
			prime_list_tail=prime_list_tail->next;
		}
	}
	print_prime(prime_list_head);
	return(0);
}
