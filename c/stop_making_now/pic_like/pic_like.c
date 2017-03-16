#include<stdio.h>
#include<stdbool.h>
#define PIN_SW 10
#define PIN_PHOT 11
#define PIN_LED_L 9
#define PIN_LED_R 8
#define PIN_CK 7
#define PIN_SIG8 /*none*/
#define PIN_SIG7 6
#define PIN_SIG6 5
#define PIN_SIG5 4
#define PIN_SIG4 3
#define PIN_SIG3 2
#define PIN_SIG2 1
#define PIN_SIG1 0




/**to debug funcucon**/
#define INPUT true
#define OUTPUT false
#define HIGH true
#define LOW false
int bord[5][4];
void init_bord(void){ int i,j;for(i=0;i<5;i++)for(j=0;j<4;j++)bord[i][j]=0;}
void print_bord(void){ int i,j;
	for(i=0;i<5;i++){
	for(j=0;j<4;j++)
		printf("%s",(bord[i][j])?"○":"●");
	printf("\n");
	}
	printf("\n");
	init_bord();
}
void digitalWrite(short int n,bool a){
	short int x,y,i;
	if(a)
		switch(n){
		case PIN_SIG1: if(n==PIN_SIG1){ x=1;y=0; }
		case PIN_SIG4: if(n==PIN_SIG4){ x=1;y=4; }
		case PIN_SIG7: if(n==PIN_SIG7){ x=1;y=2; }
			for(i=0;i<2;i++) bord[y][x+i]=1;
			break;
		case PIN_SIG2: if(n==PIN_SIG2){ x=3;y=1; }
		case PIN_SIG3: if(n==PIN_SIG3){ x=3;y=3; }
		case PIN_SIG5: if(n==PIN_SIG5){ x=0;y=3; }
		case PIN_SIG6: if(n==PIN_SIG6){ x=0;y=1; }
					   bord[y][x]=1;
			break;
	
		}
}
void pinMode(short int n,bool a){
	printf("%s:pin(%d9",(a)?"read":"write",n);
}
/**to debug funcucon**/


void setup(){
  pinMode(PIN_SW,INPUT);
  pinMode(PIN_PHOT,INPUT);
  pinMode(PIN_LED_L,OUTPUT);
  pinMode(PIN_LED_R,OUTPUT);
  pinMode(PIN_CK,OUTPUT);
  pinMode(PIN_SIG7,OUTPUT);
  pinMode(PIN_SIG6,OUTPUT);
  pinMode(PIN_SIG5,OUTPUT);
  pinMode(PIN_SIG4,OUTPUT);
  pinMode(PIN_SIG3,OUTPUT);
  pinMode(PIN_SIG2,OUTPUT);
  pinMode(PIN_SIG1,OUTPUT);
}

short int pin_segment[8]={
	PIN_SIG1,
	PIN_SIG2,
	PIN_SIG3,
	PIN_SIG4,
	PIN_SIG5,
	PIN_SIG6,
	PIN_SIG7
};
#if 0
seven_segment_num[]={
	B01111110,//0=0x7e
	B00110000,//1=0x30
	B01101101,//2=0x6d
	B01111001,//3=0x79
	B00110011,//4=0x33
	B01011011,//5=0x5b
	B01011111,//6=0x5f
	B01110010,//7=0x72
	B01111111,//8=0x7f
	B01111011,//9=0x7b
	B01111101,//A=0x7d
	B00011111,//b=0x1f
	B00011001,//c=0x19
	B00111101,//d=0x3d
	B01001111,//E=0x4f
	B00001111,//F=0x0f
	B00110111,//H=0x72
	B00001110 //L=0x0e
}
#endif
short int seven_segment_num[18]={
	0x7e,//0
	0x30,//1
	0x6d,//2
	0x79,//3
	0x33,//4
	0x5b,//5
	0x5f,//6
	0x72,//7
	0x7f,//8
	0x7b,//9
	0x77,//a
	0x1f,//b
	0x0d,//c
	0x3d,//d
	0x4f,//e
	0x47,//f
	0x37,//h
	0x0e //l
};


int main(void){
int i,n;
for(n=0;n<18;n++){//printf("%d:",n);
	 for(i=0;i<7;i++){
	  digitalWrite(pin_segment[i],(seven_segment_num[n]>>(6-i))&0x1);
 //		 printf("%c",((seven_segment_num[n]>>(6-i))& 0x1)?'1':'0');
	}
//printf("\n");
	print_bord();
}
return(0);
}
