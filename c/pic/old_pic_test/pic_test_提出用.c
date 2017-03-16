#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void print_short_int_to_binary(short int );
void p__1(void);
void p__1_01(void);
void p__1_02(void);
void p__1_03(void);
void p__1_04(void);
void p__2_01(void);
void p__2_02(void);
void p__2_03(void);
void play_game(void);
void play_game_second(void);

#define CMICRO

#ifndef CMICRO/*cmicroでコンパイルしない*/

void print_short_int_to_binary(short int n){
int i;
for(i=0;i<8;i++){ putchar(( 0x1 & (n>>((8-1)-i)) )?'1':'0'); }
putchar('\n');
return;
}

#define OUTPUT_PORTB(value) if(value & TRISB){ fprintf(stderr,"出力ポートでないのに出力しようとした。"); exit(1); }\
				PORTB=value;\
				print_short_int_to_binary(value)

#define OUTPUT_PORTA(value) if(value & TRISA){ fprintf(stderr,"出力ポートでないのに出力しようとした。"); exit(1); }\
				PORTA=value;\
				print_short_int_to_binary(value)

#define Delay_ms(value) fprintf(stderr,"Delay_ms(%s)\n",#value)

#define INPUT_SW  if( (c=getchar())=='z'){ sw=SW1; }\
		  else if(c=='x'){ sw=SW2; }\
		  else if(c=='c'){ sw=(SW1|SW2); }\
		  else { sw=0; }
short int PORTA=0;
short int PORTB=0;
short int TRISA=0;
short int TRISB=0;

#else

#define INPUT_SW  (sw=PORTA)
#define OUTPUT_PORTB(value) PORTB=value;
#define OUTPUT_PORTA(value) PORTA=value;

#endif/* CMICRO */

#define NDEBUG

#ifndef NDEBUG
#define LOG(arg) fprintf arg
#else
#define LOG(arg) /*none*/
#endif /*NDEBUG*/


unsigned short int TEMP=0;
int i;
char c;


#define SW1 (0x08)
#define SW2 (0x04)
unsigned short int sw;




void p__1(void){
	TRISA=0x00;
	TRISB=0x00;
	while(1){
		OUTPUT_PORTB(0x02);
		Delay_ms(1000);
		OUTPUT_PORTB(0x01);
		Delay_ms(1000);

	}	
}

void p__1_01(void){
	TRISA=0x00;
	TRISB=0x00;
	while(1){
		OUTPUT_PORTB(0x02);
		Delay_ms(500);
		OUTPUT_PORTB(0x01);
		Delay_ms(500);
	}	
}

void p__1_02(void){
	TRISA=0x00;
	TRISB=0x00;
	while(1){
		OUTPUT_PORTB(0xAA);
		Delay_ms(1000);
		OUTPUT_PORTB(0x55);
		Delay_ms(1000);

	}	
}
void p__1_03(void){
	TRISA=0x00;
	TRISB=0x00;
	while(1){
		OUTPUT_PORTB(0xAA);
		Delay_ms(500);
		OUTPUT_PORTB(0x00);
		Delay_ms(500);
		OUTPUT_PORTB(0x55);
		Delay_ms(500);
		OUTPUT_PORTB(0x00);
		Delay_ms(500);

	}	
}
void p__1_04(void){
	TRISA=0x00;
	TRISB=0x00;
	while(1){
			if(!TEMP){ TEMP=0x01; }
			OUTPUT_PORTB(TEMP);
			TEMP<<=1;
			Delay_ms(1000);
	}	
}
void p__02(void){
	TRISA=0x0c;
	TRISB=0x00;
	PORTA=0x00;
	while(1){
		INPUT_SW;
		if(sw & SW2){ OUTPUT_PORTB(0x01); }
		else{ OUTPUT_PORTB(0x00); }
	}	
}
void p__2_01(void){
	TRISA=0x0c;
	TRISB=0x00;
	PORTA=0x00;
	while(1){
		INPUT_SW;
		if(sw & SW1){ OUTPUT_PORTB(0x02); }
		else{ OUTPUT_PORTB(0x00); }
	}	
}
void p__2_02(void){
	TRISA=0x0c;
	TRISB=0x00;
	PORTA=0x00;
	while(1){
		INPUT_SW;
		sw &=(SW1|SW2);
		if(sw == (SW1|SW2)){ OUTPUT_PORTB(0x03); }
		else if(sw & SW1){ OUTPUT_PORTB(0x02); }
		else if(sw & SW2){ OUTPUT_PORTB(0x01); }
		else { OUTPUT_PORTB(0x00); }
	}	
}
void p__2_03(void){
	TRISA=0x0c;
	TRISB=0x00;
	PORTA=0x00;
	while(1){
		INPUT_SW;
		sw &=(SW1 | SW2);
		if( !sw ){ continue; }
		if(sw & SW1){
			if(!TEMP){ TEMP=0x01; }
			OUTPUT_PORTB(TEMP);
			TEMP<<=1;
			TEMP &= 0xff;
			Delay_ms(100);
		}
		else if(sw & SW2){
			if(!TEMP){ TEMP=0x80; }
			OUTPUT_PORTB(TEMP);
			TEMP>>=1;
			TEMP &= 0xff;
			Delay_ms(100);
		
		}
	}	
}
void count_signal(unsigned short int a,bool signal[]){
	int i;
	i=0;
	for(;i<8;a>>=1,i++){
	signal[i]=(a & 0x1); 
	}
	return;
}
/*play_gameの説明
 * 出力例
 *00100↓
 *01010↓
 *10001↓(この時10101にはならない)
 *01010
 * 前回の出力の両隣に出力していく
 *また、出力が重なることになった時は出力しない
 */
