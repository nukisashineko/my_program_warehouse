#include <LiquidCrystal.h>
//#include <string.h>
//#include <stdio.h>

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


LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
char temp_string[50];
#define SW1 6
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(SW1,INPUT);     
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("hello, world!");
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
   temp_string[0]='\0';
  sprintf(temp_string,"1=%s",(digitalRead(SW1))?"H":"L");
  lcd.print(temp_string);
  // lcd.print(millis()/1000);
}
