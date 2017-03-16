#include<stdio.h>
#include<stdlib.h>

#define bool int
#define true 1
#define false 0


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
		init_bords();
		scanf("%d%d%d%d%d",&startx,&starty,&gorlx,&gorly,&n);
		while(n--){
		  scanf("%d%d%d%d",&c,&d,&x,&y);
			for(i=0;i<8;i++)
				for(j=0;j<2;j++)
					if(d) bord[x+j][y+i]=c;
					else  bord[x+i][y+j]=c;
		}
			puts((can_go_gorl())?"OK":"NG");
	}
	return(0);
}
void init_bords(void){
	int i,j;
	for(i=0;i<M;i++)
		for(j=0;j<N;j++)
			temp_bord[i][j]=bord[i][j]=0;
}

bool walk_block(int x,int y){
  static int count=0;
  if(temp_bord[x][y]){/* flag to return false soon */
	temp_bord[x][y]=false;/*  stand flag to search */
	if(((x==gorlx)&&(y==gorly))
		||walk_block(x+1,y)
		||walk_block(x,y+1)
		||walk_block(x-1,y)
		||walk_block(x,y-1))
		return (true);
	temp_bord[x][y]=true; /* unstand flag to search */
  }
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
