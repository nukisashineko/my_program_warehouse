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


char seem_num[14][3]={"0","A","2","3","4","5","6","7","8","9","10","J","Q","K"};
char seem_mark[MARK_MAX+1][10]={"s","h","d","c","n"};
char ranking_number[NUM_MAX+1]={0,12,13,1,2,3,4,5,6,7,8,9,10,11};
typedef enum{spades=0,hearts,diamond,club,nomark} MARK_TYPE;
typedef enum{none=0,decision_sw,select_sw,left_sw,right_sw} SW_TYPE;
typedef enum {low=0,high} EXPECTATION;

typedef struct trump_card{
	int num;
	MARK_TYPE mark;
} CARD;
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
		printf("%s\n",expreination);
		sprintf(print_line,"%s%c%s%s%c%s%s",
			side_speace,(flag==left_sw)?'*':' ',A,"  ",(flag==right_sw)?'*':' ',B,side_speace);
		puts(print_line);
		old_flag=flag;
		flag=get_sw();
		if(flag==select_sw ||flag==none){ flag=old_flag; }
	}
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
	printf("game over!!\\(^ω^)/\n");
	return (which_expreination_A_B("you wonld retry ?","yes","no"));
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
				printf("you win !! count=%d\n",count);
			}else{
				printf("you lose !! count=%d\n",count);
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
			printf("com's draw %d\n",com_n);
//
//your_turn
		your_sum=add_hand(your_hand,&your_n,deck,&n);
		for(;your_sum<BLACK_JACK && your_n<PLAYERS_HAND_MAX_SMALL;){
			sprintf(print_line,"sum%d MoreDraw?",your_sum);
			if(!which_expreination_A_B(print_line,"yes","no")){ break; }
			add_hand(your_hand,&your_n,deck,&n);
				your_sum=hand_card_sum(your_hand,your_n);
			printf("draw=%s-%s,sum=%d\n"
				,seem_mark[your_hand[your_n-1].mark],seem_num[your_hand[your_n-1].num],your_sum);
		}
//
//judge
		printf("com=%d your=%d\n",com_sum,your_sum);
		if( BLACK_JACK<your_sum ){
			printf("you bust !! count=%d\n",count);
			count=0;
			if(!game_over())return;
		}else if(your_sum<=BLACK_JACK
			&& (BLACK_JACK<com_sum
			|| (com_sum<=BLACK_JACK && com_sum<your_sum))){
			printf("you win !! count=%d\n",++count);
		}else{
			printf("you lose !! count=%d\n",count);
			count=0;
			if(!game_over())return;
		}
//
	}
}
//
	typedef enum{five_of_a_kind=1,royal_flush,straight_flush,four_of_a_kind,full_house,flush,straight,three_of_a_kind,two_pairs,one_pair,no_pair,no} RANKING_HAND;
