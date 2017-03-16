#ifndef _PIC_TEST_H_
#define _PIC_TEST_H_

#define INPUT_SW  (sw=PORTA)
#define SW1 (0x08)
#define SW2 (0x04)


#if define _PIC_RAP_

#define bool char
#define OUTPUT_PORTB(value) PORTB=(value)

#else

#include<stdbool.h>

#endif/*_PIC_RAP_*/

unsigned short int sw;
unsigned short int TEMP=0;


#define DEBUG 0


#if DEBUG
	int a;
#endif




#ifdef P__1
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
#endif /*P__1*/

#ifdef P__1_01
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
#endif /*P__1_01*/

#ifdef P__1_02
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
#endif /*P__1_02*/

#ifdef P__1_03
void p__1_03(void){
	TRISA=0x00;
	TRISB=0x00;
	while(1){
		OUTPUT_PORTB(0xAA);
		Delay_ms(1000);
		OUTPUT_PORTB(0x00);
		Delay_ms(1000);
		OUTPUT_PORTB(0x55);
		Delay_ms(1000);
		OUTPUT_PORTB(0x00);
		Delay_ms(1000);

	}	
}
#endif /*P__1_03*/

#ifdef P__1_04
void p__1_04(void){
	TRISA=0x00;
	TRISB=0x00;
	while(1){
			if(!TEMP){ TRISB=0x01; }
			OUTPUT_PORTB(TEMP);
			TEMP<<=1;
			Delay_ms(1000);
	}	
}
#endif /*P__1_04*/

#ifdef P__02
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
#endif /*P__02*/

#ifdef P__2_01
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
#endif /*P__2_01*/

#ifdef P__2_02
void p__2_02(void){
	TRISA=0x0c;
	TRISB=0x00;
	PORTA=0x00;
	while(1){
		INPUT_SW;
		if(sw & (SW1|SW2)){ OUTPUT_PORTB(0x03); }
		else if(sw & SW1){ OUTPUT_PORTB(0x02); }
		else if(sw & SW2){ OUTPUT_PORTB(0x01); }
		else { OUTPUT_PORTB(0x00); }
	}	
}
#endif /*P__2_02*/

#ifdef P__2_03
void p__2_03(void){
	TRISA=0x0c;
	TRISB=0x00;
	PORTA=0x00;
	while(1){
		INPUT_SW;
		if( sw & (SW1 | SW2)){ continue; }
		if(sw & SW1){
			if(!TEMP){ TEMP=0x01; }
			OUTPUT_PORTB(TEMP);
			TRISB<<=1;
			Delay_ms(100);
		}
		if(sw & SW2){
			if(!TRISB){ TRISB=0x80; }
			OUTPUT_PORTB(TEMP);
			TRISB>>=1;
			Delay_ms(100);
		
		}
	}	
}
#endif /*play_game*/
#ifdef PLAY_GAME
void count_shigunal(unsigned short int a,bool shigunal[]){
	int i;
	i=0;
	for(;i<8;a>>=1,i++){
	//PORTB=a;
	//Delay_ms(200);
	shigunal[i]=(a & 0x1); 
	}
	return;
}
void play_game(void){
	bool shigunal[8];
	unsigned int temp=0;
	int i,j;
	TRISA=0x00;
	TRISB=0x00;
	PORTB=0x00;
	while(1){
		temp=PORTB;
		if(!temp){ temp=0x10; }
		count_shigunal(temp,shigunal);
		for(i=0;i<8;i++){
			if(shigunal[i]){
			//	PORTB=temp<<2;
			//	Delay_ms(200) ;
				temp^=(0x07 <<(i-1)); 
			}
		}
		//PORTB=0xaa;
		//DElay_ms(100);
		OUTPUT_PORTB(temp);
		Delay_ms(1000);
	}	
}
#endif /*play_game*/

#endif/*_PIC_TEST_H_*/