#include<stdio.h>
#define NDEBUG
#include "mahoujin.h"
double sprt(double x){
	int n;
	for(n=1;n*n<=x;n++)
		if(n*n==x) return (double)(n);
	return(10.1);
}

int IsMagicSquare(int str[],int nn){
  int ave,slant_line[2],side_line,lenth_line;/*平均、斜め*2、横、縦*/
  double rootn=sprt(nn);
  int n;
  int i,j;
 
 /*init*/
slant_line[0]=slant_line[1]=side_line=lenth_line=0;
 /* 引数の分解nn==n*n */
  if(rootn != (int)rootn){ goto err2; }
  n=(int)rootn;
  /*aveの計算*/
  ave=(n*n*n+n)/2;
	LOG((stderr,"ave==%d\n",ave));
  /*魔方陣の判定*/
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      lenth_line+=str[i*n+j];/*str[i][j]*/
      side_line+=str[j*n+i];/*str[j][i]*/
	LOG((stderr,"lenth_line==%d side_line==%d\n",lenth_line,side_line));
    }
    if(!(ave==lenth_line && ave==side_line )){ goto err1; }
    lenth_line=side_line=0;
    slant_line[0]+=str[i*n+i];/*str[i][i]*/
    slant_line[1]+=str[((n-1)-i)*n+((n-1)-i)];/*str[nn-i][nn-i]*/
	LOG((stderr,"slant_line[0]=%d slant_line[1]==%d\n ",slant_line[0],slant_line[1] ));
  }
    if(!(ave==slant_line[0] && ave==slant_line[1] )){ goto err1; }
    view_mahoujin(str,n);
    return (0);/*正常終了*/
 err1:
  return (-1);/*平均値と合計値が合わない（この配列は魔方陣ではない）*/
 err2:
  return (-2);/*引数nnの値がおかしい*/
}
/* main作成中にヤル気が完全に失せたので放置 4/28/2011 
 *理解できなかった部分
 *・Makefileによるマクロ(gcc) -lm
 *・セグメントエラーと出たのでどっかで確保していない領域を参照しているようだ…。
 *ごめんもう無理、ダメっす。
 */
/* 4/28/2011
 *なんかできたー 
 * 修正部initの追加
 * '='を'+='に変更
 * その他微々
 * あと、負け犬なのでsprtを繋げなかったのでドライバ自作
 * 頑張って探しといてくれ…
 */
/*
int main(void){
int flag,n=9;
int str[]={4,9,2,3,5,7,8,1,6};
flag=IsMagicSquare(str,n);
printf("flag==%d",flag);
return(0);
}
*/
