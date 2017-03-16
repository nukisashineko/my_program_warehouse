#ifndef _INCLUDE_MAHOUJIN_N_
#define _INCLUDE_MAHOUJIN_N_

#ifndef NDEBUG
#define LOG(arg) fprintf arg
#else 
#define LOG(arg) /*none*/
#endif /*NDEBUG*/

void SwapStr(int str[],int n,int str_tail);
void Sort(int str[],int n,int tail);
double sprt(double x);
int IsMagicSquare(int str[],int nn);
void view_mahoujin(int str[],int n);

#endif /*_INCLUDE_MAHOUJIN_N_*/
