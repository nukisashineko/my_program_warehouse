

#define N 10
#define LOG_CAN_SET_QUEEN(arg) fprintf(stderr,"%s%s=%s","can_set_queen",#arg,(can_set_queen arg )?"ok\n":"error\n")
#define ROJIKKU_to_char(c) (c==empty)?"□":(c==white)?"☓":(c==brack)?"■": "err";

typedef enum{ white=-1,empty,brack }ROJIKKU;
bool queen_legth_line[8]={false};
bool bord[N][N];
FILE *fp;
fp=stdout;

void init_bord(void);
bool can_set_brock(int x,int y);
void set_element(int x,int y,ROJIKKU c);
void print_bord(void);
void do_rojikku(int line_n);


void init_bord(void){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			set_element(i,j,empty)
	}
	return;
}

void print_bord(void){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			putc(ROJIKKU_to_char(date[i][j]),fp);
		putc('\n',fp);	
	}
	putc('\n',fp);
	return;
}
int main(void){
init_bord();
print_bord();
}