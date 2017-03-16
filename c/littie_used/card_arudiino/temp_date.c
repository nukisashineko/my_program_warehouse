# 1 "temp_temp.c"
# 1 "<command-line>"
# 1 "temp_temp.c"




void
disstruct trump_card(struct trump_card *hand,int *hand_n,int i)
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
disstruct trump_card_to_field(struct trump_card *field,int *field_n,struct trump_card *hand,int *hand_n,char *select_place){
 int i;
 char disstruct trump_card_count=0;
 *field_n=0;
 for(i=0;i<52/4+1;i++)
  if(*(select_place+i)){
   add_hand(field,field_n,hand,&i);
   i--;
  }
 for(i=52/4+1 -1;0<=i;i--)
  if(*(select_place+i)){
   disstruct trump_card(hand,hand_n,i);
   disstruct trump_card_count++;
  }
for(i=0;i<*field_n;i++)

 *hand_n-=disstruct trump_card_count;
 return;
}


void hand_struct trump_card_simsel_sort(struct trump_card *hand,int hand_n)
{
 int i,j,k,max;
 struct trump_card temp;

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

char
exists_select_place(char *select_place,int n)
{
 int i;
 for(i=0;i<n;i++)
  if(*(select_place+i))
   break;
 return((i<n)?true:false);
}

char
can_struct trump_card_disstruct trump_card(struct trump_card *field,int field_n,char select_count,char select_number)
{

 if(field_n!=0 && (int)select_count!=field_n ){

 }else if(field_n!=0 && !(ranking_number[(unsigned char)select_number]<ranking_number[(*field).num]) ){

 }else{

  return(true);
 }
 return(false);
}




char
select_permutation_creat_new_select(struct trump_card*field,int field_n,struct trump_card *hand,int hand_n,char *select_place)
{
 int i,j;
 int temp_place_n;
 char temp_select_place[MARK_MAX];
 struct trump_card *temp_select_struct trump_cards[MARK_MAX];
 char masc[MARK_MAX+1]={0x0,0x1,0x3,0x7,0xf};
 char flag;
 char select_count;
 char select_number;


 flag=false;
 temp_place_n=0;
 for(i=0;i<MARK_MAX;i++){
  temp_select_place[i]=false;
  temp_select_struct trump_cards[i]=NULL;
 }
 for(i=0;i<hand_n;i++){

  if(*(select_place+i)==true){
   select_number=(*(hand+i)).num;
   temp_select_struct trump_cards[temp_place_n]=(hand+i);
   temp_place_n++;

  }
 }
# 125 "temp_temp.c"
 for(i=masc[temp_place_n],select_count=0;i;select_count=0,i--){
  if(0x1&(i>>0)){ temp_select_place[0]=true; select_count++; }
  if(0x1&(i>>1)){ temp_select_place[1]=true; select_count++; }
  if(0x1&(i>>2)){ temp_select_place[2]=true; select_count++; }
  if(0x1&(i>>3)){ temp_select_place[3]=true; select_count++; }

  if(can_struct trump_card_disstruct trump_card(field,field_n,select_count,select_number)){
   flag=true;
   break;
  }
  for(j=0;j<MARK_MAX;j++)
   temp_select_place[j]=false;
 }
 if(flag){
  for(i=0;i<temp_place_n;i++)
  if(temp_select_place[i]==false)
   for(j=0;j<52/4+1;j++){
    if((hand+j)==(temp_select_struct trump_cards[i])){
     *(select_place+j)=false;

    }
   }
 }else{
  for(j=0;j<52/4+1;j++)
    *(select_place+j)=false;
 }
 return(flag);
}
char
select_from_number(struct trump_card *field,int field_n,int number,struct trump_card *hand,int hand_n,char *select_place)
{
 int i;
 char flag=false;
 char flag_selsect=false;

 for(i=0;i<52/4+1;i++){
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

char
poverty_com_AI(struct trump_card *field,int field_n,struct trump_card *hand,int hand_n,char *select_place)
{
 int i,j;
 char hand_number_count[NUM_MAX+1];
 char fainal_flag;
 char non_pair_flag;
 char pass_flag;
 char flag;


 for(i=0;i<NUM_MAX+1;i++)
  hand_number_count[i]=0;
 for(i=0;i<hand_n;i++)
  for(j=1;j<NUM_MAX+1;j++)
   if( (*(hand+i)).num==j)
    hand_number_count[j]++;
 for(non_pair_flag=flag=i=0;i<NUM_MAX;i++)
  if(!(ranking_number[1]==i||ranking_number[2]==i||ranking_number[3]==i||8==i)){
   if(hand_number_count[i]!=0)flag++;
   if(hand_number_count[i]==1)non_pair_flag++;
  }
 fainal_flag=(flag<2)?true:false;
 pass_flag=false;


 if(fainal_flag){


  for(i=3,flag=false;!flag&&1<=i;i--){
   flag=select_from_number(field,field_n,ranking_number[i],hand,hand_n,select_place);
  }if(i<1&&!select_from_number(field,field_n,8,hand,hand_n,select_place)){

   for(i=0;i<NUM_MAX+1;i++)
    if(hand_number_count[i]){

     if(select_from_number(field,field_n,i,hand,hand_n,select_place))
      break;
    }
   if(NUM_MAX+1<=i)
    pass_flag=true;
  }
 }else if(non_pair_flag){

  pass_flag=true;
  for(i=0;i<NUM_MAX/2-1;i++){
  if(!(ranking_number[1]==7-i||ranking_number[2]==7-i||ranking_number[3]==7-i||8==7-i)&&hand_number_count[7-i]==1&&select_from_number(field,field_n,7-i,hand,hand_n,select_place)){
  pass_flag=false;
  }else if(!(ranking_number[1]==7+i||ranking_number[2]==7+i||ranking_number[3]==7+i||8==7+i)&&hand_number_count[7+i]==1&&select_from_number(field,field_n,7+i,hand,hand_n,select_place)){
  pass_flag=false;
  }else{ continue;
  }




  break;
  }

 }else{

  if(field_n<2){
   i=-1;
  }else {
   for(i=NUM_MAX-1;i>=0;i--){
    if(hand_number_count[(unsigned char)ranking_number[i]]
    && select_from_number(field,field_n,ranking_number[i],hand,hand_n,select_place))
     break;
   }
  }
  if(i<0)
    pass_flag=true;
 }

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
 struct trump_card deck[struct trump_card_MAX];
 struct trump_card your_hand[52/4+1];
 struct trump_card com_hand[3][52/4+1];
 int com_n[3],your_n;
 struct trump_card field[4];
 int field_n;
 char print_line[PRINT_LINE_MAX+30]={""};
 char temp_string[temp_string_MAX]={""};
 char temp_seem_struct trump_card[PRINT_LINE_MAX]={""};
 char select_place[52/4+1];
 char select_number;
 char select_count;
 RANKING_HAND your_flag,com_flag;
 char while_end_flag;
 char winer_count;
 unsigned char player_number;
 unsigned char current;
 SW_TYPE sw=none;
 char pass_count;
 char eight_flag;
 char eleven_flag;

  init_deck(deck);
  eleven_flag=eight_flag=false;
  pass_count=winer_count=0;
  current=0;
  field_n=your_n=n=0;
  deck_clear(field,4);
  deck_clear(your_hand,52/4+1);
  for(i=0;i<3;i++){
   deck_clear(com_hand[i],52/4+1);
   com_n[i]=0;
  }
  for(i=0,n=rand()%20+4;i<n;i++)
   riffle_shuffle(deck);
  for(n=0;n<struct trump_card_MAX;){
   add_hand(your_hand,&your_n,deck,&n);
   for(i=0;i<3;i++)
    add_hand(com_hand[i],&com_n[i],deck,&n);
  }
# 320 "temp_temp.c"
  hand_struct trump_card_simsel_sort(your_hand,your_n);
  for(i=0;i<3;i++)
   hand_struct trump_card_simsel_sort(com_hand[i],com_n[i]);
while(1){




  while_end_flag=true;
  for(i=0;i<52/4+1;i++)
  select_place[i]=false;
  select_number=select_count=0;


   if(eight_flag){
    while_end_flag=false;
    your_n=current;
   }
   if(pass_count==3){
    deck_clear(field,4);
    field_n=0;
    if(eleven_flag){ revolution(); }
    eleven_flag=eight_flag=false;
   }
   if(winer_count==3){
	lcd_setCursor(0,0);
    lcd.print("you lost 4th");
    if(!game_over()) return;
   }
	lcd_setCursor(0,0);
   sprintf(print_line,"1P=%d 2P=%d 3P=%d my=%d",com_n[0],com_n[1],com_n[2],your_n);
   lcd.print(print_line);
  while(while_end_flag){


   temp_seem_struct trump_card[0]='\0';
   temp_string[0]='\0';
   print_line[0]='\0';


   for(i=0;i<field_n;i++){
    sprintf(print_line,"%s",seem_mark[field[i].mark]);
    strcat(temp_string,print_line);
   }
   if(field_n!=0){sprintf(print_line,"%s",seem_num[field[i].num]); strcat(temp_string,print_line);}
   for(;i<MARK_MAX+1;i++)
    strcat(temp_string," ");
   if(field_n==0)strcat(temp_string," ");




   if(can_struct trump_card_disstruct trump_card(field,field_n,select_count,select_number)){sprintf(temp_string,"*"); }
   if(3<current){ strcat(temp_string,"|"); }
   for(i=0;i<current && i<3;i++)
    strcat(temp_string,"▮");
   if(current < your_n){
    sprintf(temp_seem_struct trump_card,"%s%s%s"
     ,seem_mark[your_hand[current].mark]
     ,(select_place[current]==true)?".":" "
     ,seem_num[your_hand[current].num]);
   }else{
    sprintf(temp_seem_struct trump_card,"pass");
   }
   strcat(temp_string,temp_seem_struct trump_card);
   for(i=current+1;i<your_n && i<current+1+3;i++)
    strcat(temp_string,"▮");
   if( current+1+3 < your_n ){ strcat(temp_string,"|"); }
   if( your_n < current+1+3 && current < your_n ){ strcat(temp_string,"▯"); }

   lcd.print(temp_string);

   switch((sw=get_sw())){
     case decision_sw:


      if( (current==your_n)
         ||(select_number && (field_n==0 || field_n==select_count)))
       while_end_flag=false;
      break;
     case select_sw:

      if((select_number==0 || select_number==your_hand[current].num)){
       if(select_place[current]==true){
        select_place[current]=false;
        select_count--;
        if(select_count==0){ select_number=0; }
       }else if(select_place[current]==false && select_count<4){ select_place[current]=true;
        if(select_count==0){ select_number=your_hand[current].num; }
        select_count++;
       }
      }
      break;
     case left_sw :
      if(0<current)
       current--;
      break;
     case right_sw :
      if(current<your_n)
       current++;
      break;
     default:
      break;
   }

  }


  if(current<your_n){
   disstruct trump_card_to_field(field,&field_n,your_hand,&your_n,select_place);
   pass_count=0;
  }else{
   pass_count++;
  }


  if(!pass_count && field[0].num==11){ revolution(); eleven_flag=true; }
  if(!pass_count && field[0].num==8){ eight_flag=true; }
  if(!pass_count && field_n==4){ revolution(); }
  if(your_n==0){
   sprintf(print_line,"%s winer!!",
    (winer_count==0)?"1st":
    (winer_count==1)?"2nd":
    (winer_count==2)?"3rd":"");
   lcd.print(print_line);
   if(!game_over()) return;

  }



   temp_seem_struct trump_card[0]='\0';
   temp_string[0]='\0';
   print_line[0]='\0';


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



   if(can_struct trump_card_disstruct trump_card(field,field_n,select_count,select_number)){sprintf(temp_string,"*"); }
   if(3<current){ strcat(temp_string,"|"); }
   for(i=0;i<current && i<3;i++)
    strcat(temp_string,"▮");
   if(current < your_n){
    sprintf(temp_seem_struct trump_card,"%s%s%s"
     ,seem_mark[your_hand[current].mark]
     ,(select_place[current]==true)?".":" "
     ,seem_num[your_hand[current].num]);
   }else{
    sprintf(temp_seem_struct trump_card,"pass");
   }
   strcat(temp_string,temp_seem_struct trump_card);
   for(i=current+1;i<your_n && i<current+1+3;i++)
    strcat(temp_string,"▮");
   if( current+1+3 < your_n ){ strcat(temp_string,"|"); }
   if( your_n < current+1+3 && current < your_n ){ strcat(temp_string,"▯"); }

   lcd.print(temp_string);


for(player_number=0;player_number<3;player_number++){
# 505 "temp_temp.c"
  while_end_flag=true;
  for(i=0;i<52/4+1;i++)
  select_place[i]=false;
  select_number=select_count=0;


   if(eight_flag){
    while_end_flag=false;
    your_n=current;
   }
   if(pass_count==3){
    deck_clear(field,4);
    field_n=0;
    if(eleven_flag){ revolution(); }
    eleven_flag=eight_flag=false;
   }
   if(com_n[player_number]==0){
    pass_count++;
    continue;
   }

  if(eight_flag || poverty_com_AI(field,field_n,com_hand[player_number],com_n[player_number],select_place)){

    pass_count++;

  }else{
   disstruct trump_card_to_field(field,&field_n,com_hand[player_number],&com_n[player_number],select_place);
   pass_count=0;
  }


  if(!pass_count && field[0].num==11){ revolution(); eleven_flag=true; }
  if(!pass_count && field[0].num==8){ eight_flag=true; }
  if(!pass_count && field_n==4){ revolution(); }
  if(com_n[player_number]==0){
   winer_count++;
  }

   sprintf(print_line,"%c1P=%d%c2P=%d%c3P=%d my=%d"
    ,(player_number==0)?'*':' ',com_n[0]
    ,(player_number==0)?'*':' ',com_n[1]
    ,(player_number==0)?'*':' ',com_n[2]
    ,your_n);
   lcd.print(print_line);


   temp_seem_struct trump_card[0]='\0';
   temp_string[0]='\0';
   print_line[0]='\0';


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



   if(can_struct trump_card_disstruct trump_card(field,field_n,select_count,select_number)){sprintf(temp_string,"*"); }
   if(3<current){ strcat(temp_string,"|"); }
   for(i=0;i<current && i<3;i++)
    strcat(temp_string,"▮");
   if(current < your_n){
    sprintf(temp_seem_struct trump_card,"%s%s%s"
     ,seem_mark[your_hand[current].mark]
     ,(select_place[current]==true)?".":" "
     ,seem_num[your_hand[current].num]);
   }else{
    sprintf(temp_seem_struct trump_card,"pass");
   }
   strcat(temp_string,temp_seem_struct trump_card);
   for(i=current+1;i<your_n && i<current+1+3;i++)
    strcat(temp_string,"▮");
   if( current+1+3 < your_n ){ strcat(temp_string,"|"); }
   if( your_n < current+1+3 && current < your_n ){ strcat(temp_string,"▯"); }

   lcd.print(temp_string);



}
}
return;
}
