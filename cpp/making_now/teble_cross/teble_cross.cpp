/*  vim: set foldmethod=marker commentstring=//%s foldmarker={{{,}}} : */
#include<cstdio>
using namespace std;

/*------------func declare----------------*/
void print_d(int d[],int n){
	for(int i=0;i<n;i++){
		printf("%d",d[i]);
	}
	puts("");

}
/*-------------------------------------*/

/*-----------nomal func----------------*/
class Panel{
private:
int _left,_right,_above,_under,_number;
protected:
public:
int left(void){return (_left);}
int right(void){return (_right);}
int above(void){return (_above);}
int under(void){return (_under);}
int number(void){return (_number);}
Panel(int l,int r,int a,int u,int n){
_left=l;_right=r;_above=a;_under=u;_number=n;
return;}
};
#define N 9
int func(void){
int d[N]={1,2,3,4,5,6,7,8,9};
	for(int i=0;i<N;i++){
		for(int k=0;k<i;k++){
//			Panel temp=d[0];
			int temp=d[0];
			for(int j=0;j<i-1;j++)
				d[j]=d[j+1];
			d[i-1]=temp;
			print_d(d,N);
//			if(is_clear(d)){ print_panel(d); return 1; };
		}
		
	}
	return 0;
		
}


/*-------------------------------------*/

int main(int argc,char* argv[])
{
func();
return(0);
}
