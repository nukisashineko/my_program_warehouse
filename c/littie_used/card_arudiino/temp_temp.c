

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
	char discard_count=0;
	*field_n=0;
	for(i=0;i<PLAYERS_HAND_MAX_BIG;i++)
		if(*(select_place+i)){
			add_hand(field,field_n,hand,&i);
			i--;
		}
	for(i=PLAYERS_HAND_MAX_BIG-1;0<=i;i--)
		if(*(select_place+i)){
			discard(hand,hand_n,i);
			discard_count++;
		}
for(i=0;i<*field_n;i++)
//printf("discard_to_field %s%s\n",seem_mark[field[i].mark],seem_num[field[i].num]);
	*hand_n-=discard_count;
	return;
}


void hand_card_simsel_sort(CARD *hand,int hand_n)
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
can_card_discard(CARD *field,int field_n,char select_count,char select_number)
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
select_permutation_creat_new_select(CARD*field,int field_n,CARD *hand,int hand_n,bool *select_place)
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
select_from_number(CARD *field,int field_n,int number,CARD *hand,int hand_n,bool *select_place)
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
#define EQUAL_STRONG_CAND(trump_num) (ranking_number[1]==trump_num||ranking_number[2]==trump_num||ranking_number[3]==trump_num||8==trump_num)
bool
poverty_com_AI(CARD *field,int field_n,CARD *hand,int hand_n,bool *select_place)
{
	int i,j;
	char hand_number_count[NUM_MAX+1];
	bool fainal_flag;
	bool non_pair_flag;
	bool pass_flag;
	bool flag;

	//init
	for(i=0;i<NUM_MAX+1;i++)
		hand_number_count[i]=0;
	for(i=0;i<hand_n;i++)
		for(j=1;j<NUM_MAX+1;j++)
			if( (*(hand+i)).num==j)
				hand_number_count[j]++;
	for(non_pair_flag=flag=i=0;i<NUM_MAX;i++)
		if(!EQUAL_STRONG_CAND(i)){
			if(hand_number_count[i]!=0)flag++;
			if(hand_number_count[i]==1)non_pair_flag++;
		}
	fainal_flag=(flag<2)?true:false;
	pass_flag=false;
//puts("init end of AI");
	//
	if(fainal_flag){//if near finanal
//puts("near fainal");
///puts("discard strong_card");
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
	}else if(non_pair_flag){//if exists not pair  card
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
	}else{//from weak number to strong number
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
	}
//	select_permutation_creat_new_select(field,field_n,hand,hand_n,select_place);
	return(pass_flag);
}
void
revolution(void){
	char temp;
	int i;
	for(i=1;i<(NUM_MAX+1)/2;i++){
		temp=ranking_number[i];
		ranking_number[i]=ranking_number[(NUM_MAX+1)-i];
		ranking_number[(NUM_MAX+1)-i]=temp;
	}
}


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
	char print_line[PRINT_LINE_MAX+30]={""};
	char temp_string[temp_string_MAX]={""};
	char temp_seem_card[PRINT_LINE_MAX]={""};
	bool select_place[PLAYERS_HAND_MAX_BIG];
	char select_number;
	char select_count;
	RANKING_HAND your_flag,com_flag;
	bool while_end_flag;
	char winer_count;
	unsigned char player_number;
	unsigned char current;
	SW_TYPE sw=none;
	char pass_count;
	bool eight_flag;
	bool eleven_flag;
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
				if(eleven_flag){ revolution(); }	
				eleven_flag=eight_flag=false;
			}
			if(winer_count==3){
				lcd_setCursor(0,0);
				puts("you lost 4th");
				stop_print();
				if(!game_over()) return;
			}
		//
			lcd_setCursor(0,0);
			sprintf(print_line,"1P=%d 2P=%d 3P=%d my=%d",com_n[0],com_n[1],com_n[2],your_n);
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
				sprintf(print_line,"%s",seem_mark[field[i].mark]);
				strcat(temp_string,print_line);
			}
			if(field_n!=0){sprintf(print_line,"%s",seem_num[field[i].num]); strcat(temp_string,print_line);}
			for(;i<MARK_MAX+1;i++)
				strcat(temp_string," ");
			if(field_n==0)strcat(temp_string," ");
			 
//				 
//			puts(print_line);	

			if(can_card_discard(field,field_n,select_count,select_number)){sprintf(temp_string,"*"); }
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
			lcd_setCursor(0,1);
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
		if(current<your_n){
			discard_to_field(field,&field_n,your_hand,&your_n,select_place);
			pass_count=0;
		}else{//else is pass
			pass_count++;
		}
	//
	//after_turn_judge
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
					sprintf(print_line,"%s",seem_mark[field[i].mark]);
					strcat(temp_string,print_line);
				}
				if(field_n!=0){sprintf(print_line,"%s",seem_num[field[0].num]); strcat(temp_string,print_line);}
				for(;i<MARK_MAX+1;i++)
					strcat(temp_string," ");
				if(field_n==0)strcat(temp_string," ");
			}else{
				sprintf(temp_string," pass ");
			}
//				 
//			puts(print_line);	

			if(can_card_discard(field,field_n,select_count,select_number)){sprintf(temp_string,"*"); }
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
			lcd_setCursor(0,1);
			puts(temp_string);
			stop_print();
		//
//
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
			if(pass_count==COMPUTER_MEMBER){
				deck_clear(field,FIELD_SIZE);
				field_n=0;
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
		if(!pass_count && field[0].num==11){ revolution(); eleven_flag=true; }	
		if(!pass_count && field[0].num==8){ eight_flag=true; }	
		if(!pass_count && field_n==4){ revolution(); }	
		if(com_n[player_number]==0){
			winer_count++;
		}
	//
			lcd_setCursor(0,0);
			sprintf(print_line,"%c1P=%d%c2P=%d%c3P=%d my=%d"
				,(player_number==0)?'*':' ',com_n[0]
				,(player_number==0)?'*':' ',com_n[1]
				,(player_number==0)?'*':' ',com_n[2]
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
					sprintf(print_line,"%s",seem_mark[field[i].mark]);
					strcat(temp_string,print_line);
				}
				if(field_n!=0){sprintf(print_line,"%s",seem_num[field[0].num]); strcat(temp_string,print_line);}
				for(;i<MARK_MAX+1;i++)
					strcat(temp_string," ");
				if(field_n==0)strcat(temp_string," ");
			}else{
				sprintf(temp_string," pass ");
			}
//				 
//			puts(print_line);	

			if(can_card_discard(field,field_n,select_count,select_number)){sprintf(temp_string,"*"); }
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
			lcd_setCursor(0,1);
			puts(temp_string);
			stop_print();
	
	//
//
}
}
return;
}
