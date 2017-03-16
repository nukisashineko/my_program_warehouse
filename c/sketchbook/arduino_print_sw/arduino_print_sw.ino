#include <LiquidCrystal.h>
#include <string.h>
#include <stdio.h>

// Arduino    LCD
//  D2        14(DB7)
//  D3        13(DB6)
//  D4        12(DB5)
//  D5        11(DB4)
//  D10        6(E)
//  D11        5(R/W)
//  D12        4(RS)
//             3(VLC)
//             2(Vdd)
//             1(Vss)
// Arduino    SW
// D6         1(decision_sw)
// D7         2(select_sw)
// D8         3(left_sw)
// D9         4(right_sw)
#define SW1 6
#define SW2 7
#define SW3 8
#define SW4 9


#define CARD_MAX 52
#define NUM_MAX 13
#define MARK_MAX 4
#define PRINT_LINE_MAX 17
#define temp_string_MAX 30
#define SPACE_MAX "                "

char seem_num[14][3]={"0","A","2","3","4","5","6","7","8","9","0","J","Q","K"};
char seem_mark[MARK_MAX+1][10]={"s","h","d","c","n"};
char ranking_number[NUM_MAX+1]={0,12,13,1,2,3,4,5,6,7,8,9,10,11};
typedef enum{spades=0,hearts,diamond,club,nomark} MARK_TYPE;
typedef enum{none=0,decision_sw,select_sw,left_sw,right_sw} SW_TYPE;
typedef struct trump_card{
	int num;
	MARK_TYPE mark;
} CARD;
char get_sw(void);
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
char temp_string[50];
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(SW1,INPUT);     
  pinMode(SW2,INPUT);     
  pinMode(SW3,INPUT);     
  pinMode(SW4,INPUT);     
}

char get_sw(void){
    SW_TYPE flag;
   if(digitalRead(SW1)){
          flag=decision_sw;     
   }else if(digitalRead(SW2)){
          flag=select_sw;
   }else if(digitalRead(SW3)){
           flag=left_sw;
   }else if(digitalRead(SW4)){
           flag=right_sw;
   }else{
           flag=none;
   }
    return(flag);
}
bool
game_start(const char *expreination){

	SW_TYPE sw;
	lcd.setCursor(0,0);
        lcd.print(expreination);
	lcd.setCursor(0,1);
	lcd.print("   [*start]    ");
	for(sw=(SW_TYPE)get_sw();;sw=(SW_TYPE)get_sw()){
		switch(sw){
			case decision_sw:	return(true); break;
			case select_sw:	return(false);break;
			default:				break;
		}		
	}
}

void loop() {
  SW_TYPE sw;
  lcd.setCursor(0, 0);
  lcd.print("hello, world!");
  lcd.setCursor(0, 1);
  temp_string[0]='\0';
  sw=(SW_TYPE)get_sw();
game_start("can start!!");
sprintf(temp_string,"1=%s",
    (sw==decision_sw)?"decision_sw":
    (sw==select_sw)?"select_sw":
    (sw==left_sw)?"left_sw":
    (sw==right_sw)?"right_sw":SPACE_MAX
   );
  lcd.print(temp_string);
  // lcd.print(millis()/1000);
}
