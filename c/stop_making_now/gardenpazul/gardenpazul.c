#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  N 8

FILE *fp;
#define getchar() getc(fp)
void *my_malloc(int n){
	void *A;
	A=(void*)malloc(n);
	if(!A){ printf("malloc can not get memory \n"); exit(1);}
	return(A);
}
#define malloc(A) my_malloc(A)


typedef enum{ west,east,north,south } DIRECTION;
typedef struct ans{
	short int x;
	short int y;
	DIRECTION direction;
	struct ans *next;
} ANS;

ANS *ans_stack;

typedef enum{ bloom=0,bud } CONDITION;
typedef enum{ red=0,yellow } FLOWER_COLOR;

typedef struct flower{
	FLOWER_COLOR color;
	CONDITION condition;
	union block *next;
} FLOWER;

typedef struct specal{
	int x;
	int y;
} SPECIAL;
typedef union block
{
	FLOWER flower;
	SPECIAL special;
} BLOCK;
BLOCK *flower_list;
BLOCK *bord[N][N];
BLOCK muimui,butterfly;

void BLOCK_pointer_swap(BLOCK**,BLOCK**);
void push_ans(int,int,DIRECTION);
ANS* pop_ans(void);
void init_ans_stack(void);
void init_flower_list(void);
void init_bord(void);
void init_temp_bord(bool [N][N]);
void scan_map(void);
void can_muimui_move_point(bool[N][N],int,int);
bool can_butterfly_move(bool[N][N],int,int);
bool are_flower_all_bloom(void);
void before_butterfly_move_above_flower(BLOCK*,BLOCK*);
void butterfly_move_above_flower(BLOCK*,BLOCK*);
bool garder_pazul(void);

void BLOCK_pointer_swap(BLOCK **a,BLOCK **b)
{
	static	BLOCK temp;
	temp=**a;
	**a=**b;
	**b=temp;
	return;
}
void push_ans(int x,int y,DIRECTION direction){
	ANS *temp;
	temp=(void*)malloc(sizeof(ANS));
	temp->x=x;
	temp->y=y;
	temp->direction=direction;
	temp->next=ans_stack;
	ans_stack=temp;
	return;
}
ANS* pop_ans(void){
	ANS *temp;
	temp=ans_stack;
	if(ans_stack!=NULL)
		ans_stack=ans_stack->next;
	return(temp);
}
void init_temp_bord(bool temp_bord[N][N])
{
	int i,j;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			temp_bord[i][j]=false;
	return;
}
void init_ans_stack(void)
{
	ans_stack=NULL;
}
void init_flower_list(void)
{
	flower_list=NULL;
}
void init_bord(void)
{
	int i,j;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			bord[i][j]=NULL;
	return;
}

void scan_map(void)
{
	BLOCK *temp;
	char c;
	int i,j,tmpx,tmpy;
//	char tmp_color[7];
//	char tmp_condition[6];
//	printf("花の位置の入力数を入れてください。\n花の位置を入力してください(x,y,color condition)\n");
//	scanf("%d",&n);
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			if((c=getchar()-'0')!=0){
				temp=(void*)malloc(sizeof(BLOCK));
				//scanf("%d%d%s%s",&tmpx,&tmpy,tmp_color,tmp_condition);
				if(c==5){ //5==muimui
					muimui.special.x=tmpx=i;
					muimui.special.y=tmpy=j;
				}else if(c==7){//7==butterfly
					butterfly.special.x=tmpx;
					butterfly.special.y=tmpy;
					bord[tmpx][tmpy]=&butterfly;
				}else if(c==1||c==2||c==3||c==9){
					//1==bud_red_flower,2==bud_yellow_flower,3==bloom_yellow_flower,9==bloom_red_flower
					tmpx=i;tmpy=j;temp->flower.color=(c==1)?red:yellow;
					temp->flower.condition=(c==1||c==2)?bud:bloom;
			
//				if(!strcmp("red",tmp_color))		{ temp->flower.color=red; }
//				else if(!strcmp("yellow",tmp_color))	{ temp->flower.color=yellow; }
//				else 					{ goto err; }
//				if(!strcmp("bloom",tmp_condition))	{ temp->flower.condition=bloom; }
//				else if(!strcmp("bud",tmp_condition))	{ temp->flower.condition=bud; }
//				else 					{ goto err; }
	
				temp->flower.next=flower_list;
				flower_list=temp;
			
				bord[tmpx][tmpy]=temp;
				}
			}
		getchar();//'\n' to dast
	
	}

//		printf("ムイムイの位置を入力してください(x,y)\n");
//		scanf("%d%d",&tmpx,&tmpy);
//		muimui.special.x=tmpx;
//		muimui.special.y=tmpy;
//		muimui don't put on bord because muimui is player and it can free moving;

//		printf("蝶の位置を入力してください(x,y)\n");		
//		scanf("%d%d",&tmpx,&tmpy);
//		butterfly.special.x=tmpx;
//		butterfly.special.y=tmpy;
//		bord[tmpx][tmpy]=&butterfly;
	return;
}

