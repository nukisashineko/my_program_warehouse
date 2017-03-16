/*2011.5.5 eight queen*/

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

bool queen_legth_line[8]={false};
bool bord[8][8];
FILE *fp;

void init_bord(void);//ok
bool can_set_queen(int x,int y);//ok
void set_queen(int x,int y);//ok
void reset_queen(int x,int y);//ok
void print_bord(void);//ok
void make_queen(int line_n);//ok
//void is_once_bord(void);/*あとで実装するかも…*/

#define MAX 8
#define LOG_CAN_SET_QUEEN(arg) fprintf(stderr,"%s%s=%s","can_set_queen",#arg,(can_set_queen arg )?"ok\n":"error\n")




void init_bord(void){
	int i,j;
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++)
			bord[i][j]=(false);
	}
	return;
}

void print_bord(void){
	int i,j;
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++)
			putc((bord[i][j])?'Q':'.',fp);
		putc('\n',fp);	
	}
	putc('\n',fp);
	return;
}
void set_queen(int y,int x){ bord[y][x]=true; queen_legth_line[y]=true; }
void reset_queen(int y,int x){ bord[y][x]=false; queen_legth_line[y]=false; }

bool can_set_queen(int y,int x){
	int i,j;
	for(i=y,j=x;(i<MAX)&&(j<MAX);i++,j++)//斜め右下
		if(bord[i][j]==true){ return (false); }
	for(i=y,j=x;(i<MAX)&&(j<MAX);j++)//真横
		if(bord[i][j]==true){ return (false); }
	for(i=y,j=x;((0<=i)&&(i<MAX))&&((0<=j)&&(j<MAX));i--,j++)//斜め右上
		if(bord[i][j]==true){ return (false); }
	return (true);
}

void make_queen(int line_n){
	int i;
	static int count=0;
	if(line_n<0){ fprintf(fp,"%d\n",++count); print_bord(); }
	for(i=0;i<MAX;i++){
		if( !(queen_legth_line[i]) && can_set_queen(i,line_n) ){
			set_queen(i,line_n);
			make_queen(line_n-1);
			reset_queen(i,line_n);
		}
	}
	return;
}


int main(void){
	fp=fopen("wirte_eight_queen.txt","w");
	init_bord();
	make_queen(MAX-1);
	print_bord();
	return(0);
}