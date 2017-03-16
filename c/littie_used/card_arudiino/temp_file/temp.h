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
#define COMPUTER_MEMBER 3
#define PLAYERS_HAND_MAX_BIG 52/4+1
#define EQUAL_STRONG_CAND(trump_num) (ranking_number[trump_num]==1||ranking_number[trump_num]==2||ranking_number[trump_num]==3||8==trump_num)
#define BLACK_JACK 21
#define PLAYERS_HAND_MAX_SMALL 5
#define FIELD_SIZE 4

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
