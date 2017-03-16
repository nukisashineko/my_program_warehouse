#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DEBAG 0
 
#if (DEBAG==1)

#define LOG_LINE_MAKE_P() /*none*/
#define LOG_LINE() fprintf(stderr,"line=%d\n",__LINE__)
#define LOG(arg) fprintf arg
#define LOG_print_item_list(list) print_item_list(list)
#define LOG_print_item_about(q) print_item_about(q)
#elif (DEBAG==2)

#define LOG_LINE_MAKE_P() fprintf(stderr,"line=%d,file=%s\n",__LINE__,__FILE__)
#define LOG_LINE() fprintf(stderr,"line=%d,file=%s\n",__LINE__,__FILE__)
#define LOG(arg) fprintf arg
#define LOG_print_item_list(list) print_item_list(list)
#define LOG_print_item_about(q) print_item_about(q)
#elif (DEBAG==0)

#define LOG_LINE_MAKE_P() /*none*/
#define LOG_LINE() /*none*/
#define LOG(arg) /*none*/
#define LOG_print_item_list(list) /*none*/
#define LOG_print_item_about(q) /*none*/
#endif

typedef struct RESHIPI_LIST{
	char *str;
	struct RESHIPI_LIST *next;
} RESHIPI;
typedef struct ITEM_LIST{
	char *str;
	int value;
	RESHIPI *reshipi_list;
	struct ITEM_LIST *next;
} ITEM;


ITEM* make_item_p(char *str,int value){
	ITEM *new;
	new=(ITEM*)malloc(sizeof(ITEM));
	LOG_LINE_MAKE_P();
	new->str=(char*)malloc(sizeof(char)*(strlen(str)+1));
	LOG_LINE_MAKE_P();
	strcpy(new->str,str);
	new->value=value;
	LOG_LINE_MAKE_P();
	new->reshipi_list=NULL;
	new->next=NULL;

	return(new);
}
RESHIPI* make_reshipi_p(char *str){
	RESHIPI *new;

	new=(RESHIPI*)malloc(sizeof(RESHIPI));
	new->str=(char*)malloc(sizeof(char)*(strlen(str)+1));
	strcpy(new->str,str);
	new->next=NULL;

	return(new);
}

RESHIPI* get_reshipi(void){
	int i,n;
	char str[60];
	RESHIPI *reshipi_list,*new;

	LOG_LINE_MAKE_P();
	scanf("%d",&n);
	reshipi_list=make_reshipi_p(" ");
	LOG_LINE_MAKE_P();
	for(i=0;i<n;i++){
		scanf("%s",str);
		LOG((stderr,"get_reshipi():%s\n",str));
		LOG_LINE_MAKE_P();
		new=make_reshipi_p(str);
		LOG_LINE_MAKE_P();
		new->next=reshipi_list;
		LOG_LINE_MAKE_P();
		reshipi_list=new;
	}
	return(reshipi_list);
}

void free_item(ITEM* taget){
	RESHIPI *p,*q;
	if(taget->reshipi_list!=NULL){
	//	LOG_LINE();
		q=taget->reshipi_list;
		p=taget->reshipi_list->next;
		if(p){
			for(;p->next;q=p,p=p->next){
				q->next=NULL;
			LOG_LINE();
				free(q);
			}
			LOG_LINE();
			free(q);
			LOG_LINE();
			free(p);
			LOG_LINE();
		}
		else{
			LOG_LINE();
			q->next=NULL;
			free(q);
		}

	}
		LOG_LINE();
	taget->value=0;
	taget->next=NULL;
	free(taget->str);
		LOG_LINE();	
	free(taget);
		LOG_LINE();
	return;
}
void print_item_about(ITEM *item){
	ITEM *p;
	p=item;
		if(fprintf(stderr,"p:%p\n",((p==NULL)?NULL:p))){
			fprintf(stderr,"\tp->str:%p==%s\n\t"
			,((p->str==NULL)?NULL:p->str)
			,((p->str==NULL)?"NULL":p->str)
			);
			fprintf(stderr,"p->value:%p==%d\n\t"
			,(&p->value)
			,((p->value==0)?0:p->value)
			);
			fprintf(stderr,"p->reshipi_list:%p\n\t"
			,((p->reshipi_list==NULL)?NULL:p->reshipi_list)
			);
			fprintf(stderr,"==%s\n\t"
			,((p->reshipi_list==NULL)?"NULL":p->reshipi_list->str)
			);
			fprintf(stderr,"p->next:%p"
			,((p->next==NULL)?NULL:p->next)
			);
			fprintf(stderr,"==%s\n"			
			,((p->next==NULL)?"NULL":p->next->str)
			);
		}
		return;
}

