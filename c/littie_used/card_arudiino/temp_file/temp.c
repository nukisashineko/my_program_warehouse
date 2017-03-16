#include "temp.h"
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
void
print_field()
{
}
void
print_field_and_hand()
{
}
void
print_field_and_hand(int your_n,int field_n,char select_number,char select_count,unsigned char current){
	int i;
	char print_line[PRINT_LINE_MAX+15]={""};
	char temp_string[temp_string_MAX]={""};
	char temp_seem_card[PRINT_LINE_MAX]={""};

	CARD your_hand[PLAYERS_HAND_MAX_BIG];
	CARD field[PLAYERS_HAND_MAX_SMALL];
	bool select_place[PLAYERS_HAND_MAX_BIG];

//char_on
	char shikaku[5]={""};
	char white_shikaku[5]={""};
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
}
int main(void)
{
int your_n;
int field_n;
char select_number;
char select_count;
unsigned char current;
	return(0);
}
