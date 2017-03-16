//#include <LiquidCrystal.h>
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

char seem_num[14][3]={"0","A","2","3","4","5","6","7","8","9","0","J","Q","K"};
char seem_mark[MARK_MAX+1][10]={"s","h","d","c","n"};
char ranking_number[NUM_MAX+1]={0,12,13,1,2,3,4,5,6,7,8,9,10,11};
typedef enum{spades=0,hearts,diamond,club,nomark} MARK_TYPE;
typedef enum{none=0,decision_sw,select_sw,left_sw,right_sw} SW_TYPE;
typedef enum {low=0,high} EXPECTATION;

typedef struct trump_card{
	int num;
	MARK_TYPE mark;
} CARD;
SW_TYPE get_sw(void);
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

SW_TYPE get_sw(void){
    MT_SW_TYPE flag;
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
}


void loop() {
  SW_TYPE sw;
  lcd.setCursor(0, 0);
  lcd.print("hello, world!");
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
   temp_string[0]='\0';
   sw=get_sw();
  sprintf(temp_string,"1=%s",
    (sw==decision_sw)?"decision_sw":
    (sw==select_sw)?"select_sw":
    (sw==left_sw)?"left_sw":
    (sw==right_sw)?"right_sw":"none"
   );
  lcd.print(temp_string);
  // lcd.print(millis()/1000);
}
