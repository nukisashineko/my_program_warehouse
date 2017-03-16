/*
***trump***
spades (♠), hearts (♥), diamonds (♦) and clubs (♣)
****full_riffle_shuffle*****
山札を作る
フルリフルシャッフルをする
出力終了
***:full_riffle_shuffle:****
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define CARD_MAX 52
#define NUM_MAX 13
#define MARK_MAX 4


typedef enum{spades=0,hearts,diamond,club} MARK_TYPE;
typedef enum{none=0,decision,select,left,right} SW_TYPE;

typedef struct trump_card{
int num;
MARK_TYPE mark;
} CARD;
void
file_clear(void)
{
FILE *fp;
fp=fopen("card_date.txt","w");
fclose(fp);
}
void
print_deck(CARD trump[CARD_MAX])
{
int i;
FILE *fp;
//spades (♠), hearts (♥), diamonds (♦) and clubs (♣)
char seem_mark[MARK_MAX+1][10]={"spade","heart","diamond","club","none"};
fp=fopen("card_date.txt","a");
for(i=0;i<CARD_MAX;i++)
fprintf(fp,"num=%d,\tmark=%s\n",trump[i].num,seem_mark[trump[i].mark]);
fprintf(fp,"\n");
fclose(fp);
return;
}
deck_cp(CARD *deck_copy,CARD *deck)
{
int i;
CARD temp_deck[CARD_MAX];
for(i=0;i<CARD_MAX;i++){
(*(deck_copy+i)).num=(*(deck+i)).num;
(*(deck_copy+i)).mark=(*(deck+i)).mark;
}
return;
}

void
init_deck(CARD *deck)
{

int i,j;
for(i=0;i<MARK_MAX;i++)
for(j=0;j<NUM_MAX;j++){
(*(deck+i*NUM_MAX+j)).num=j+1;
(*(deck+i*NUM_MAX+j)).mark=i;
}
return;
}

void
full_riffle_shuffle(CARD *deck)
{
int i,j;
CARD temp_deck[CARD_MAX];
deck_cp(temp_deck,deck);
for(i=0,j=0;i<CARD_MAX/2;i++,j+=2){
(*(deck+j))=temp_deck[i];
(*(deck+j+1))=temp_deck[CARD_MAX/2+i];
}
return;
}

void
riffle_shuffle(CARD *deck)
{
int i,j,k,temp;
CARD temp_deck[CARD_MAX];

	srand((unsigned)time(NULL));
deck_cp(temp_deck,deck);
for(i=0,j=CARD_MAX/2,k=0;i<CARD_MAX/2&&j<CARD_MAX;){
for(temp=i+rand()%4/*,printf("i=%d,",temp-i)*/;i<temp&&i<CARD_MAX/2;i++,k++)
{
(*(deck+k))=temp_deck[i];
// printf("num=%d,\tmark=%d\n",deck[i].num,deck[i].mark);
}
for(temp=j+rand()%4/*,printf("j=%d\n",temp-j)*/;j<temp&&j<CARD_MAX;j++,k++)
{
(*(deck+k))=temp_deck[j];
// printf("num=%d,\tmark=%d\n",deck[j].num,deck[j].mark);
}
}
for(;i<CARD_MAX/2;i++,k++)
(*(deck+k))=temp_deck[i];
for(;j<CARD_MAX;j++,k++)
(*(deck+k))=temp_deck[j];
return;
}
SW_TYPE
get_sw(void){
	char c;
	SW_TYPE flag;
	c=getchar();
	swhich(c){
		case'z':flag=decision;break;
		case'x':flag=select	;break;
		case'c':flag=left	;break;
		case'v':flag=right	;break;
		default:flag=none	;break;
	}
	return(flag);
}
int
main(void)
{
int i,j,temp,n;
CARD deck[CARD_MAX];
CARD temp_deck[CARD_MAX];

file_clear();
for(i=0;i<8;i++)
	printf("%d %d",i,get_sw());

//clear value
for(i=0;i<CARD_MAX;i++){
deck[i].num=0;
deck[i].mark=MARK_MAX;
}
//
init_deck(deck);
for(i=0,n=rand()%10+4;i<n;i++)
	riffle_shuffle(deck);

//game_black_jack
//sw=decision,select,left,right
//typedef enum{none,decision,select,left,right} SW_TYPE;
//when start flag=low,count=0

new_card=draw_a_card();
while(1){
get_sw();
//printf("\t%d Is next number \n\t    high or low?")
if(decision){
	old_card=new_card;
	new_card=draw_a_card();
	if(  flag=low && new_num<=old_num 
	   ||flag=high && old_num<=new_num){
		count++;
	printf("you win !!");
	}else{
	printf("you lose !!");
		if(gameover()) break;
	}
}
//else if(select){} //not used this game
else if(left){
	flag=low;
}
else if(right){
	flag=high;
}
}
//
//voidgame over()

printf("game over!!\(^ω^)/\n");
printf("you wonld retry ?");
flag=get_flag();
//return (flag);

//
print_deck(deck);
return;
}


//hindu_shuffle
/*
deck_cp(temp_deck,deck);
for(i=0,temp=0;i<CARD_MAX;i=temp,temp=i+(rand()%10))
{
if(temp>CARD_MAX){ temp=CARD_MAX; }//over write gard 
for(j=temp;i<j;j--)
{
printf("%d %d %d %d \n",temp,i,j-1,CARD_MAX-j);
deck[i]=temp_deck[j-1];
}
}*/
//
//	printf("%d %d %d\n",trump.num,trump.mark,n);


/*

switch((sw=get_sw())){
		case decision_sw:
			break;
		case select_sw:
			break;
		case left_sw	:
			break;
		case right_sw	:
			break;
		default:
			break;
}
*/

