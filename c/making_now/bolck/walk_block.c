#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>



#define M 10
#define N 10


bool walk_block(int,int);


char temp_bord[M][N];
int bord[M][N];
int startx=1,starty=1,gorlx=8,gorly=8;
int w=9,h=9;

void print_bord(int w,int h,int x,int y){
int i,j;
	for(i=0;i<w;i++){
		for(j=0;j<h;j++)
			fprintf(stderr,"%d",(i==y&&j==x)?7:(i==starty&&j==startx)?8:((i==gorly)&&(j==gorlx))?9:bord[i][j]);
		printf("\n");
	}

}
int main(int argv,char **argc){
		int c,d,x,y,i,j;
			c=d=1;x=y=0;
			for(i=0;i<8;i++)
				for(j=0;j<2;j++)
					if(d) bord[y+j][x+i]=c;
					else  bord[y+i][x+j]=c;
			c=1;d=0;;x=7;y=1;
			for(i=0;i<8;i++)
				for(j=0;j<2;j++)
					if(d) bord[y+j][x+i]=c;
					else  bord[y+i][x+j]=c;
				print_bord(w,h,x,y);
		walk_block(0,0);
		return(0);
}

bool walk_block(int x,int y){
	static int count=0;
	fprintf(stderr,"%d:[%d][%d]\n",count++,x,y);
	print_bord(w,h,x,y);
	if(!bord[y][x]);/* flag to return false soon */
	else if( bord[x][y]=0 /*  stand flag to search */
		||((x==gorlx)&&(y==gorly))
		||walk_block(x+1,y)
		||walk_block(x,y+1)
		||walk_block(x-1,y)
		||walk_block(x,y-1))
		return (true);
	else if (bord[x][y]=true);/*  unstand flag to search */
	return (false);
}

