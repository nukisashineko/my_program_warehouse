#include<cstdio>
#include<cmath>
#include<GL/glut.h>
#define setgetd(setlocal,getlocal,local)\
void setlocal(double a){ local=a;}\
double getlocal(void){ return(local);}

#define setgetWi(setlocal,getlocal,local)\
void setlocal(int a,int b){ local.a=a;local.b=b;}\
Wi getlocal(void){ return(local);}
#define initWi(local) local.a=0;local.b=0

#define setgetWd(setlocal,getlocal,local)\
void setlocal(double a,double b){ local.a=a;local.b=b;}\
Wd getlocal(void){ return(local);}
#define initWd(local) local.a=0.0;local.b=0.0
using namespace std;
typedef struct two_double_parameter{ double a;double b; } Wd;
typedef struct two_int_parameter{ int a;int b; } Wi;
class Temp{
	private:
		Wd localP;//x,y
		Wd localV;//x,y
		Wd window_middle;//w,h
		Wi mouse_pos;//x,y
		double localr;
		double locala;
		double localt;
	protected:
	public:
	Temp(void){
		initWd(localP);
		initWd(localV);
		initWd(window_middle);
		initWi(mouse_pos);
		locala=0.0;
		localr=0.0;
		localt=0.0;
	};
	setgetWd(setP,getP,localP);
	setgetWd(setV,getV,localV);
	setgetWd(setwindow_middle,getwindow_middle,window_middle);
	setgetWi(setmouse_pos,getmouse_pos,mouse_pos);
	setgetd(seta,geta,locala);
	setgetd(setr,getr,localr);
	setgetd(sett,gett,localt);
};

	Temp pos;

void push_mouse(int button,int state,int x,int y){ pos.setmouse_pos(x,y); }
void push_window_middle(int w,int h){  pos.setwindow_middle(w/2.0,h/2.0);}
void calculate_p(void)
{
	Wd P=pos.getP();
	Wd V=pos.getV();
	double a=pos.geta();
	double t=pos.gett();
	pos.setP(V.a*t+P.a,V.b*t+P.b);
}
void calculate_radian(int x,int y)
{
	static double rad=0.0;
	static double old_rad=0.0;
	double t=pos.gett();
	rad=old_rad;
	rad=asin((double)x/pow((double)(x*x+y*y),0.5));
	pos.seta((rad-old_rad)/t);
}
void calculate_r(void)
{
	double a=pos.geta();
	double t=pos.gett();
	double r=pos.getr();
	pos.setr(a*t+r);
}
void calculate_V(void)
{
	Wd V=pos.getV();
	double r=pos.getr();
	double V_dash;
	V_dash=pow(V.a*V.a+V.b*V.b,0.5);
	pos.setV(V_dash*sin(r),V_dash*cos(r));
}
double to_degree(double radian){
	const static double PI=3.14159265;
	return(radian*180/PI);
}

void rotatede_func(void(*func)(void))
{
	Wd P=pos.getP();
	double r=pos.getr();
	glPushMatrix();
	glRotated(-r,-P.a,0,-P.b);
	func();
	glPopMatrix();
}

int main(int argc,char* argv[])
{
	printf("%f,%f",pos.getP().a,pos.getP().b);
return(0);
}
