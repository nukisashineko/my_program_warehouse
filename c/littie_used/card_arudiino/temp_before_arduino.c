#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
/* <stdbool.h> */
#define bool char
#define true 1
#define false 0
#define __bool_true_false_are_defined 1
/*\<stdbool.h>*/

#define CARD_MAX 52
#define NUM_MAX 13
#define MARK_MAX 4
#define PRINT_LINE_MAX 17
#define temp_string_MAX 30
#define SPACE_MAX "                "

char seem_num[14][3]={"0","A","2","3","4","5","6","7","8","9","0","J","Q","K"};
char seem_mark[MARK_MAX+1][10]={"s","h","d","c","n"};
char ranking_number[NUM_MAX+1]={0,2,1,13,12,11,10,9,8,7,6,5,4,3};
typedef enum{five_of_a_kind=1,royal_flush,straight_flush,
		four_of_a_kind,full_house,flush,straight,
		three_of_a_kind,two_pairs,one_pair,no_pair,no} RANKING_HAND;
typedef enum{spades=0,hearts,diamond,club,nomark} MARK_TYPE;
typedef enum{none=0,decision_sw,select_sw,left_sw,right_sw} SW_TYPE;
typedef enum {low=0,high} EXPECTATION;
typedef struct trump_card{
	int num;
	MARK_TYPE mark;
} CARD;

//char get_sw(void);
void stop_print(void);
//void file_clear(void);
void deck_clear(CARD *deck,int n);
//void print_deck(CARD trump[CARD_MAX]);
void deck_cp(CARD *deck_copy,CARD *deck);
SW_TYPE get_sw(void);
bool game_start(const char *expreination);
bool which_expreination_A_B(const char *expreination,const char *A,const char *B);
void riffle_shuffle(CARD *deck);
bool game_over(void);
CARD draw_a_card(CARD *deck,int *n);
int add_hand(CARD *hand,int *hand_n,CARD *deck,int *deck_n);
int discard_and_draw(CARD *hand,int i,CARD *deck,int *deck_n);
void init_deck(CARD *deck);
void game_HIGH_LOW(void);
int hand_card_sum(CARD *hand,int hand_n);
void game_black_jack(void);
char* from_RANK_to_string(RANKING_HAND flag);
RANKING_HAND Is_this_hand_rank(CARD *hand);
void poker_com_AI(CARD *hand,bool *select_place,RANKING_HAND com_flag);
void game_poker(void);
//void discard(CARD *hand,int *hand_n,int i);
//void discard_to_field(CARD *field,int *field_n,CARD *hand,int *hand_n,bool *select_place);
//void hand_card_simsel_sort(CARD *hand,int hand_n)
//bool exists_select_place(bool *select_place,int n);
//bool can_card_discard(CARD *field,int field_n,char select_count,char select_number);
//void game_poverty(void);

//arudino_function()
//#define lcd.print puts
//#define lcd_setCursor lcd.setCursor
SW_TYPE get_sw(void);
void
lcd_setCursor(int x, int y){ return; }
void
stop_print(void){
//	while(!(SW_TYPE)get_sw());
}
//		


/*
void
file_clear(void)
{
	FILE *fp;
	fp=fopen("card_date.txt","w");
	fclose(fp);
}
*/
void
deck_clear(CARD *deck,int n)
{
	int i;
	for(i=0;i<n;i++){
		(*(deck+i)).num=0;
		(*(deck+i)).mark=MARK_MAX;
	}
	return;

}
/*
void
print_deck(CARD trump[CARD_MAX])
{
int i;
FILE *fp;
//spades (♠), hearts (♥), diamonds (♦) and clubs (♣)
//char seem_mark[MARK_MAX+1][10]={"spade","heart","diamond","club","none"};
fp=fopen("card_date.txt","a");
for(i=0;i<CARD_MAX;i++)
fprintf(fp,"num=%d,\tmark=%s\n",trump[i].num,seem_mark[trump[i].mark]);
fprintf(fp,"\n");
fclose(fp);
return;
}
*/
void
deck_cp(CARD *deck_copy,CARD *deck)
{
	int i;
	for(i=0;i<CARD_MAX;i++){
		(*(deck_copy+i)).num=(*(deck+i)).num;
		(*(deck_copy+i)).mark=(*(deck+i)).mark;
	}
	return;
}

SW_TYPE
get_sw(void){
	char c;
	SW_TYPE flag;
	while((c=getchar())=='\n');
	switch(c){
		case'z':flag=decision_sw;	break;
		case'x':flag=select_sw;	break;
		case'c':flag=left_sw;	break;
		case'v':flag=right_sw;	break;
		default:flag=none;		break;
	}
	return(flag);
}

bool
game_start(const char *expreination){
	SW_TYPE sw;
	lcd_setCursor(0,0);
	puts(expreination);
	lcd_setCursor(0,1);
	puts("   [*start]    ");
	for(sw=(SW_TYPE)get_sw();;sw=(SW_TYPE)get_sw()){
		switch(sw){
			case decision_sw:	return(true); break;
			case select_sw:	return(false);break;
			default:				break;
		}		
	}
}

