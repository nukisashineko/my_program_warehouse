#include<stdio.h>
#include<stdlib.h>

char str[4]="";
FILE *fp_w,*fp_r;

char cleck(char *p){
	printf("*(p-5)=\"%s\"",p-5);
	if(*(p-3)!='h'&& *(p-3)!='c'&& *(p-3)!='n'/*※ .htm || .com || .net*/
	   && *(p-4)!='h'&& *(p-1)!='l'/*※ .html*/
	   &&*(p-1)!='/' /* フォルダでない */  
	   &&(*(p-3)=='.'||*(p-4)=='.'||*(p-5)=='.'))
		{printf("ture\n"); return (1);}
	printf("false\n");return (0);


}

char my_getchar(void){
	static char a;
	a=getc(fp_r);
	if(a==EOF)
		exit(0);
	return(a);

}

int main(void){
	int i,j,flag;
	char str[200],*p,c;
	fp_w=fopen("get_pict.sh","w");
	fp_r=fopen("toi","r");
	while(1){
		for(;(c=my_getchar())!='<';);
			if((c=my_getchar())!='a'/*||c!='i'*/);
			else if((c=my_getchar())!=' '/*||c!='m'*/);
			else if((c=my_getchar())!='h'/*||c!='g'*/);
			else {
				if(c=='h'){
					for(;((c=my_getchar())!='='););
					p=str;flag=0;
					if((c=my_getchar())=='"')
						{c=my_getchar();flag=1;}
					do{
						*p=c;
						p++;
						if(!flag){ *p='\0';if(!strcmp(".jpg",p-4)) break; }
					}while((c=my_getchar())!='"' && c!='>');
					if(c=='>'){ printf("continue\n");continue; }
					*p='\0';
					printf("flag=%s:**1**",((flag==1)?"true":"false"));
					if(cleck(p))
						fprintf(fp_w,"wget %s\n",str);
				}
#if 0
				else if(c=='g'){
					for(;((c=my_getchar())!='='););
					c=my_getchar();p=str;
					do{
						*p=c;
						p++;
						*p='\0';
					}while((c=my_getchar())!='>'&& strcmp(".jpg",p-4));
					if(c=='>')continue;
					*p='\0';
					printf("**2**");
					if(cleck(p))
						fprintf(fp_w,"wget %s\n",str);
				}
#endif
			}
			for(;((c=my_getchar())!='>'););
		
	}
	return(0);
}
