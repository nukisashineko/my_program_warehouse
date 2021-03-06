#include<stdio.h>
//#include<stdbool.h>
#include<stdlib.h>

#define bool int
#define true 1
#define false 0

#define DEBAG 2
 
#if (DEBAG==1)

#define LOG_LINE_P() /*none*/
#define LOG_P() /*none*/
#define LOG_LINE() fprintf(stderr,"line=%d\n",__LINE__)
#define LOG(arg) fprintf arg
#define LOG_print_bord(arg) /*none*/
#elif (DEBAG==2)

#define LOG_LINE_P() fprintf(stderr,"line=%d,file=%s\n",__LINE__,__FILE__)
#define LOG_LINE() fprintf(stderr,"line=%d,file=%s\n",__LINE__,__FILE__)
#define LOG_P(arg) fprintf arg
#define LOG(arg) fprintf arg
#define LOG_print_bord(arg) print_bord arg

#elif (DEBAG==0)

#define LOG_LINE_MAKE_P() /*none*/
#define LOG_LINE() /*none*/
#define LOG_P(arg) /*none*/
#define LOG(arg) /*none*/
#define LOG_print_bord(arg) /*none*/

#endif



#define M 105
#define N 105

bool walk_block(int,int);
bool can_go_gorl(void);
void init_bords(void);
void print_bord(int,int);

char temp_bord[M][N];
int bord[M][N];
int startx,starty,gorlx,gorly;
int w,h;

int main(int argv,char **argc){
	int c,d,x,y,n,i,j;
	while(scanf("%d%d",&w,&h),w&&h){
		LOG((stderr,"w=%d,h=%d\n",w,h));
		init_bords();
		scanf("%d%d%d%d%d",&startx,&starty,&gorlx,&gorly,&n);
		LOG((stderr,"sx=%d,sy=%d,gx=%d,gy=%d,n=%d\n",startx,starty,gorlx,gorly,n));
		while(n--){
			scanf("%d%d%d%d",&c,&d,&x,&y);
			LOG((stderr,"c=%d,d=%d,[%d][%d]\n",c,d,x,y));
			for(i=0;i<8;i++)
				for(j=0;j<2;j++)
					if(d) bord[x+j][y+i]=c;
					else  bord[x+i][y+j]=c;
				print_bord(w,h);
				LOG_LINE();
		}
		LOG_LINE();
		puts((can_go_gorl())?"OK":"NG");
	}
	return(0);
}

void print_bord(int w,int h){
	int i,j;
		LOG((stderr,"w=%d,h=%d\n",w,h));
	for(i=0;i<w;i++){
		for(j=0;j<h;j++)
			printf("%d",(i==startx&&j==starty)?8:((i==gorlx)&&(j==gorly))?9:bord[i][j]);
		printf("\n");
	}

}
void print_temp_bord(int w,int h,int x,int y){
int i,j;
	for(i=0;i<w;i++){
		for(j=0;j<h;j++)
			fprintf(stderr,"%d",(i==x&&j==y)?7:(i==startx&&j==starty)?8:((i==gorlx)&&(j==gorly))?9:temp_bord[i][j]);
		printf("\n");
	}

}
void init_bords(void){
	int i,j;
	for(i=0;i<M;i++)
		for(j=0;j<N;j++)
			temp_bord[i][j]=bord[i][j]=0;
}

bool walk_block(int x,int y){
	static int count=0;
	LOG((stderr,"%d:[%d][%d]\n",count++,x,y));
	if(!temp_bord[x][y]);/* flag to return false soon */
	else if( temp_bord[x][y]=0 /*  stand flag to search */
		||((x==gorlx)&&(y==gorly))
		||walk_block(x+1,y)
		||walk_block(x,y+1)
		||walk_block(x-1,y)
		||walk_block(x,y-1))
		return (true);
	else if (temp_bord[x][y]=true);/*  unstand flag to search */
	print_temp_bord(w,h,x,y);
	return (false);
}
bool can_go_gorl(void){
	int color=bord[startx][starty];
	int i,j;
	for(i=M-1;i;i--)
		for(j=N-1;j;j--)
			temp_bord[i][j]=(bord[i][j]==color)?1:0;
	if(!temp_bord[startx][starty]
	 ||!temp_bord[gorlx][gorly]) /* flag to return false soon */
		return(false);
	return(walk_block(startx,starty));
}
 
 
