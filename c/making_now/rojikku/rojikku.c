#include<stdio.h>
#include<stdbool.h>

#define N 10
#define LOG_CAN_SET_QUEEN(arg) fprintf(stderr,"%s%s=%s","can_set_queen",#arg,(can_set_queen arg )?"ok\n":"error\n")
#define ROJIKKU_to_char(c) ((c==empty)?"□":(c==white)?"☓":(c==brack)?"■": "err")

/*debug*/
#define fp stdout


typedef enum{ empty=0,white,brack }ROJIKKU;
bool queen_legth_line[8]={false};
int date[N][N];
bool bord[N][N];
//FILE *fp;

void init_bord(void);
bool can_set_brock(int x,int y);
void set_element(int x,int y,ROJIKKU c);
void print_bord(void);
void do_rojikku(int line_n);



void set_element(int x,int y,ROJIKKU c){ date[x][y]=c; return; }

void init_bord(void){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			set_element(i,j,empty);
	}
	return;
}

void print_bord(void){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			fprintf(fp,"%s",ROJIKKU_to_char(date[i][j]));
			/*putc(ROJIKKU_to_char(date[i][j]),fp);*/
		putchar('\n'); /*putc('\n',fp);*/
	}
	putchar('\n'); /*putc('\n',fp);*/
	return;
}
int main(void){
//fp=fopen("ans","w");
init_bord();
print_bord();
}
