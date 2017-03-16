#include<cstdio>
using namespace std;
class Temp{
private:
	int i;
protected:
public:
	int b;
Temp (void){}
};

void print_my(void)
{
	printf("show me!\n");
}

/*-----------void func void---------------------*/
void pipe_func_repert_1(void(*func)(void),int n)
{
	if(func){
	for(int i=0;i<n;i++)
		func();
	}
	return;
}
void pipe_func_repert_2(void(*func)(void),int n)
{
	if(func&&n>1){
		pipe_func_repert_1(func,n-1);
	}
}
/*-----------------------------------------------*/

/*------------original func----------------------*/
void pipe_func(void(*func)(void))
{
	if(func){
	func();
	}
}
/*-----------------------------------------------*/
int main(int argc,char* argv[])
{
	pipe_func_repert(NULL,3);
return(0);
}
