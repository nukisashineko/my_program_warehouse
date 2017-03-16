/*2011.5.5 nannpure*/

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

#define NDEBUG

bool temp_bord[9][9];
char bord[9][9];
FILE *fp;

void init_bord(void);//ok
void init_temp_bord(void);//ok
bool search_set_num(char num);//ok
void set_num(int x,int y,char num);//ok
//void reset_num(int x,int y 	 );
bool is_end(void);/*全てのマスに数字を入れていればtrue*/
void print_bord(void);//ok
void make_nannpure(void);
bool bord_side_line_count_true(int y,int x);//ok
bool bord_legth_line_count_true(int y,int x);//ok
bool bord_box_count_true(int y,int x);//ok
void get_mondai(void);

#define MAX 9
#define BROD_COUNT_TRUE(arg) (bord_side_line_count_true arg || bord_legth_line_count_true arg || bord_box_count_true arg )

#ifndef NDEBUG
#define LOG_SEARCH_SET_NUM(n) \
fprintf(stderr,"%s%s%s=%s","search_set_num(",#n,")",(search_set_num(n) )?"ok\n":"error\n");\
	print_bord();\
	print_temp_bord();

#else
#define LOG_SEARCH_SET_NUM(arg) /*none*/
#endif /* NDEGUG */
void get_mondai(void){
	int i,j;
	FILE *fp_r;
	fp_r=fopen("mondai","r");
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++)
			bord[i][j]=getc(fp_r);
		getc(fp_r);//deleat '\n'
	}
	return;
}

void init_temp_bord(void){
	int i,j;
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++)
			temp_bord[i][j]=(true);
	}
	return;
}
void init_bord(void){
	int i,j;
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++)
			bord[i][j]=('0');
	}
	return;
}
bool is_end(void){
	int i,j;
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++)
			if(bord[i][j] =='0'){ return (false); }
	}
	return (true);
}
void print_bord(void){
	int i,j;
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++)
			putc(bord[i][j],fp);
		putc('\n',fp);	
	}
	putc('\n',fp);
	return;
}

void print_temp_bord(void){
	int i,j;
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++)
			putc((temp_bord[i][j])?'1':'.',fp);
		putc('\n',fp);	
	}
	putc('\n',fp);
	return;
}

void set_num(int y,int x,char num){ bord[y][x]=(num+'0'); }
void reset_num(int y,int x	 ){ bord[y][x]='0'; }

bool bord_legth_line_count_true(int y,int x){
	int i,j;
	int count=0;
	for(i=0,j=x;(i<MAX)&&(j<MAX);i++)//縦
		if(temp_bord[i][j]==(true)){
			count++;
		}
	return ((count==1)?true:false);
}
bool bord_side_line_count_true(int y,int x){
	int i,j;
	int count=0;
	for(i=y,j=0;(i<MAX)&&(j<MAX);j++)//横
		if(temp_bord[i][j]==(true)){
			count++;
		}
	return ((count==1)?true:false);
}
bool bord_box_count_true(int y,int x){
	int i,j;
	int count=0;
	for(i=(y/3*3);i<(y/3*3)+3;i++){//枠の中
		for(j=(x/3*3);j<(x/3*3)+3;j++)
		if((temp_bord[i][j]==(true))){
			count++;
		}
	}
	return ((count==1)?true:false);
}
void bord_set_false(int y,int x){
	int i,j;
	for(i=y,j=0;(i<MAX)&&(j<MAX);j++)//横
			temp_bord[i][j]=(false);
	for(i=0,j=x;(i<MAX)&&(j<MAX);i++)//縦
			temp_bord[i][j]=(false);
	for(i=(y/3*3);i<(y/3*3)+3;i++){//枠の中
		for(j=(x/3*3);j<(x/3*3)+3;j++)
			temp_bord[i][j]=(false);
	}
	return;
}
bool search_set_num(char num){
	int i,j;
	bool flag=false;
	init_temp_bord();
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++){
			if(bord[i][j] != '0'){ temp_bord[i][j]=false; }
			if(bord[i][j] == (num+'0')){ bord_set_false(i,j); }
		}
	}
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++){
			if((temp_bord[i][j]) && (bord[i][j] == '0') && BROD_COUNT_TRUE((i,j)) ){
			set_num(i,j,num);
			flag=true; 
			}
		}
	}
	return (flag);
}

void make_nannpure(void){
	int i;
	for(i=1;;i++){
		if(i>MAX){ i=1; if(is_end()){ return; } }
		search_set_num(i);
	}
}

int main(void){
	init_bord();
	get_mondai();
	fp=fopen("wirte_ans.txt","w");
	LOG_SEARCH_SET_NUM(8);
	LOG_SEARCH_SET_NUM(8);
	LOG_SEARCH_SET_NUM(8);
	LOG_SEARCH_SET_NUM(8); 
	make_nannpure();
	print_bord();
	return(0);
}
