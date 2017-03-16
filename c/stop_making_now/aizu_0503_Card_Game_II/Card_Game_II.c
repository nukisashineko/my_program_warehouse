#include<stdio.h>
void print_division_to_r(int a,int b,int r);
void init_date(int date[][],int n,int k);
void SwapStr(int str[],int n,int str_tail);
Sort(int str[],int n,int str_tail);
Card_Game_2(int date[],int depth[],int count,int k,int n,bool m);

my_pow(int x,int y);
print_vector_num(int date[],int lenth,int base);
division_in_vector(int date[],int n,int lenth,int base);

#if 0
void print_division_to_r(int a,int b,int r){
	int i;
	printf("%d.",a/b);
	a%=b*10;
	for(i=0;i<r;i++){ 
	printf("%d",a/b);
	a=a%b*10;
	}
		return;
}

void init_date(int date[][],int n,int k){
	int i,j;
	for(i=0;i<k;i++)
		for(j=0;j<n;j++)
			date[i][j]=i;
	return;
}

void SwapStr(int str[],int n,int str_tail){
  int i,temp,k=str_tail-n;
  temp=str[k];
  for(i=k;i<str_tail;i++)
    str[i]=str[i+1];
  str[str_tail]=temp;
  return;
 }
void Sort(int str[],int n,int str_tail){
  int i;
  static int count=0;
  if(n>1)
      for(i=0;i<n+1;i++){
      Sort(str,n-1,str_tail);
      SwapStr(str,n,str_tail-1);
    }
  else{
	init_depth((int [])depth);
	if( Card_Game_2((int [][])date,(int [])depth,count=0,k,n,m) )
		count++;
  }
  return(count);
}

//#define K 10
//#define N 3

bool Card_Game_2(int date[],int depth[],int count,int k,int n,bool m){
//	int date[K][N];
//	int depth[K];
	int k,n;
//	int count=0;
//	init_date(date);
	while(1){
		if(depth[k] == N){
				if(m){ return (Card_Game_2(date,depth,count,k,n,false)) ; }
				return(false);/*false_end*/ 
		}
		if(depth[k] == N-1){ count++; }
		if(count == K-1){ return(ture);/*ture_end*/ }
		k=date[k][depth[k]]
		depth[k]++;
	}
}
#endif
int main(void){
	int k,n,m,count,r;
	bool m;
	int str[]={2222,2222,2222,2222 }
	int *date,*depth;
	division_in_vector(str,2,3,10000);
	print_vector_num(str,3,10000);
	date=(int *)malloc(sizeof(int)*k*n);
	depth=(int *)malloc(sizeof(int)*k);
	
//	init_date((int [][])date,n,k);
//	count=sort((int [])date,k*n-1,k*n);

//	init_depth((int [])depth);
//	Card_Game_2((int [][])date,(int [])depth,count=0,k,n,m);
//	count++;

	print_division_to_r(count,kaijou(k),r);
//	kaijou(int) is retuen (100!>=x>=1!)

	free(depth);
	free(date);
	return(0);
}

void kaijou(int date[],int n){
	
}

void multiplication_in_vector(int date[],int n,int lenth){ 
	int i,quotient,remainder;// 商、余
	for(i=lenth;i>0;i--){
		date[i]*=n;
		if(i>0){ date[i+1]+=date[i]/N; }//date[i+1]=quotient=date[i]/N /* 繰り上がり */
		if(i>0){ date[i]%=N; }//date[i]=remainder=date[i]%N /* 桁揃え */
	}
	return;
 }

int my_pow(int x,int y){
int i,ans=1;
for(i=0;i<y;i++){ ans*=x; }
return(ans);
}
void print_vector_num(int date[],int lenth,int base){
	int i,quotient,remainder;// 商、余
	for(i=0;i<lenth;i++){
		printf("%d",date[lenth]);
	}
	return;
}
void division_in_vector(int date[],int n,int lenth,int base){ 
	int i,quotient,remainder;// 商、余
	for(i=lenth;i>0;i--){
		date[i]/=n;
		if(i>0){ date[i-1]+=(date[i]%n)*base; }//date[i-1]=remainder=date[i]/N /* 繰り下がり */
		if(i>0){ date[i]/=n; }//date[i]=quotient=date[i]%N /* 桁揃え */
	}
	return;
 }