//
char*
from_RANK_to_string(RANKING_HAND flag)
{
	switch(flag){
		case five_of_a_kind:	return("five_of_a_kind=1");	break;
		case royal_flush:	return("royal_flush");	break;
		case straight_flush:	return("straight_flush");	break;
		case four_of_a_kind:	return("four_of_a_kind");	break;
		case full_house:	return("full_house");	break;
		case flush:		return("flush");		break;
		case straight:	return("straight");		break;
		case three_of_a_kind:return("three_of_a_kind");	break;
		case two_pairs:	return("two_pairs");		break;
		case one_pair:	return("one_pair");		break;
		case no_pair:		return("no_pair");		break;
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
					printf("error flag is no\n");exit(1);

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
	char temp_string[PRINT_LINE_MAX]={""};
	bool select_place[PLAYERS_HAND_MAX_SMALL];
	RANKING_HAND your_flag,com_flag;
	bool while_end_flag;
	unsigned char current;
	SW_TYPE sw=none;
//	while(1){
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

			printf("com          %s\n",from_RANK_to_string(com_flag));
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
			puts(print_line);
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
			printf("you          %s\n",from_RANK_to_string(your_flag));
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
			puts(print_line);
			switch((sw=get_sw())){
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
		sprintf(print_line,"your %s%s %s%s %s%s %s%s %s%s"
			,seem_mark[your_hand[0].mark],seem_num[your_hand[0].num]
			,seem_mark[your_hand[1].mark],seem_num[your_hand[1].num]
			,seem_mark[your_hand[2].mark],seem_num[your_hand[2].num]
			,seem_mark[your_hand[3].mark],seem_num[your_hand[3].num]
			,seem_mark[your_hand[4].mark],seem_num[your_hand[4].num]
		);
		puts(print_line);
		sprintf(print_line,"com  %s%s %s%s %s%s %s%s %s%s"
			,seem_mark[com_hand[0].mark],seem_num[com_hand[0].num]
			,seem_mark[com_hand[1].mark],seem_num[com_hand[1].num]
			,seem_mark[com_hand[2].mark],seem_num[com_hand[2].num]
			,seem_mark[com_hand[3].mark],seem_num[com_hand[3].num]
			,seem_mark[com_hand[4].mark],seem_num[com_hand[4].num]
		);
		puts(print_line);
//
//judge
		com_flag=Is_this_hand_rank(com_hand);
		your_flag=Is_this_hand_rank(your_hand);
		printf("your %s\n",from_RANK_to_string(your_flag));
		printf("com  %s\n",from_RANK_to_string(com_flag));
		if	(your_flag == com_flag){
			printf("draw !! count=%d\n",count);
		}else if(com_flag  < your_flag){
			printf("you lost!! count=%d\n",count);
			count=0;
			if(!game_over())return;
		}else if(your_flag  < com_flag){
			printf("you win !! count=%d\n",++count);
		}
//	}
//
}

#if 0

#define COMPUTER_MEMBER 3
#define PLAYERS_HAND_MAX_BIG 52/4+1
// this +1 value is joker speace

void
discard(CARD *hand,int *hand_n,int i)
{
	for(;i<*hand_n-1;i++){
		*(hand+i)=*(hand+i+1);
	}
	(*(hand+*hand_n-1)).num=0;
	(*(hand+*hand_n-1)).mark=nomark;
	*hand_n--;
	return;
}

void
discard_to_field(CARD *field,int *field_n,CARD *hand,int *hand_n,bool *select_place){
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
	return;
}


void hand_card_simsel_sort(CARD *hand,int hand_n)
{
	int i,j,k,min;
	CARD temp;

	for(i=0;i<(hand_n-1);i++){
		min=ranking_number[(*(hand+i)).num];
		k=i;
		for(j=i+1;j<hand_n;j++){
			if(ranking_number[(*(hand+j)).num]<min){
			min=ranking_number[(*(hand+j)).num];
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
can_card_discard(CARD *field,int field_n,char select_count,char select_number)
{
	if((int)select_count!=field_n){
	}else if( !(ranking_number[select_number]<ranking_number[(*field).num]) ){
	}else{
		return(true);
	}
	return(false);	
	
}

#define FIELD_SIZE 4
void
game_poverty(void)
{
	int i,n,count=0;
	CARD deck[CARD_MAX];
	CARD your_hand[PLAYERS_HAND_MAX_BIG];
	CARD com_hand[COMPUTER_MEMBER][PLAYERS_HAND_MAX_BIG];
	int com_n[COMPUTER_MEMBER],your_n;//count hand
	CARD field[FIELD_SIZE];
	int field_n;
	char print_line[PRINT_LINE_MAX]={""};
	char temp_string[PRINT_LINE_MAX]={""};
	char temp_seem_card[PRINT_LINE_MAX]={""};
	bool select_place[PLAYERS_HAND_MAX_BIG];
	char select_number;
	char select_count;
	RANKING_HAND your_flag,com_flag;
	bool while_end_flag;
	char winer_count;
	unsigned char current;
	SW_TYPE sw=none;
	
//init
		init_deck(deck);
		winer_count=0;
		current=0;
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
//		your_hand[0].num=1;
//		your_hand[1].num=1;
//		your_hand[2].num=1;
//		your_hand[3].num=1;
//		your_hand[4].num=1;

		field[0].num=1;
//		field[1].num=1;
//		field[2].num=1;
//		field[3].num=1;
		field[0].mark=0;
//		field[1].mark=1;
//		field[2].mark=2;
//		field[3].mark=3;
		field_n=1;
		
		hand_card_simsel_sort(your_hand,your_n);
		for(i=0;i<COMPUTER_MEMBER;i++)
			hand_card_simsel_sort(com_hand[i],com_n[i]);

//
//your_turn
	//select
		//before_turn_judge
			if(winer_count==3){
				printf("you lost 4th");
				if(!game_over()) return;
			}
		//
		//select_init
		while_end_flag=true;
		for(i=0;i<PLAYERS_HAND_MAX_BIG;i++)
		select_place[i]=false;
		select_number=select_count=0;
		//
			printf("1P=%d 2P=%d 3P=%d my=%d\n",com_n[0],com_n[1],com_n[2],your_n);
		while(while_end_flag){
//			printf("1P=%d 2P=%d 3P=%d my=%d\n",com_n[0],com_n[1],com_n[2],your_n);
			//init
			temp_seem_card[0]='\0';
			temp_string[0]='\0';
			//
			//string_make
			if(can_card_discard(field,field_n,select_count,select_number)){ strcat(temp_string,"*"); }
			if(3<current){ strcat(temp_string,"|"); }
			for(i=0;i<current && i<3;i++)
				strcat(temp_string,"▮");
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
				strcat(temp_string,"▮");
			if( current+1+3 < your_n ){ strcat(temp_string,"|"); }
			if( your_n < current+1+3 && current < your_n ){ strcat(temp_string,"▯"); }
			//
			puts(temp_string);
			//sw
			switch((sw=get_sw())){
					case decision_sw:
//						this 'exists_select_place' used when game is not use (kaidan)
//						if(exists_select_place(select_place,PLAYERS_HAND_MAX_BIG))
						if(	(current==your_n) //this is pass
						   ||(select_number && (field_n==0 || field_n==select_count)))
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
		if(current<your_n)
			discard_to_field(field,&field_n,your_hand,&your_n,select_place);
		//else is pass
	//
	//after_turn_judge
		if(your_n==0){
			printf("%s winer!!",
				(winer_count==0)?"1st":
				(winer_count==1)?"2nd":
				(winer_count==2)?"3rd":"");
			if(!game_over()) return;			
		}
	//
	//temp_print_feild
		print_line[0]=temp_string[0]='\0';
		for(i=0;i<field_n;i++){
			sprintf(temp_string,"%s",seem_mark[field[i].mark]);
			strcat(print_line,temp_string);
		}
			sprintf(temp_string,"%s",seem_num[field[0].num]);
			strcat(print_line,temp_string);
			puts(print_line);
	//
//
for(player_number=0;player_number<;player_number++){
//com_turn_1
//select
		//before_turn_judge
			if(com_n[player_number]==0)
				continue;
		//
		//select_init
		while_end_flag=true;
		for(i=0;i<PLAYERS_HAND_MAX_BIG;i++)
		select_place[i]=false;
		select_number=select_count=0;
		//
		
		can_card_discard(field,field_n,select_count,select_number)
	//discard
		if(current<your_n)
			discard_to_field(field,&field_n,your_hand,&your_n,select_place);
		//else is pass
	//
	//after_turn_judge
		if(your_n==0){
			printf("%s winer!!",
				(winer_count==0)?"1st":
				(winer_count==1)?"2nd":
				(winer_count==2)?"3rd":"");
			if(!game_over()) return;			
		}
	//
	//temp_print_feild
		print_line[0]=temp_string[0]='\0';
		for(i=0;i<field_n;i++){
			sprintf(temp_string,"%s",seem_mark[field[i].mark]);
			strcat(print_line,temp_string);
		}
			sprintf(temp_string,"%s",seem_num[field[0].num]);
			strcat(print_line,temp_string);
			puts(print_line);
	//
//
}
return;
}
//ストップしたのはコンピュータのAI作ってるとこ時間内から大富豪は後回しにすることした。
#endif

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
//	file_clear();
//	game_HIGH_LOW();
	game_black_jack();
//	game_poker();
//	game_poverty();
	return(0);

}

