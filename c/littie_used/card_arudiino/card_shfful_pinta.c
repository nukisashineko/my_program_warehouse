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

typedef struct trump_card{
int num;
MARK_TYPE mark;
struct trump_card *next;
} CARD;

void file_clear(void);
void print_deck(CARD *);
void init_deck(CARD *deck);
void riffle_shuffle(CARD *deck);
void malloc_deck(CARD **,int *,int);

void
file_clear(void)
{
FILE *fp;
fp=fopen("card_date.txt","w");
fclose(fp);
}
void
print_deck(CARD *trump)
{
int count=0 ;
FILE *fp;
char seem_mark[MARK_MAX+1][10]={"spade","heart","diamond","club","none"};
fp=fopen("card_date.txt","a");
for(;trump;trump=trump->next){
fprintf(fp,"%d\tnum=%d,\tmark=%s\n",count++,trump->num,seem_mark[trump->mark]);
fprintf(fp,"\n");
}
fclose(fp);
return;
}


void
init_deck(CARD *deck)
{
int i,j;
for(i=0;deck && i<MARK_MAX;i++)
for(j=0;deck && j<NUM_MAX;j++,deck=deck->next){
deck->num=j+1;
deck->mark=i;
}
return;
}

void
full_riffle_shuffle(CARD **deck_top,int deck_lugth)
{
int i;
CARD *deck_high,*deck_low,*trump;

deck_high=trump=*deck_top;
*deck_top=NULL;
for(i=0;i<deck_lugth/2-1;i++)//trump=deck_high.end
	trump=trump->next;
deck_low=trump->next;
printf("%d %d %d %d ;n %d %d %d %d\n",deck_high->num,deck_high->mark,deck_low->num,deck_low->mark,deck_high->next->num,deck_high->next->mark,deck_low->next->num,deck_low->next->mark);
printf("%d %d %p\n",trump->num,trump->mark,trump->next,);
trump->next=NULL;

for(;deck_low || deck_high;){
	if(deck_high){
	printf("high %d %d  ;n %d %d\n",deck_high->num,deck_high->mark,deck_high->next->num,deck_high->next->mark);
		trump=deck_high;
		deck_high=deck_high->next;
		if(*deck_top!=NULL)
		trump->next=*deck_top;
		else
		trump->next=NULL;
		*deck_top=trump;
	}
	if(deck_low){
	printf("low %d %d  ;n %d %d\n",deck_low->num,deck_low->mark,deck_low->next->num,deck_low->next->mark);
		trump=deck_high;
		deck_low=deck_low->next;
		if(*deck_top!=NULL)
		trump->next=*deck_top;
		else
		trump->next=NULL;
		*deck_top=trump;
	}
}
return;
}

void
riffle_shuffle(CARD *deck)
{
return;
}

void
malloc_deck(CARD **deck_top,int *deck_lugth,int n){

int i;
CARD *temp_trump=NULL;

for(i=0;i<n;i++){
temp_trump=(CARD *)malloc(sizeof(CARD));
if(!temp_trump){fprintf(stderr,"end becuase can't malloc \n");exit(1);}
temp_trump->num=0;
temp_trump->mark=MARK_MAX;//mark=none
temp_trump->next=*deck_top;
*deck_top=temp_trump;
(*deck_lugth)++;
}
return;
}

int
main(void)
{
int i,j,temp;
CARD *deck_top=NULL;
CARD *temp_trump=NULL;
int deck_lugth=0;

file_clear();
malloc_deck(&deck_top,&deck_lugth,CARD_MAX);

init_deck(deck_top);
//hindu_shuffle
//
full_riffle_shuffle(&deck_top,deck_lugth);
print_deck(deck_top);
//printf("%d\n",deck_lugth);
return;
}