void all_free_item(ITEM *item_list){
	ITEM *p,*q;
	LOG((stderr,"START:all_free_item();\n"));	
	q=item_list;
	p=item_list->next;
	if(p){
		LOG_LINE();
		for(;p->next;q=p,p=p->next){
			LOG_print_item_about(q);
		LOG_LINE();
				free_item(q);
		}
		LOG_LINE();
		LOG((stderr,"print_end q\n"));
			LOG_print_item_about(q);
		free_item(q);
		LOG_LINE();	
		LOG((stderr,"print_end p\n"));
			LOG_print_item_about(q);
		free_item(p);
		LOG_LINE();	
	}
	else{	
		LOG_LINE();
		free_item(q);
	}
	LOG((stderr,"END:all_free_item();\n"));	
	return;
}

void print_item_list(ITEM *item_list){
	ITEM *temp;
	LOG((stderr,"START:print_item_list();\n"));
	if(item_list->next==NULL)	LOG((stderr,"NULL\n"));
	else				LOG((stderr,"!NULL\n"));
	for(temp=item_list;temp->next;temp=temp->next)
		LOG((stderr,"temp:str=%s,value=%d\n",temp->str,temp->value));;
	LOG((stderr,"END:print_item_list();\n"));
	return;
}

ITEM* search_item(char *str,ITEM *item_list){
	ITEM *temp;
	for(temp=item_list;temp->next;temp=temp->next)
		if(temp->str)
			if(!strcmp(str,temp->str))
				return(temp);
	return(NULL);
}
int get_min_value(ITEM *taget,ITEM *item_list){
	int value;
	RESHIPI *temp;
	if(taget->reshipi_list!=NULL){
		for(value=0,temp=taget->reshipi_list;temp->next;temp=temp->next){
				LOG((stderr,"search_item():str=%s\n",temp->str));
			if(temp->str)
				value+=get_min_value(search_item(temp->str,item_list),item_list);
		}
			if((taget->value)<value)
				value=taget->value;
	}
	else
			value=taget->value;
	LOG((stderr,"get_min_value():str=%s,value=%d\n",taget->str,value));
	return(value);
}
int main(void){
	int i,n,m,value;
	char str[60];
	ITEM *item_list,*new,*temp;

while(1){
	LOG_LINE();
	
	scanf("%d",&n);
	if(n==0)
		break;


//	item_list=NULL;
	item_list=make_item_p(" ",0);
	LOG_LINE();
		LOG((stderr,"print_item_list_start p\n"));
			LOG_print_item_about(item_list);



	for(i=0;i<n;i++){
		if(scanf("%s%d",str,&value)<2){
			i--;
			continue;
		}
		LOG((stderr,"str=%s,value=%d\n",str,value));
		new=make_item_p(str,value);
		new->next=item_list;
		item_list=new;
	}
	LOG_LINE();
	LOG_print_item_list(item_list);
	scanf("%d",&m);
	for(i=0;i<m;i++){
		if(scanf("%s",str)<1){
			i--;
			LOG((stderr,"!!--happen scan error--!!\n"));
			continue;
		}
		LOG_LINE();
		LOG((stderr,"str=%s\n",str));
		temp=search_item(str,item_list);	
		LOG((stderr,"temp:str=%s,value=%d\n",temp->str,temp->value));
		LOG_LINE();
		temp->reshipi_list=get_reshipi();
	}
	LOG_LINE();
	scanf("%s",str);
	temp=search_item(str,item_list);
	printf("%d\n",get_min_value(temp,item_list));
	all_free_item(item_list);
	LOG_print_item_list(item_list);
	
}
	return(0);
}