bool
which_expreination_A_B(const char *expreination,const char *A,const char *B)
{
	char side_speace[10],middle_speace=2,print_line[PRINT_LINE_MAX];
	short int length_A,length_B,length_speace,i;
	SW_TYPE flag=none,old_flag;
	length_A=strlen(A)+1;
	length_B=strlen(B)+1;
	length_speace=(16-(length_A+length_B+middle_speace))/2;	
	for(i=0;i<length_speace;i++)
		side_speace[i]=' ';
	side_speace[i]='\0';
	while(1){
		if( (old_flag==left_sw ||old_flag==right_sw) && flag==decision_sw){ break; }
		sprintf(print_line,"%s",expreination);
		lcd_setCursor(0,0);
		puts(print_line);
		sprintf(print_line,"%s%c%s%s%c%s%s",
			side_speace,(flag==left_sw)?'*':' ',A,"  ",(flag==right_sw)?'*':' ',B,side_speace);
		lcd_setCursor(0,1);
		puts(print_line);
		old_flag=flag;
		flag=(SW_TYPE)get_sw();
		if(flag==select_sw ||flag==none){ flag=old_flag; }
	}
	lcd_setCursor(0,0);
	puts(SPACE_MAX); 
	lcd_setCursor(0,1);
	puts(SPACE_MAX);
	return(((old_flag==left_sw)?true:false));
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

bool
game_over(void){
	lcd_setCursor(0,0);
	puts("GameOver \\(^ω^)/");
	lcd_setCursor(0,1);
	puts(SPACE_MAX);
	stop_print();
	return (which_expreination_A_B("you wonld retry?","yes","no"));
}

CARD
draw_a_card(CARD *deck,int *n)
{
	(*n)++;
	return(*(deck+*n-1));
}

int
add_hand(CARD *hand,int *hand_n,CARD *deck,int *deck_n)
{
	(*(hand+*hand_n))=draw_a_card(deck,deck_n);
	(*hand_n)++;

	return((*(hand+*hand_n-1)).num);
}
int
discard_and_draw(CARD *hand,int i,CARD *deck,int *deck_n)
{
	(*(hand+i))=draw_a_card(deck,deck_n);
	return((*(hand+i)).num);
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

//game_black_jack
//sw=decision,select,left,right
//typedef enum{none,decision,select,left,right} SW_TYPE;
//when start flag=low,count=0
void
game_HIGH_LOW(void)
{
	int i,n,count=0;
	CARD deck[CARD_MAX];
	CARD old_card,new_card;
	EXPECTATION flag=low;
	char print_line[PRINT_LINE_MAX];
	init_deck(deck);
	if(!game_start("game_HIGH_LOW")) return;
	while(1){
		for(i=0,n=rand()%10+4;i<n;i++)
			riffle_shuffle(deck);

		n=0;
		new_card=draw_a_card(deck,&n);
//		print_deck(deck);

		while(1){
			sprintf(print_line,"now %s-%s Is next?",seem_mark[new_card.mark],seem_num[new_card.num]);
			old_card=new_card;
			new_card=draw_a_card(deck,&n);
			flag=(which_expreination_A_B(print_line,"high","low"))?high:low;
			if(	(flag==high && old_card.num<=new_card.num)
			    || (flag==low && new_card.num<=old_card.num)	){
					count++;
				sprintf(print_line,"you win !! count=%d",count);
				lcd_setCursor(0,0);
				puts(print_line);
				stop_print();
			}else{
				sprintf(print_line,"you lose !! count=%d",count);
				lcd_setCursor(0,0);
				puts(print_line);
				stop_print();
				count=0;
				if(!game_over())return;
				else		break;
			}
		}
	}

}
#define BLACK_JACK 21
#define PLAYERS_HAND_MAX_SMALL 5
int
hand_card_sum(CARD *hand,int hand_n){
	int sum,i,A_count=0;
		for(i=sum=0;i<hand_n;i++){
			if(10<(*(hand+i)).num){
				sum+=10;
			}else if((*(hand+i)).num==1){
				A_count++;
			}else{
				sum+=(*(hand+i)).num;
			}
		}
		for(;A_count;A_count--){
			if(sum<=BLACK_JACK-11){
				sum+=11;
			}else{
				sum+=1;
			}
		}
	return(sum);
}

void
game_black_jack(void)
{
	int i,n,count=0;
	CARD deck[CARD_MAX];
	CARD your_hand[PLAYERS_HAND_MAX_SMALL];
	CARD com_hand[PLAYERS_HAND_MAX_SMALL];
	int com_n,your_n;//count hand
	int com_sum,your_sum;//hands sum number
	char print_line[PRINT_LINE_MAX]={""};

	init_deck(deck);
	if(!game_start("game_black_jack"))return;
	while(1){
		com_n=your_n=n=0;
		deck_clear(your_hand,PLAYERS_HAND_MAX_SMALL);	
		deck_clear(com_hand,PLAYERS_HAND_MAX_SMALL);	
	
//shuffle
		for(i=0,n=rand()%20+4;i<n;i++)
			riffle_shuffle(deck);
//
//com_turn
		for(com_sum=0;com_sum<BLACK_JACK-3 && com_n<PLAYERS_HAND_MAX_SMALL;){
			add_hand(com_hand,&com_n,deck,&n);
			com_sum=hand_card_sum(com_hand,com_n);
		}
			sprintf(print_line,"com's draw %d",com_n);
				lcd_setCursor(0,0);
				puts(print_line);
				lcd_setCursor(0,0);
				puts(SPACE_MAX); 
				lcd_setCursor(0,1);
				puts(SPACE_MAX);
				stop_print();
//
//your_turn
		your_sum=add_hand(your_hand,&your_n,deck,&n);
		for(;your_sum<BLACK_JACK && your_n<PLAYERS_HAND_MAX_SMALL;){
			sprintf(print_line,"sum%d MoreDraw?",your_sum);
			if(!which_expreination_A_B(print_line,"yes","no")){ break; }
			add_hand(your_hand,&your_n,deck,&n);
				your_sum=hand_card_sum(your_hand,your_n);
			sprintf(print_line,"draw=%s-%s,sum=%d"
				,seem_mark[your_hand[your_n-1].mark],seem_num[your_hand[your_n-1].num],your_sum);
			lcd_setCursor(0,0);
			puts(print_line);
			stop_print();
		}
//
//judge
		sprintf(print_line,"com=%d your=%d",com_sum,your_sum);
			lcd_setCursor(0,0);
			puts(print_line);
		if( BLACK_JACK<your_sum ){
			sprintf(print_line,"you bust !! count=%d",count);
			lcd_setCursor(0,1);
			puts(print_line);
			stop_print();
			count=0;
			if(!game_over())return;
		}else if(your_sum<=BLACK_JACK
			&& (BLACK_JACK<com_sum
			|| (com_sum<=BLACK_JACK && com_sum<your_sum))){
			sprintf(print_line,"you win !! count=%d",++count);
			lcd_setCursor(0,1);
			puts(print_line);
			stop_print();
		}else{
			sprintf(print_line,"you lose !! count=%d",count);
			lcd_setCursor(0,1);
			puts(print_line);
			stop_print();
			count=0;
			if(!game_over())return;
		}
//
	}
}
//
//	typedef enum{five_of_a_kind=1,royal_flush,straight_flush,four_of_a_kind,full_house,flush,straight,three_of_a_kind,two_pairs,one_pair,no_pair,no} RANKING_HAND;
//
char*
from_RANK_to_string(RANKING_HAND flag)
{
	switch(flag){
		case five_of_a_kind:	return("FiveOfAKind");	break;
		case royal_flush:	return("RoyalFlush");	break;
		case straight_flush:	return("StraighFlush");	break;
		case four_of_a_kind:	return("FourOfAKind");	break;
		case full_house:	return("FullHouse");		break;
		case flush:		return("Flush");		break;
		case straight:	return("Straight");		break;
		case three_of_a_kind:return("ThreeOfAKind");	break;
		case two_pairs:	return("TwoPairs");		break;
		case one_pair:	return("OnePair");		break;
		case no_pair:		return("NoPair");		break;
		case no:		return("no");			break;
		default:		return(" ");			break;
	}
}

RANKING_HAND
Is_this_hand_rank(CARD *hand)
{
	int i,j;
	char five_kind,four_kind,three_kind,two_kind;
	int kind[NUM_MAX+1];
	bool flush_flag;
	char num_min=14,num_max=0;//min!=1
	MARK_TYPE mark;
	RANKING_HAND flag=no;
//init
	flush_flag=true;
	five_kind=four_kind=three_kind=two_kind=0;
	for(i=0;i<NUM_MAX+1;i++)
		kind[i]=0;
//
	for(i=0,mark=(*hand).mark;i<PLAYERS_HAND_MAX_SMALL;i++){
		for(j=1;j<NUM_MAX+1;j++){
			if(mark !=(*(hand+i)).mark){ flush_flag=false; }
			if((*(hand+i)).num!=1
			&& (*(hand+i)).num<num_min){ num_min=(*(hand+i)).num; }
			if(num_max<(*(hand+i)).num){ num_max=(*(hand+i)).num; }	
		}
		kind[(*(hand+i)).num]++;
	}
	for(i=0;i<NUM_MAX+1;i++)
	switch(kind[i]){
		case 2: two_kind++;	break;
		case 3: three_kind++;break;
		case 4: four_kind++;	break;
		case 5: five_kind++;	break;
		default:		break;
	}
	if	(five_kind)						{ flag=five_of_a_kind; }
	else if(four_kind)						{ flag=four_of_a_kind; }
	else if(two_kind && three_kind)				{ flag=full_house; }
	else if(three_kind)						{ flag=three_of_a_kind; }
	else if(two_kind==2)						{ flag=two_pairs; }
	else if(two_kind)						{ flag=one_pair; }
	else if(kind[1]==1 && kind[2]==0 
		&& num_max-num_min==3 && flush_flag)		{ flag=royal_flush; }
	else if((num_max-num_min==4 && flush_flag && kind[1]!=1)
	     ||( num_max-num_min==3 && kind[1]==1 && flush_flag)){ flag=straight_flush; }
	else if(flush_flag)						{ flag=flush; }
	else if( (num_max-num_min==4 && kind[1]!=1)
		||( num_max-num_min==3 && kind[1]==1 ))		{ flag=straight; }
	else								{ flag=no_pair; }
	return(flag);
}

void
poker_com_AI(CARD *hand,bool *select_place,RANKING_HAND com_flag)
{
	int i,j;
	int kind[NUM_MAX+1];
	char num_max=0;//min!=1
	int mark_count[MARK_MAX],mark_max;
	char pick_up=0;
//init
	for(i=0;i<NUM_MAX+1;i++)
		kind[i]=0;
	for(i=0;i<MARK_MAX;i++)
		mark_count[i]=0;
	mark_max=0;
//
	for(i=0;i<PLAYERS_HAND_MAX_SMALL;i++){
		for(j=1;j<NUM_MAX+1;j++){
			if(num_max<(*(hand+i)).num){ num_max=(*(hand+i)).num; }	
		}
		mark_count[(*(hand+i)).mark]++;		
		kind[(*(hand+i)).num]++;
	}

	
	switch(com_flag){
		case five_of_a_kind:	break;//none
		case royal_flush:	break;//none
		case straight_flush:	break;//none
		case four_of_a_kind:	//pick_up is four_kind's number
						for(i=0;i<NUM_MAX+1;i++)
							if(kind[i]==4){ pick_up=i; }
						for(i=0;i<PLAYERS_HAND_MAX_SMALL;i++)
							if((*(hand+i)).num!=pick_up){ *(select_place+i)=true; }
					break;
		case full_house:	break;//none
		case flush:		break;//none
		case straight:	break;//none
		case three_of_a_kind:	//pick_up is three_kind's number
						for(i=0;i<NUM_MAX+1;i++)
							if(kind[i]==3){ pick_up=i; }
						for(i=0;i<PLAYERS_HAND_MAX_SMALL;i++)
							if((*(hand+i)).num!=pick_up){ *(select_place+i)=true; }
					break;
		case two_pairs:	//pick_up is not pair's number
						for(i=0;i<NUM_MAX+1;i++)
							if(kind[i]==1){ pick_up=i; }
						for(i=0;i<PLAYERS_HAND_MAX_SMALL;i++)
							if((*(hand+i)).num==pick_up){ *(select_place+i)=true; }
					break;
		case one_pair:	//pick_up is one_pair's number
						for(i=0;i<NUM_MAX+1;i++)
							if(kind[i]==2){ pick_up=i; }
						for(i=0;i<PLAYERS_HAND_MAX_SMALL;i++)
							if((*(hand+i)).num!=pick_up){ *(select_place+i)=true; }
					break;
		case no_pair:		//pick_up is most mark_count's mark
						for(i=0;i<MARK_MAX;i++)
							if( mark_max < mark_count[i] ){
								 mark_max=mark_count[i]; pick_up=i;
							}
						for(i=0;i<PLAYERS_HAND_MAX_SMALL;i++)
							if((int)(*(hand+i)).mark!=pick_up){ *(select_place+i)=true; }
					break;
		case no:		//this is error
								lcd_setCursor(0,0);
								puts("error flag is no");exit(1);

					break;
	}
	return;
}

void
game_poker(void)
{
	int i,n,count=0;
	CARD deck[CARD_MAX];
	CARD your_hand[PLAYERS_HAND_MAX_SMALL];
	CARD com_hand[PLAYERS_HAND_MAX_SMALL];
	int com_n,your_n;//count hand
	char print_line[PRINT_LINE_MAX]={""};
	char temp_string[temp_string_MAX]={""};
	bool select_place[PLAYERS_HAND_MAX_SMALL];
	RANKING_HAND your_flag,com_flag;
	bool while_end_flag;
	unsigned char current;
	SW_TYPE sw=none;

	if(!game_start("   game_poker   "))return;
	while(1){
//init	
		init_deck(deck);

		com_n=your_n=n=0;
		deck_clear(your_hand,PLAYERS_HAND_MAX_SMALL);	
		deck_clear(com_hand,PLAYERS_HAND_MAX_SMALL);
		for(i=0,n=rand()%20+4;i<n;i++)
			riffle_shuffle(deck);
//
	
//com_draw
		for(i=0;i<PLAYERS_HAND_MAX_SMALL;i++)
			add_hand(com_hand,&com_n,deck,&n);	
//
//your_draw
		for(i=0;i<PLAYERS_HAND_MAX_SMALL;i++)
			add_hand(your_hand,&your_n,deck,&n);

//	this is royal_flush when you want to show royal.
//		your_hand[0].num=1;
//		your_hand[1].num=13;
//		your_hand[2].num=12;
//		your_hand[3].num=11;
//		your_hand[4].num=10;

//
//com_select
	//init
		for(i=0;i<PLAYERS_HAND_MAX_SMALL;i++)
		select_place[i]=false;
		com_flag=Is_this_hand_rank(com_hand);
		current=6;
	//
		poker_com_AI(com_hand,select_place,com_flag);

			sprintf(print_line,"com %s",from_RANK_to_string(com_flag));
			lcd_setCursor(0,0);
			puts(print_line);
			for(i=0,temp_string[0]='\0';i<PLAYERS_HAND_MAX_SMALL;i++){
				strcat(temp_string,	(current==i && select_place[i])?"$":
							(current==i)?"*":
							(select_place[i])?"+":" ");
				strcat(temp_string,"%s%s");
			}
	
			sprintf(print_line,temp_string
				,seem_mark[com_hand[0].mark],seem_num[com_hand[0].num]
				,seem_mark[com_hand[1].mark],seem_num[com_hand[1].num]
				,seem_mark[com_hand[2].mark],seem_num[com_hand[2].num]
				,seem_mark[com_hand[3].mark],seem_num[com_hand[3].num]
				,seem_mark[com_hand[4].mark],seem_num[com_hand[4].num]
			);
			lcd_setCursor(0,1);
			puts(print_line);
			stop_print();
//
//com_descard_and_draw
		for(i=0;i<PLAYERS_HAND_MAX_SMALL;i++){
			if(select_place[i])
				discard_and_draw(com_hand,i,deck,&n);
		}

//
//your_select
	//init
		for(i=0;i<PLAYERS_HAND_MAX_SMALL;i++)
		select_place[i]=false;
		while_end_flag=true;
		your_flag=Is_this_hand_rank(your_hand);
		current=2;
	//
		while(while_end_flag){
			sprintf(print_line,"you %s",from_RANK_to_string(your_flag));
			lcd_setCursor(0,0);
			puts(print_line);
			for(i=0,temp_string[0]='\0';i<PLAYERS_HAND_MAX_SMALL;i++){
				strcat(temp_string,	(current==i && select_place[i])?"$":
							(current==i)?"*":
							(select_place[i])?"+":" ");
				strcat(temp_string,"%s%s");
			}
	
			sprintf(print_line,temp_string
				,seem_mark[your_hand[0].mark],seem_num[your_hand[0].num]
				,seem_mark[your_hand[1].mark],seem_num[your_hand[1].num]
				,seem_mark[your_hand[2].mark],seem_num[your_hand[2].num]
				,seem_mark[your_hand[3].mark],seem_num[your_hand[3].num]
				,seem_mark[your_hand[4].mark],seem_num[your_hand[4].num]
			);
			lcd_setCursor(0,1);
			puts(print_line);
			switch((sw=(SW_TYPE)get_sw())){
					case decision_sw:
						while_end_flag=false;
						break;
					case select_sw:
						if(select_place[current]==true)
							select_place[current]=false;
						else
							select_place[current]=true;
						break;
					case left_sw	:
						if(0<current)
							current--;
						break;
					case right_sw	:
						if(current<PLAYERS_HAND_MAX_SMALL-1)
							current++;
						break;
					default:
						break;
			}
		}
//
//your_descard_and_draw
		for(i=0;i<PLAYERS_HAND_MAX_SMALL;i++){
			if(select_place[i])
				discard_and_draw(your_hand,i,deck,&n);
		}
//
//print_each_other
		sprintf(print_line,"your %s%s%s%s%s%s%s%s%s%s"
			,seem_mark[your_hand[0].mark],seem_num[your_hand[0].num]
			,seem_mark[your_hand[1].mark],seem_num[your_hand[1].num]
			,seem_mark[your_hand[2].mark],seem_num[your_hand[2].num]
			,seem_mark[your_hand[3].mark],seem_num[your_hand[3].num]
			,seem_mark[your_hand[4].mark],seem_num[your_hand[4].num]
		);
		lcd_setCursor(0,0);
		puts(print_line);
		sprintf(print_line,"com  %s%s%s%s%s%s%s%s%s%s"
			,seem_mark[com_hand[0].mark],seem_num[com_hand[0].num]
			,seem_mark[com_hand[1].mark],seem_num[com_hand[1].num]
			,seem_mark[com_hand[2].mark],seem_num[com_hand[2].num]
			,seem_mark[com_hand[3].mark],seem_num[com_hand[3].num]
			,seem_mark[com_hand[4].mark],seem_num[com_hand[4].num]
		);
		lcd_setCursor(0,1);
		puts(print_line);
		stop_print();
//
//judge
		com_flag=Is_this_hand_rank(com_hand);
		your_flag=Is_this_hand_rank(your_hand);
		sprintf(print_line,"you %s",from_RANK_to_string(your_flag));
		lcd_setCursor(0,0);
		puts(print_line);
		sprintf(print_line,"com %s",from_RANK_to_string(com_flag));
		lcd_setCursor(0,1);
		puts(print_line);
		stop_print();
		if	(your_flag == com_flag){
			sprintf(print_line,"draw !! win=%d",count);
			lcd_setCursor(0,1);
			puts(print_line);
			stop_print();
		}else if(com_flag  < your_flag){
			sprintf(print_line,"lost!! win=%d",count);
			lcd_setCursor(0,1);
			puts(print_line);
			stop_print();
			count=0;
			if(!game_over())return;
		}else if(your_flag  < com_flag){
			sprintf(print_line,"win !! win=%d",++count);
			lcd_setCursor(0,1);
			puts(print_line);
			stop_print();
		}
	}
//
}

//show

#define COMPUTER_MEMBER 3
#define PLAYERS_HAND_MAX_BIG 52/4+1
// this +1 value is joker speace

void
discard(struct trump_card *hand,int *hand_n,int i)
{
	for(;i<*hand_n-1;i++){
		*(hand+i)=*(hand+i+1);
	}
	(*(hand+*hand_n-1)).num=0;
	(*(hand+*hand_n-1)).mark=nomark;
	(*hand_n)--;
	return;
}

void
discard_to_field(struct trump_card *field,int *field_n,struct trump_card *hand,int *hand_n,bool *select_place){
	int i;
	*field_n=0;
	for(i=0;i<PLAYERS_HAND_MAX_BIG;i++)
		if(*(select_place+i)){
			add_hand(field,field_n,hand,&i);
			i--;
		}
	for(i=PLAYERS_HAND_MAX_BIG-1;0<=i;i--)
		if(*(select_place+i)){
			discard(hand,hand_n,i);
		}
for(i=0;i<*field_n;i++)
//printf("discard_to_field %s%s\n",seem_mark[field[i].mark],seem_num[field[i].num]);
	return;
}


void hand_card_simsel_sort(struct trump_card *hand,int hand_n)
{
	int i,j,k,max;
	CARD temp;

	for(i=0;i<(hand_n-1);i++){
		max=ranking_number[(*(hand+i)).num];
		k=i;
		for(j=i+1;j<hand_n;j++){
			if(max<ranking_number[(*(hand+j)).num]){
			max=ranking_number[(*(hand+j)).num];
			k=j;
			}
		}
	temp=*(hand+i);
	*(hand+i)=*(hand+k);
	*(hand+k)=temp;
	}
}

bool
exists_select_place(bool *select_place,int n)
{
	int i;
	for(i=0;i<n;i++)
		if(*(select_place+i))
			break;
	return((i<n)?true:false);
}

bool
can_card_discard(struct trump_card *field,int field_n,char select_count,char select_number)
{
//printf("field_n=%d\n",field_n);
	if(field_n!=0 && (int)select_count!=field_n ){
//puts("select_count!=field_n");
	}else if(field_n!=0 && !(ranking_number[(unsigned char)select_number]<ranking_number[(*field).num]) ){//ranking number is strong lower than high
//printf("%d[%d]<%d[%d]\n",ranking_number[(unsigned char)select_number],select_number,ranking_number[(*field).num],(*field).num);
	}else{
//puts("sccuss!!");
		return(true);
	}
	return(false);
}

#define FIELD_SIZE 4
//search from hand by number 
//return false is no mach hand
bool
select_permutation_creat_new_select(struct trump_card*field,int field_n,struct trump_card *hand,int hand_n,bool *select_place)
{
	int i,j;
	int  temp_place_n;
	bool temp_select_place[MARK_MAX];
	CARD *temp_select_cards[MARK_MAX];
	char masc[MARK_MAX+1]={0x0,0x1,0x3,0x7,0xf};
	bool flag;
	char select_count;
	char select_number;

	//init	
	flag=false;
	temp_place_n=0;
	for(i=0;i<MARK_MAX;i++){
		temp_select_place[i]=false;
		temp_select_cards[i]=NULL;
	}
	for(i=0;i<hand_n;i++){
//printf("%d",*(select_place+i));
		if(*(select_place+i)==true){
			select_number=(*(hand+i)).num;
			temp_select_cards[temp_place_n]=(hand+i);
			temp_place_n++;
		
		}
	}
//puts("");
//puts("init end");
//printf("masc %d,temp_place_n %d,select_number %d,hand_n %d\n",masc[temp_place_n],temp_place_n,select_number,hand_n);
//for(i=0;temp_select_cards[i]&&i<MARK_MAX;i++){
//	printf("%s%s,",seem_mark[temp_select_cards[i]->mark],seem_num[temp_select_cards[i]->num]);
//}
//puts("");
	//
	for(i=masc[temp_place_n],select_count=0;i;select_count=0,i--){
		if(0x1&(i>>0)){ temp_select_place[0]=true; select_count++; }
		if(0x1&(i>>1)){ temp_select_place[1]=true; select_count++; } 
		if(0x1&(i>>2)){ temp_select_place[2]=true; select_count++; }
		if(0x1&(i>>3)){ temp_select_place[3]=true; select_count++; }
//printf("select %d,next %d,%d%d%d%d \n",select_count,i&masc[temp_place_n],0x1&(i>>3),0x1&(i>>2),0x1&(i>1),0x1&(i>>0));
		if(can_card_discard(field,field_n,select_count,select_number)){
			flag=true;
			break;
		}
		for(j=0;j<MARK_MAX;j++)
			temp_select_place[j]=false;
	}	
	if(flag){
		for(i=0;i<temp_place_n;i++)
		if(temp_select_place[i]==false)
			for(j=0;j<PLAYERS_HAND_MAX_BIG;j++){
				if((hand+j)==(temp_select_cards[i])){
					*(select_place+j)=false;
			
				}
			}
	}else{
		for(j=0;j<PLAYERS_HAND_MAX_BIG;j++)
				*(select_place+j)=false;
	}
	return(flag);
}
bool
select_from_number(struct trump_card *field,int field_n,int number,struct trump_card *hand,int hand_n,bool *select_place)
{
	int i;
	bool flag=false;
	bool flag_selsect=false;
//printf("number is %d on select_from_number\n",number);
	for(i=0;i<PLAYERS_HAND_MAX_BIG;i++){
		*(select_place+i)=false;
	}
	for(i=0;i<hand_n;i++)
		if((*(hand+i)).num==number){
			flag_selsect=*(select_place+i)=true;
		}
	if(flag_selsect && select_permutation_creat_new_select(field,field_n,hand,hand_n,select_place))
		flag=true;
	return(flag);
}
#define EQUAL_STRONG_CAND(trump_num) (ranking_number[trump_num]==1||ranking_number[trump_num]==2||ranking_number[trump_num]==3||8==trump_num)
bool
poverty_com_AI(struct trump_card *field,int field_n,struct trump_card *hand,int hand_n,bool *select_place)
{
	int i,j;
	char hand_number_count[NUM_MAX+1];
	bool fainal_flag;
	bool non_pair_flag;
	bool pass_flag;
	bool flag;
	bool discard_pair_flag;

	//init
	for(i=0;i<NUM_MAX+1;i++)
		hand_number_count[i]=0;
	for(i=0;i<hand_n;i++)
		for(j=1;j<NUM_MAX+1;j++)
			if( (*(hand+i)).num==j)
				hand_number_count[j]++;
	for(discard_pair_flag=non_pair_flag=flag=i=0;i<NUM_MAX;i++)
		if(!EQUAL_STRONG_CAND(i)){
			if(hand_number_count[i]!=0)flag++;
			if(hand_number_count[i]==1)non_pair_flag++;
			if(!field_n && hand_number_count[i]==field_n) discard_pair_flag++;
		}
	fainal_flag=(flag<2)?true:false;
	pass_flag=false;
//puts("init end of AI");
	//
	if(fainal_flag){//if near finanal
//puts("near fainal");
//puts("discard strong_card");
		for(i=3,flag=false;!flag&&1<=i;i--){//discard strong_card
			flag=select_from_number(field,field_n,ranking_number[i],hand,hand_n,select_place); 
		}if(i<1&&!select_from_number(field,field_n,8,hand,hand_n,select_place)){//discard 8
//puts("discard other one");
			for(i=0;i<NUM_MAX+1;i++)// discard other one
				if(hand_number_count[i]){
//printf("hand_number_count[%d]  true",i);
					if(select_from_number(field,field_n,i,hand,hand_n,select_place))	
						break;
				}
			if(NUM_MAX+1<=i)//can't discard hand
				pass_flag=true;
		}
	}else if(!non_pair_flag || discard_pair_flag){//from weak number to strong number
//puts("from weak number to strong number");
		if(field_n<2){
			i=-1; 
		}else {
			for(i=NUM_MAX-1;i>=0;i--){
				if(hand_number_count[(unsigned char)ranking_number[i]]
				&& select_from_number(field,field_n,ranking_number[i],hand,hand_n,select_place))
					break;
			}
		}
		if(i<0)//can't discard hand
				pass_flag=true;
	}else{//if exists not pair  card
//puts("exists non pair");
		pass_flag=true;
		for(i=0;i<NUM_MAX/2-1;i++){
		if(!EQUAL_STRONG_CAND(7-i)&&hand_number_count[7-i]==1&&select_from_number(field,field_n,7-i,hand,hand_n,select_place)){
		pass_flag=false;
		}else if(!EQUAL_STRONG_CAND(7+i)&&hand_number_count[7+i]==1&&select_from_number(field,field_n,7+i,hand,hand_n,select_place)){
		pass_flag=false;
		}else{ continue;
		}
//for(i=0;i<field_n;i++)
//printf("exists non pair %s%s\n",seem_mark[field[i].mark],seem_num[field[i].num]);

//puts("frond!! and no continue");
		break;
		}
		//can't discard hand
	}
//	select_permutation_creat_new_select(field,field_n,hand,hand_n,select_place);
	return(pass_flag);
}
void
revolution(void){
	char temp;
	int i;
	for(i=1;i<(NUM_MAX+1)/2;i++){
		ranking_number[i]=(NUM_MAX+1)-ranking_number[i];
	}
}


void
game_poverty(void)
{
	int i,n;
	CARD deck[CARD_MAX];
	CARD your_hand[PLAYERS_HAND_MAX_BIG];
	CARD com_hand[COMPUTER_MEMBER][PLAYERS_HAND_MAX_BIG];
	int com_n[COMPUTER_MEMBER],your_n;//count hand
	CARD field[FIELD_SIZE];
	int field_n;
	char print_line[PRINT_LINE_MAX+15]={""};
	char temp_string[temp_string_MAX]={""};
	char temp_seem_card[PRINT_LINE_MAX]={""};
	bool select_place[PLAYERS_HAND_MAX_BIG];
	char select_number;
	char select_count;
	bool while_end_flag;
	char winer_count;
	unsigned char player_number;
	unsigned char current;
	SW_TYPE sw=none;
	char pass_count;
	bool eight_flag;
	bool eleven_flag;
//char_on
	char shikaku[5]={""};
	char white_shikaku[5]={""};

	strcpy(shikaku,"▮");
//	shikaku[0]=0xff;
//	shikaku[1]='\0';
	strcpy(white_shikaku,"▯");
//	white_shikaku[0]=0x7e;
//	white_shikaku[1]='\0';
	if(!game_start(" game_poverty")){ return; };
while(1){
//init
		init_deck(deck);
		eleven_flag=eight_flag=false;
		pass_count=winer_count=0;
		current=0;
		field_n=your_n=n=0;
		deck_clear(field,FIELD_SIZE);
		deck_clear(your_hand,PLAYERS_HAND_MAX_BIG);
		for(i=0;i<COMPUTER_MEMBER;i++){
			deck_clear(com_hand[i],PLAYERS_HAND_MAX_BIG);
			com_n[i]=0;
		}
		for(i=0,n=rand()%20+4;i<n;i++)
			riffle_shuffle(deck);
		for(n=0;n<CARD_MAX;){
			add_hand(your_hand,&your_n,deck,&n);
			for(i=0;i<COMPUTER_MEMBER;i++)
				add_hand(com_hand[i],&com_n[i],deck,&n);
		}
//		your_hand[0].num=1;
//		your_hand[1].num=1;
//		your_hand[2].num=1;
//		your_hand[3].num=1;
//		your_hand[4].num=1;

//		field[0].num=1;
//		field[1].num=1;
//		field[2].num=1;
//		field[3].num=1;
//		field[0].mark=0;
//		field[1].mark=1;
//		field[2].mark=2;
//		field[3].mark=3;
//		field_n=1;
		
		hand_card_simsel_sort(your_hand,your_n);
		for(i=0;i<COMPUTER_MEMBER;i++)
			hand_card_simsel_sort(com_hand[i],com_n[i]);
while(1){
//
//your_turn
	//select
		//select_init
		while_end_flag=true;
		for(i=0;i<PLAYERS_HAND_MAX_BIG;i++)
		select_place[i]=false;
		select_number=select_count=0;
		//
		//before_turn_judge
			if(eight_flag){
				while_end_flag=false;
				your_n=current;
			}			
			if(pass_count==COMPUTER_MEMBER){
				deck_clear(field,FIELD_SIZE);
				field_n=0;	
				field[0].num=0;
				field[0].mark=nomark;	
				if(eleven_flag){ revolution(); }	
				eleven_flag=eight_flag=false;
			}
			if(winer_count==3){
				lcd_setCursor(0,0);
				puts("you lost 4th");
				stop_print();
				if(!game_over()) return;
				else break;
			}
		//
			lcd_setCursor(0,0);
//			puts(SPACE_MAX); 
			sprintf(print_line," P%d P%d P%d*I%d",com_n[0],com_n[1],com_n[2],your_n);
			puts(print_line);
		while(while_end_flag){
//			printf("1P=%d 2P=%d 3P=%d my=%d\n",com_n[0],com_n[1],com_n[2],your_n);
			//init
			temp_seem_card[0]='\0';
			temp_string[0]='\0';
			print_line[0]='\0';
			//
			//string_make
			for(i=0;i<field_n;i++){
				sprintf(temp_string,"%s",seem_mark[field[i].mark]);
				strcat(print_line,temp_string);
			}
			if(field_n!=0){sprintf(temp_string,"%s",seem_num[field[0].num]); strcat(print_line,temp_string);}
			for(;i<MARK_MAX+1;i++)
				strcat(print_line," ");
			if(field_n==0)strcat(print_line," ");
			 
//				 
//			puts(print_line);	

			if(can_card_discard(field,field_n,select_count,select_number)){sprintf(temp_string,"*"); }
			temp_string[0]='\0';
			if(3<current){ strcat(temp_string,"|"); }
			for(i=0;i<current && i<3;i++){
				strcat(temp_string,shikaku);
			}
			if(current < your_n){
				sprintf(temp_seem_card,"%s%s%s"
					,seem_mark[your_hand[current].mark]
					,(select_place[current]==true)?".":" "
					,seem_num[your_hand[current].num]);
			}else{
				sprintf(temp_seem_card,"pass");
			}
			strcat(temp_string,temp_seem_card);
			for(i=current+1;i<your_n && i<current+1+3;i++)
				strcat(temp_string,shikaku);
			if( current+1+3 < your_n ){ strcat(temp_string,"|"); }
			if( your_n < current+1+3 && current < your_n ){ strcat(temp_string,white_shikaku); }
			//
//			strcat(print_line,temp_string);
			lcd_setCursor(0,1);

//printf("temp_string=%s|%d\n",temp_string,strlen(temp_string));
//printf("shikaku=%s|%d\n",shikaku,strlen(shikaku));
//printf("temp_seem_card=%s|%d\n",temp_seem_card,strlen(temp_seem_card));
//printf("print_line=%s|%d\n",print_line,strlen(print_line));
//printf("nomarl:");
			strcat(print_line,temp_string);
			puts(print_line);
			//sw
			switch((sw=(SW_TYPE)get_sw())){
					case decision_sw:
//						this 'exists_select_place' used when game is not use (kaidan)
//						if(exists_select_place(select_place,PLAYERS_HAND_MAX_BIG))
					if(	(current==your_n) //this is pass
						||((select_number && (field_n==0 || field_n==select_count)
						&&can_card_discard(field,field_n,select_count,select_number))))
							while_end_flag=false;
						break;
					case select_sw:
//						this 'select_number' used when game is not use (kaidan)
						if((select_number==0 || select_number==your_hand[current].num)){
							if(select_place[current]==true){
								select_place[current]=false;
								select_count--;
								if(select_count==0){ select_number=0; }
							}else if(select_place[current]==false && select_count<FIELD_SIZE){								select_place[current]=true;
								if(select_count==0){ select_number=your_hand[current].num; }
								select_count++;
							}
						}
						break;
					case left_sw	:
						if(0<current)
							current--;
						break;
					case right_sw	:
						if(current<your_n)
							current++;
						break;
					default:
						break;
			}
			//
		}
	//
	//discard
		if(current<your_n){
			discard_to_field(field,&field_n,your_hand,&your_n,select_place);
			pass_count=0;
		}else{//else is pass
			pass_count++;
		}
	//
	//after_turn_judge
			lcd_setCursor(0,1);
			puts(SPACE_MAX); 
		if(!pass_count && field[0].num==11){ revolution(); eleven_flag=true; }	
		if(!pass_count && field[0].num==8){ eight_flag=true; }	
		if(!pass_count && field_n==4){ revolution(); }	
		if(your_n==0){
			lcd_setCursor(0,0);
			sprintf(print_line,"%s winer!!",
				(winer_count==0)?"1st":
				(winer_count==1)?"2nd":
				(winer_count==2)?"3rd":"");
			puts(print_line);
			stop_print();
				if(!game_over()) return;				
				else break;
		}
	//
	//temp_print_feild
			//init
			temp_seem_card[0]='\0';
			temp_string[0]='\0';
			print_line[0]='\0';
			//
			//string_make
			if(!pass_count){
				for(i=0;i<field_n;i++){
					sprintf(temp_string,"%s",seem_mark[field[i].mark]);
					strcat(print_line,temp_string);
				}
				if(field_n!=0){sprintf(temp_string,"%s",seem_num[field[0].num]); strcat(print_line,temp_string);}
				for(;i<MARK_MAX+1;i++)
					strcat(print_line," ");
				if(field_n==0)strcat(print_line," ");
			}else{
				sprintf(print_line," pass ");
			}
//				 
//			puts(print_line);	

			if(can_card_discard(field,field_n,select_count,select_number)){sprintf(temp_string,"*"); }

			temp_string[0]='\0';
//puts(temp_string);
			if(3<current){ strcat(temp_string,"|"); }
			for(i=0;i<current && i<3;i++)
				strcat(temp_string,shikaku);
			if(current < your_n){
				sprintf(temp_seem_card,"%s%s%s"
					,seem_mark[your_hand[current].mark]
					,(select_place[current]==true)?".":" "
					,seem_num[your_hand[current].num]);
			}else{
				sprintf(temp_seem_card,"pass");
			}
			strcat(temp_string,temp_seem_card);
			for(i=current+1;i<your_n && i<current+1+3;i++)
				strcat(temp_string,shikaku);
			if( current+1+3 < your_n ){ strcat(temp_string,"|"); }
			if( your_n < current+1+3 && current < your_n ){ strcat(temp_string,white_shikaku); }
			//
			strcat(print_line,temp_string);
			lcd_setCursor(0,1);

//printf("temp_string=%s|%d\n",temp_string,strlen(temp_string));
//printf("shikaku=%s|%d\n",shikaku,strlen(shikaku));
//printf("temp_seem_card=%s|%d\n",temp_seem_card,strlen(temp_seem_card));
//printf("print_line=%s|%d\n",print_line,strlen(print_line));
//printf("nomarl:");

			puts(print_line);
			stop_print();
		//
//
			lcd_setCursor(0,0);
			puts(SPACE_MAX); 
for(player_number=0;player_number<COMPUTER_MEMBER;player_number++){
//com_turn_1
	
//	temp_string[0]='\0';
//	print_line[0]='\0';
//	sprintf(print_line,"com[%d] ",player_number);
//	for(i=0;i<com_n[(unsigned char)player_number];i++){
//		sprintf(temp_string,"%s%s,",seem_mark[com_hand[player_number][i].mark],seem_num[com_hand[player_number][i].num]);
//	strcat(print_line,temp_string);
//}
//	strcat(print_line,"");
//select
//printf("aaa");
		//select_init
		while_end_flag=true;
		for(i=0;i<PLAYERS_HAND_MAX_BIG;i++)
		select_place[i]=false;
		select_number=select_count=0;
		//
		//before_turn_judge
			if(eight_flag){
				while_end_flag=false;
				your_n=current;
			}			
			if(pass_count==COMPUTER_MEMBER-1){
				deck_clear(field,FIELD_SIZE);
				field_n=0;
				field[0].num=0;
				field[0].mark=nomark;	

				if(eleven_flag){ revolution(); }	
				eleven_flag=eight_flag=false;
			}
			if(com_n[player_number]==0){//if com is winer
				pass_count++;		
				continue;
			}
////ここ作らなきゃ・・・ make a do it
		if(eight_flag || poverty_com_AI(field,field_n,com_hand[player_number],com_n[player_number],select_place)){
//puts("passing");
				pass_count++;		
	//discard
		}else{
		 discard_to_field(field,&field_n,com_hand[player_number],&com_n[player_number],select_place);
			pass_count=0;
		}
	//
	//after_turn_judge

			lcd_setCursor(0,0);
			puts(SPACE_MAX); 
			lcd_setCursor(0,1);
			puts(SPACE_MAX); 
		if(!pass_count && field[0].num==11){ revolution(); eleven_flag=true; }	
		if(!pass_count && field[0].num==8){ eight_flag=true; }	
		if(!pass_count && field_n==4){ revolution(); }	
		if(com_n[player_number]==0){
			winer_count++;
		}
	//
			lcd_setCursor(0,0);
			sprintf(print_line,"%cP%d%cP%d%cP%d I%d"
				,(player_number==0)?'*':' ',com_n[0]
				,(player_number==1)?'*':' ',com_n[1]
				,(player_number==2)?'*':' ',com_n[2]
				,your_n);
			puts(print_line);
	//temp_print_feild
			//init
			temp_seem_card[0]='\0';
			temp_string[0]='\0';
			print_line[0]='\0';
			//
			//string_make
			if(!pass_count){
				for(i=0;i<field_n;i++){
					sprintf(temp_string,"%s",seem_mark[field[i].mark]);
					strcat(print_line,temp_string);
				}
				if(field_n!=0){sprintf(temp_string,"%s",seem_num[field[0].num]); strcat(print_line,temp_string);}
				for(;i<MARK_MAX+1;i++)
					strcat(print_line," ");
				if(field_n==0)strcat(print_line," ");
			}else{
				sprintf(print_line," pass ");
			}
//				 
//			puts(print_line);	

			if(can_card_discard(field,field_n,select_count,select_number)){sprintf(temp_string,"*"); }
			temp_string[0]='\0';
			if(3<current){ strcat(temp_string,"|"); }
			for(i=0;i<current && i<3;i++)
				strcat(temp_string,shikaku);
			if(current < your_n){
				sprintf(temp_seem_card,"%s%s%s"
					,seem_mark[your_hand[current].mark]
					,(select_place[current]==true)?".":" "
					,seem_num[your_hand[current].num]);
			}else{
				sprintf(temp_seem_card,"pass");
			}
			strcat(temp_string,temp_seem_card);
			for(i=current+1;i<your_n && i<current+1+3;i++)
				strcat(temp_string,shikaku);
			if( current+1+3 < your_n ){ strcat(temp_string,"|"); }
			if( your_n < current+1+3 && current < your_n ){ strcat(temp_string,white_shikaku); }
			//
			strcat(print_line,temp_string);
			lcd_setCursor(0,1);

//printf("temp_string=%s|%d\n",temp_string,strlen(temp_string));
//printf("shikaku=%s|%d\n",shikaku,strlen(shikaku));
//printf("temp_seem_card=%s|%d\n",temp_seem_card,strlen(temp_seem_card));
//printf("print_line=%s|%d\n",print_line,strlen(print_line));
//printf("nomarl:");

			puts(print_line);
			stop_print();
	
	//
//
}
}
}
return;
}
//ストップしたのはコンピュータの	AI作ってるとこ時間内から大富豪は後回しにすることした。

void
dbug_temp(void){
	int i,n;
	CARD deck[CARD_MAX];
	CARD your_hand[PLAYERS_HAND_MAX_BIG];
	CARD com_hand[COMPUTER_MEMBER][PLAYERS_HAND_MAX_BIG];
	int com_n[COMPUTER_MEMBER],your_n;//count hand
	CARD field[FIELD_SIZE];
	int field_n;
//	char print_line[PRINT_LINE_MAX]={""};
//	char temp_string[temp_string_MAX]={""};
//	char temp_seem_card[PRINT_LINE_MAX]={""};
	bool select_place[PLAYERS_HAND_MAX_BIG];
//	char select_number;
//	char select_count;
	bool flag;	
//init
		init_deck(deck);
		field_n=your_n=n=0;
		deck_clear(field,FIELD_SIZE);
		deck_clear(your_hand,PLAYERS_HAND_MAX_BIG);
		for(i=0;i<COMPUTER_MEMBER;i++){
			deck_clear(com_hand[i],PLAYERS_HAND_MAX_BIG);
			com_n[i]=0;
		}
//		for(i=0,n=rand()%20+4;i<n;i++)
//			riffle_shuffle(deck);
		for(n=0;n<CARD_MAX;){
			add_hand(your_hand,&your_n,deck,&n);
			for(i=0;i<COMPUTER_MEMBER;i++)
				add_hand(com_hand[i],&com_n[i],deck,&n);
		}
		hand_card_simsel_sort(your_hand,your_n);
		for(i=0;i<COMPUTER_MEMBER;i++)
			hand_card_simsel_sort(com_hand[i],com_n[i]);


		your_hand[0].num=5;
		your_hand[1].num=5;
		your_hand[2].num=9;
		your_hand[3].num=9;
		your_hand[4].num=1;
		your_hand[5].num=1;
		your_hand[0].mark=1;
		your_hand[1].mark=2;
		your_hand[2].mark=3;
		your_hand[3].mark=1;
		your_hand[4].mark=2;
		your_hand[5].mark=1;
		your_n=6;

		field[0].num=9;
//		field[1].num=9;
//		field[2].num=9;
//		field[3].num=1;
		field[0].mark=2;
//		field[1].mark=3;
//		field[2].mark=4;
//		field[3].mark=3;
		field_n=1;
		

		for(i=0;i<PLAYERS_HAND_MAX_BIG;i++)
				select_place[i]=false;

//		select_place[0]=true;
//		select_place[1]=true;
//		select_place[2]=true;
//		select_count=0;
//		select_number=your_hand[0].num;
//





//can_card_discard(field,field_n,select_count,select_number);
//	flag=select_permutation_creat_new_select(field,field_n,your_hand,your_n,select_place);
//for(i=0;i<13;i++)
// select_from_number(field,field_n,,your_hand,your_n,select_place);
flag=poverty_com_AI(field,field_n,your_hand,your_n,select_place);
	puts((flag)?"true and passing":"false");
for(i=0;i<your_n;i++)
	printf("%s%s,",seem_mark[your_hand[i].mark],seem_num[your_hand[i].num]);
puts("");
for(i=0;i<your_n;i++)
	printf((select_place[i])?"**,":"  ,");
puts("");		
discard_to_field(field,&field_n,your_hand,&your_n,select_place);
for(i=0;i<your_n;i++)
	printf("%s%s,",seem_mark[your_hand[i].mark],seem_num[your_hand[i].num]);
puts("");
for(i=0;i<your_n;i++)
	printf((select_place[i])?"**,":"  ,");
puts("");		
	
printf("field_n %d,your_n %d\n",field_n,your_n);
}



int
main(void)
{
/*
*やることを記する
*
*単一の数字を選択すると他の数字が選択できなくなるようにする。
*すべての選択を取り消すと他の数字が選択できるようにする。
*
*今日は終了だべ、帰る、寝る！！
*/
/*
*ふと思いついたことを書く
*選択時に印を出すのではなく
*選んだカードが場に出せる状態ならば
*印を出すようにするといいかもしれない。
*
*/

//	dbug_temp();
//	file_clear();
//	game_HIGH_LOW();
//	game_black_jack();
//	game_poker();
	game_poverty();
	return(0);

}