void can_muimui_move_point(bool temp_bord[N][N],int x,int y)
{
	temp_bord[x][y]=true;
	if(x+1<N &&  !bord[x+1][y]&&  !temp_bord[x+1][y]){ can_muimui_move_point(temp_bord,x+1,y); }
	if(x-1>=0 && !bord[x-1][y]&& !temp_bord[x-1][y]){ can_muimui_move_point(temp_bord,x-1,y); }
	if(y+1<N && !bord[x][y+1]&& !temp_bord[x][y+1]){ can_muimui_move_point(temp_bord,x,y+1); }
	if(y-1>=0 && !bord[x][y-1]&& !temp_bord[x][y-1]){ can_muimui_move_point(temp_bord,x,y-1); }
	return;
}
bool can_butterfly_move(bool temp_bord[N][N],int x,int y)
{
	BLOCK *flower_stack;
	int tmpx,tmpy;
	
	flower_stack=NULL;
	if(0<=x-1 && x+1<N &&temp_bord[x+1][y]&&bord[x-1][y]){//east
		for(tmpx=x+1;tmpx>=0&&bord[tmpx][y];tmpx--);
			if(tmpx>=0){ 
					for(tmpx=x-1;tmpx>=0&&bord[tmpx][y];tmpx--){
						butterfly_move_above_flower(bord[tmpx][y],flower_stack);
					}
					bord[x][y]=NULL;
					butterfly.special.x=tmpx; 
					bord[tmpx][y]=&butterfly;
					if(are_flower_all_bloom()||garder_pazul() ){
						push_ans(x,y,east);	
						return(true);
					}
					bord[tmpx][y]=NULL;
					butterfly.special.x=x;
				 	bord[x][y]=&butterfly;
					for(tmpx++;tmpx!=x&&bord[tmpx][y];tmpx++){
						before_butterfly_move_above_flower(bord[tmpx][y],flower_stack);
					}

			}
	
	}
	if(0<=x-1 && x+1<N && temp_bord[x-1][y]&&bord[x+1][y]){//west
			for(tmpx=x+1;tmpx<N&&bord[tmpx][y];tmpx++);
			if(tmpx<N){ 
					for(tmpx=x+1;tmpx<N&&bord[tmpx][y];tmpx++){
						butterfly_move_above_flower(bord[tmpx][y],flower_stack);
					}
					bord[x][y]=NULL; 
					butterfly.special.x=tmpx;
					bord[tmpx][y]=&butterfly;
					if(are_flower_all_bloom()||garder_pazul() ){
						push_ans(x,y,west);	
						return(true);
					}
					bord[tmpx][y]=NULL;
					butterfly.special.x=x;
				 	bord[x][y]=&butterfly;
					for(tmpx--;tmpx!=x&&bord[tmpx][y];tmpx--){
						before_butterfly_move_above_flower(bord[tmpx][y],flower_stack);
					}
			}
	}
	if(0<=y-1 && y+1<N &&temp_bord[x][y+1]&&bord[x][y-1]){//south
 			for(tmpy=y-1;tmpy>=0&&bord[x][tmpy];tmpy--);
			if(tmpy>=0){
		 			for(tmpy=y-1;tmpy>=0&&bord[x][tmpy];tmpy--){
						butterfly_move_above_flower(bord[x][tmpy],flower_stack);
					}
					bord[x][y]=NULL; 
					butterfly.special.y=tmpy;
					bord[x][tmpy]=&butterfly;
					if(are_flower_all_bloom()||garder_pazul() ){
						push_ans(x,y,south);	
						return(true);
					}
					bord[x][tmpy]=NULL;
					butterfly.special.y=y;
				 	bord[x][y]=&butterfly;
					for(tmpy++;tmpy!=y&&bord[x][tmpy];tmpy++){
						before_butterfly_move_above_flower(bord[x][tmpy],flower_stack);
					}
			}
	
	}
	if(0<=y-1 && y+1<N &&temp_bord[x][y-1]&&bord[x][y+1]){//north
			for(tmpy=y+1;tmpy<N&&bord[x][tmpy];tmpy++);
			if(tmpy<N){ 
					for(tmpy=y+1;tmpy<N&&bord[x][tmpy];tmpy++){
						butterfly_move_above_flower(bord[x][tmpy],flower_stack);
					}
					bord[x][y]=NULL;
					butterfly.special.y=tmpy; 
					bord[x][tmpy]=&butterfly;
					if(are_flower_all_bloom()||garder_pazul() ){
						push_ans(x,y,north);	
						return(true);
					}
					bord[x][tmpy]=NULL;
					butterfly.special.y=y;
				 	bord[x][y]=&butterfly;
					for(tmpy--;tmpy!=y&&bord[x][tmpy];tmpy--){
						before_butterfly_move_above_flower(bord[x][tmpy],flower_stack);
					}
			}
	}
	return(false);
}

