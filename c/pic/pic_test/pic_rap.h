#ifndef _PIC_RAP_H_
#define _PIC_RAP_H_


#include<stdio.h>
#include<stdlib.h>

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

#define Delay_ms(value) printf("%s\n",#value)


#endif/* _PIC_RAP_H_ */
