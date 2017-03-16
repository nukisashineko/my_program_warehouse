#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

#define MAX 100


void move_next_operator(char **current_point);//ok
int parenthesis_add(char **current_point);//ok
void strcat_plas(char *p,char **q,char *str);//ok
int get_value(char **current_point);//ok
//int string_math(char **current_point);

char *stac[MAX];int n=0;

bool search_log(char **log);
char *pop_log(	void	){
static char *null_p;
	null_p=0;
	printf("pop_log\n");
 	if(n<=0){
		return(null_p);
		// printf("error __LINE__==%d\n",__LINE__);exit(1); 
	}
	 return(stac[--n]);
}
void push_log(  char **log){ if(n>MAX){ printf("error __LINE__==%d\n",__LINE__);exit(1); } stac[n++]=*log; };

bool search_log(char **log){
	int i;
	for(i=0;i<n;i++)
		if(*log==stac[i]){ return(false); }
	return(true);
}

/*//関数化したいな…
do{
p=pop_log();
printf("search_log=true"); parenthesis_add(&p);
}while(p);
*/
int parenthesis_add(char **current_point){
	char *p,*q,str[MAX],*p2,*temp;
	int parenthesis_add_flag=0,sa_=0;
	static bool flag=false;
	static int nest=-1;
	nest++;
	p=q=*current_point;
	p2=str;
	for(;;q=p,p++,q++){
		printf("'%c'_",*p);
//	printf(",");
	move_next_operator(&p);
//	printf(",");	
		if( !parenthesis_add_flag ){/*フラグは立っていないなら*/
			if('*'==*p||*p=='/')/*operatorをみて後続の奴にカッコを入れさせる*/
				{ parenthesis_add_flag=1; *p2='('; p2++; }
		}else{ 
			if(('-'==*p||*p=='+')||(')'==*p||*p=='\0'))/*operatorをみて後続の奴にカッコを入れさせる*/
				{ parenthesis_add_flag=0; for(;(p-1)>=q;q++,p2++){ *p2=*q; } *p2=')'; p2++; }
		}
		for(;p>=q;q++,p2++){ *p2=*q; }
		if( *p=='\0' ){ break; }
		if( *p==')' ){ break; }/*カッコを飛ばす処理(ネスト回数を数える)*/
	}
	while( (temp=pop_log())!=NULL ){
		flag=true;
		printf("temp==%p\nn=%d\n",temp,n);
		printf("search_log=true\n"); 
		printf("sa_==%d\n",sa_=parenthesis_add(&temp));
		if(!nest){
			for(;sa_>0;sa_--,q--);
			for(;sa_<0;sa_++,q++);
		}
	}
		printf("sa_==%d\n",sa_);
	sa_=(q-*current_point)-strlen(str);
		printf("nest==%d\nflag=%s\nstr=%s\n*current_point=%s\nq=%s\n",nest,(flag)?"true":"false",str,*current_point,q);	
	if(!flag || !nest)strcat_plas(*current_point,&q,str);//*カウントポインタからqまでの文字列をけし、その場所にstrを挿入する。
	nest--;
	return(sa_);
}

int get_value(char **current_point){
	int value;
	char *p,*q,str[MAX];
	p=*current_point;/*ポインタの設定*/
	q=str;

	*q=*p;/*一文字目を取得*/
	p++;
	if(*q=='('){/*カッコが始まっていたらネストする*/
		printf("ネストします\n"); value=0;/*string_math(&p);*/
	}
	else{/*数字を取り出す処理*/
		for(q++;'0'<=*p && *p<='9';q++){ printf("'%c'_",*p);*q=*p; p++; }/*一文字ずつを取得*/
		printf("\n");
		*q='\0';
		value=atoi(str);
	}
	*current_point=p;
	return(value);
}

/*current_pointをoperator,null,')'に移動させる*/
void move_next_operator(char **current_point){
	char *p;
	int parenthesis_flag=0;
	p=*current_point;
//	printf("move");
	for(;;p++){
//		printf("'%c'_",*p);
		if(*p=='('){ 
			if(search_log(&p)){ 
				p++;
				push_log(&p);
//				printf("search_log=true"); parenthesis_add(&p); 
//				pop_log();
			}
			parenthesis_flag++; //  printf("parenthesis_flag=%d",parenthesis_flag);
			 continue; 
		}/*カッコを飛ばす処理(ネスト回数を数える)*/
		if(*p==')'){
			 parenthesis_flag--; //printf("parenthesis_flag=%d",parenthesis_flag);
		continue; }/*カッコを飛ばす処理(ネスト回数を数える)*/
		if(parenthesis_flag>0){ continue; }
		if('0'<=*p&&*p<='9'){ continue; }/*数字を飛ばす処理*/
		break;
	}

	printf("\n");
	*current_point=p;
	return;
}

void strcat_plas(char *p,char **q,char *str){//pからqまでの文字列をけし、その場所にstrを挿入する。
	char temp[MAX];
	*p='\0';
	strcpy(temp,*q);
	strcat(p,str);
	*q=p+strlen(str);
	strcat(*q,temp);
}

int main(void){
	int value;
	char str[MAX]={"(5*5+4)+3"};
	char str2[MAX]={"(1*2+3)+4*(5+6*7)/(8+9)*10"};
	char str3[MAX]={"(4876+56)"};
	char *p,*q;

	printf("\n!!parenthesis_add!!\n");
	p=str2;
	parenthesis_add(&p);
	printf("str2==%s\n",str2);


	printf("\n!!get_value!!\n");
	p=str3;
	value=get_value(&p);
	printf("value=%d\n",value);

	printf("\n!!move_next_operator!!\n");
	p=str;
	move_next_operator(&p);
	printf("*p=%c\n",*p);

	printf("\n!!strcat_plas!!\n");
	q=p=str;
	p+=1;
	q+=4;
	printf("str=%s\nstr2=%s\n",str,str2);
	strcat_plas(p,&q,str2);
	printf("str=%s\n",str);

	printf("\n!!move_next_operator!!\n");
	p=str;
	move_next_operator(&p);
	printf("*p=%c\n",*p);

	return(0);
}

/*
int string_math(char **current_point){
	int temp,flag=0,value;
	char *p,operator='n';
	p=*current_point;
	do{
	temp=get_value(&p);
	swich(operator){
			case'+': value+=temp; break;
			case'-': value-=temp; break;
			case'*': value*=temp; break;
			case'/': value/=temp; break;
			case'n': value=temp; break;/*clean_value*/
	} 
	operator=getc(p); p++;//operator=get_operator();
	}while( *p=='/0' || *p==')' );
	*current_point=p;
	return(value);
	
}*/