bool are_flower_all_bloom(void)
{
	BLOCK *temp;
	for(temp=flower_list;temp->flower.condition==bloom && temp->flower.next; temp=temp->flower.next);
	if(temp->flower.next==NULL)
		return(true);
	return(false);
}
void butterfly_move_above_flower(BLOCK *target,BLOCK *flower_stack)
{
		BLOCK *temp;
		temp=(void*)malloc(sizeof(BLOCK));
		*temp=*target;
		temp->flower.next=flower_stack;//temp next is stack next
		flower_stack=temp;

		if(target->flower.color==red){ 
			target->flower.condition=bloom;
		}
		if(target->flower.color==yellow){ 
			target->flower.condition=(target->flower.condition==bud)?bloom:bud;
		}
		return;
}
void before_butterfly_move_above_flower(BLOCK *target,BLOCK *flower_stack)
{	
		BLOCK *temp;
		temp=flower_stack;
		flower_stack=flower_stack->flower.next;
		*temp->flower.next=*target->flower.next;//next is not equal stack or list
		*target=*temp;
		free(temp);
		return;
}
bool garder_pazul(void)
{	
	
	bool temp_bord[N][N];
//	bool **temp_bord;
	int x,y,i,tmpx,tmpy,tmp_mui_x,tmp_mui_y;
//	temp_bord=(bool**)malloc(sizeof(bool*)*N);
//	for(i=0;i<N;i++){ temp_bord[i]=(bool*)malloc(sizeof(bool)*N); }
	tmp_mui_x=muimui.special.x;
	tmp_mui_y=muimui.special.y;
	init_temp_bord(temp_bord);
	can_muimui_move_point(temp_bord,muimui.special.x,muimui.special.y);
	if(can_butterfly_move(temp_bord,butterfly.special.x,butterfly.special.y)){ return(true); }
	
	for(x=0;x<N;x++)
		for(y=0;y<N;y++){
			if(bord[x][y]){
				if(0<=x-1 && x+1<N &&temp_bord[x+1][y]&&!bord[x-1][y]){//east
					for(tmpx=x-1;tmpx>=0&&!bord[tmpx-1][y];tmpx--);
						if(tmpx<0){ tmpx=0; }
						if(tmpx>=0){
						 	BLOCK_pointer_swap(&bord[x][y],&bord[tmpx][y]);
							muimui.special.x=tmpx+1;
							if( garder_pazul() ){
								push_ans(x,y,east);	
								return(true);
							}
							muimui.special.x=tmp_mui_x;
							BLOCK_pointer_swap(&bord[x][y],&bord[tmpx][y]);
						}
				}
				if(0<=x-1 && x+1<N &&temp_bord[x-1][y]&&!bord[x+1][y]){//west
					for(tmpx=x+1;tmpx<N&&!bord[tmpx+1][y];tmpx++);
						if(tmpx>=N){ tmpx=N-1; }
						if(tmpx<N){
						 	BLOCK_pointer_swap(&bord[x][y],&bord[tmpx][y]);
							muimui.special.x=tmpx-1;
							if(garder_pazul() ){
								push_ans(x,y,west);	
								return(true);
							}
							muimui.special.x=tmp_mui_x;
							BLOCK_pointer_swap(&bord[x][y],&bord[tmpx][y]);
						}
				}
				if(0<=y-1 && y+1<N &&temp_bord[x][y+1]&&!bord[x][y-1]){//south
					for(tmpy=y-1;tmpy>=0&&!bord[x][tmpy-1];tmpy--);
						if(tmpy<0){ tmpy=0; }
						if(tmpy>=0){ 	
							BLOCK_pointer_swap(&bord[x][y],&bord[x][tmpy]);
							muimui.special.y=tmpy+1;
							if(garder_pazul() ){
								push_ans(x,y,south);	
								return(true);
							}
							muimui.special.y=tmp_mui_y;
							BLOCK_pointer_swap(&bord[x][y],&bord[x][tmpy]);
						}
				}
				if(0<=y-1 && y+1<N &&temp_bord[x][y-1]&&!bord[x][y+1]){//north
					for(tmpy=y+1;tmpy<N&&!bord[x][tmpy+1];tmpy++);
						if(tmpy>=N){ tmpy=N-1; }
						if(tmpy<N){
						 	BLOCK_pointer_swap(&bord[x][y],&bord[x][tmpy]);
							muimui.special.y=tmpy-1;
							if(garder_pazul() ){
								push_ans(x,y,north);	
								return(true);
							}
							muimui.special.y=tmp_mui_y;
							BLOCK_pointer_swap(&bord[x][y],&bord[x][tmpy]);
						}
				}
			}
		}
	for(i=0;i<N;i++){ free(temp_bord[i]); }
	free(temp_bord);

	return(false);
}
int main(void)
{
	ANS *temp;
	fp=fopen("toi","r");
	init_flower_list();
	init_ans_stack();
	scan_map();
	if(garder_pazul()){
		for(temp=pop_ans();temp!=NULL;temp=pop_ans()){
			printf("(%d,%d,",temp->x,temp->y);
			switch(temp->direction){
				case east:printf("east");break;
				case west:printf("west");break;
				case south:printf("south");break;
				case north:printf("north");break;
			}
			printf(")\n");
			free(temp);
		}
	}else{
		printf("srroy fault ans...\n");
	}
	
	return(0);
}
