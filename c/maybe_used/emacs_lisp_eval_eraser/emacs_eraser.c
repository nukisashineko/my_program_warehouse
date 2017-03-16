#include<stdio.h>
#include<string.h>
char eraser_line(void);
char hold_line(void);
#define true 1
#define false 0
#define bool char
char
eraser_line(void)
{
	char c;
	while( (c=getchar())!='\n' && c!=EOF );
	return((c==EOF)?EOF:'\n');
}
char
hold_line(void)
{
	char c;
	if( (c=getchar())!='\n' && c!=EOF )
		do{
			putchar(c);
		}while( (c=getchar())!='\n' && c!=EOF );
		putchar('\n');
//	printf("in_hold_line=%s",(c==EOF)?"EOF":(c=='\n')?"\\n":"other");
	if(c==EOF)
		putchar('\n');
	return((c==EOF)?EOF:'\n');
}
void lisp_cord(void){
	int i;
	char string[9];
	bool flag=true;
	while(flag){
//	puts("equal EOF");
		for(i=0 ;i<9-1 && (string[i]=getchar())!='\n'&& string[i]!=EOF ;i++);
		if(i<9-1){
			 string[i+1]='\0';
		}
		else if(string[i]==EOF){
		  string[i]='\0';
		  flag=false;
		}
		else{
		  string[i]='\0';
		}
//	printf("string=|%s|\n",string);
		if(string[i]!='\n'){
			if(strcmp(string,"CL-USER>")){
//	puts("not equal string");
				printf(string);
				if(hold_line()==EOF)
					flag=false;
			}else{
//	puts("equal string");
				if(hold_line()==EOF)
					flag=false;
			}
		}
	}
	return;	
}

int main(void)
{
/*
	char c;
	char string[9];
	while(1){
		if((string[0]=getchar())==EOF){
			puts("equal EOF");
			return(0);
		}
		putchar(string[0]);
		putchar('\n');
		if((c=hold_line())==EOF){
			puts("end of hold_line");
			return(0);
		}
		putchar('\n');
		printf("hold_line=%s",(c==EOF)?"EOF":(c=='\n')?"\\n":"other");
		putchar('\n');
		
	}
*/
	lisp_cord();
	return(0);
}