void play_game(void){
	bool signal[8];
	unsigned int temp=0;
	int i,j;
	TRISA=0x00;
	TRISB=0x00;
	PORTB=0x00;
	while(1){
		temp=PORTB;
		temp &= 0xff;//short intの大きさに制限する。
		if(!temp){ temp=0x10; }
		count_signal(temp,shigunal);//1bitごとに分けてshigunal[]に格納する。
		for(j=0;j<8;j++){
//			putchar((shigunal[j])?'t':'f');
			if(signal[j]){
				if(0>(j-1)){ temp ^= 0x03; }//負の時のビット演算処理
				else { temp ^= (0x07<<(j-1)); }//通常のビット演算処理
			}
		}
//		LOG((stderr,"_0x%x_",temp));
		OUTPUT_PORTB(temp);
		Delay_ms(500);
	}	
}
/*
 * play_game_second()の説明
 * 出力例
 * ※ただし、左側の出力のほうが処理速度が早いとする。
 * ※また、書かれている方向に進むことを省略して[進む」と書きます。
 * ※また、既に進路が塞がれているのせいで進めないときに方向を変えることを省略して「方向」と書きます。
 *※左側の出力ビットのことを左のボール、
 *※右側の出力ビットのことを右のボールと呼称します。
 * (位置,方向)⇢出力⇐(位置,方向)
 * (5,left)⇢10001⇐(0,right)//左のボール「進む」右ボール[進む](結果↓)
 * (4,left)⇢01010⇐(1,right)//左「進む」右[方向]
 * (3,left)⇢00110⇐(1,left)//左「方向」右[進む]
 * (3,right)⇢00101⇐(0,left)//左「進む」右[方向]
 * (4,right)⇢01001⇐(0,right)//左「進む」右[進む]
 * (5,right)⇢10010⇐(1,right)
 *
 * 出力ビット(ボール)はそれぞれ独立して方向を持っておりその方向に進もうとする。
 * ビットの端にたどり着くか、進もうとした位置にボールがあったときその場で方向転換をする
 */

#define ALL_PLACE(temp) for(temp=0,j=0;j<8;j++){ if(boll[j].direction!=null){temp |=(1<<boll[j].place);} }

typedef enum{ null,right,left }DERECTION;
struct {short int place;
	DERECTION direction;}boll[8];
//bollは自分の位置と進んでいる方向を持っている。

void init_boll(void){ int j; for(j=0;j<8;j++){ boll[j].direction=null; boll[j].place=0; } }
void add_boll(short int place,DERECTION direction){ static int count=0; if(count>7){ init_boll(); count=0; } boll[count].direction=direction; boll[count].place=place; count++; };
void play_game_second(void){
	int j,k,temp;

	while(1){
		INPUT_SW;
		if(sw==SW1){ add_boll(0,left); LOG((stderr,"sw==SW1\n")); }
		else if(sw==SW2){ add_boll(7,right); LOG((stderr,"sw==SW2\n")); }
		else if(sw==(SW1|SW2)){ init_boll(); LOG((stderr,"sw==SW1|SW2\n")); }
		ALL_PLACE(temp);
		for(k=0;k<8;k++){
			LOG((stderr,"boll[%d].direction=%d,boll[%d].place=%d",k,boll[k].direction,k,boll[k].place));
			if(boll[k].direction!=null && boll[k].direction==right){ /*"右"*/
				if(((boll[k].place-1)==-1)||(temp & 1 <<(boll[k].place-1))){ boll[k].direction=left;LOG((stderr,"_flag1")); }//壁に突き当たるか、他のbollがあるなら、向きを変える
				else{ boll[k].place--;ALL_PLACE(temp); LOG((stderr,"_flag2")); }//いないなら、移動し、移動したことを確認する
			}
			else if(boll[k].direction!=null && boll[k].direction==left){  /*左*/
				if( (boll[k].place+1)==8 ||(temp & 1 <<(boll[k].place+1))){ boll[k].direction=right;LOG((stderr,"_flag3")); }//壁に突き当たるか、他のbollがあるなら、向きを変える
				else{ boll[k].place++;ALL_PLACE(temp); LOG((stderr,"_flag4")); }//いないなら、移動し、移動したことを確認する	
			}
		
		LOG((stderr,"\n"));
		}
		temp&=0xff;
		OUTPUT_PORTB(temp);
		Delay_ms(500);
	}
	return;
}
int main(void){
	play_game_second();
	return (0);
}
