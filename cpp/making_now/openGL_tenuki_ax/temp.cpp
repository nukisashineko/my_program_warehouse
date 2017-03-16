#include<cstdio>
#include<cmath>
#include<GL/glut.h>
/*--------------class contrl macro------------------------------------*/
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
/*---------------------------------------------------------*/
/*---------------------two parameters-------------------------*/
typedef struct two_double_parameter{ double a;double b; } Wd;
typedef struct two_int_parameter{ int a;int b; } Wi;
/*---------------------------------------------------------*/
/*---------------------class ------------------------------*/
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

/*---------------------------------------------------------*/
/*-------------------temp class control func------------------------------*/

void push_mouse(int button,int state,int x,int y);
void push_window_middle(int w,int h);
void calculate_p(void);
void calculate_radian(int x,int y);
void calculate_r(void);
void calculate_V(void);
double to_degree(double radian);
void rotatede_func(void(*func)(void));
/*---------------------------------------------------------*/
/*----global variable--------------*/
typedef enum {on,off,light_up,light_green,
					red,green,blue,yellow} FLAG;
int rubberband=0;
Temp pos;
/*---------------------------------*/
/*-----------function declare------------------*/
void push_array_point(int point[],int x,int y);
void set_light(FLAG flag);
void num_incf(void);
void num_decf(void);
void push_array_point(int point[],int x,int y);
void mouse_set_rubber_and_point(int button,int state,int x,int y);
void figure_and_rotation(void (*func)(void));
void parallelepiped_by_line(void);
void parallelepiped_by_face(void);
void square(GLdouble n);
void two_line_writer(int x0,int y0,int x1,int y1);
void two_line_writerw(int p1[],int x1,int y1);
void two_line_writerv(int p1[],int p2[]);
void figure_two_appear(void (*func)(void));
//void figure_some_appear(void (*func)(void),int n,int r,double add_count,double x,double y,double z);
//void figure_some_appear2(void (*func)(void),int n,int r,double add_count,double x,double y,double z);
/*---------------------------------------------*/
/*-------------print to debug------------------------*/
void mouseposition_to_term(int button,int state,int x,int y);
/*---------------------------------------------------------*/
/*-------------------date managment-------------------------*/
/*-------------------ex-html-------------------------------*/
void sence_ex_a_html(void);
void display_ex_a_html(void);
void scene_ex_a(void);
void display_ex_a(void);
void resize_ex_a(int w,int h);
void keyboard_ex_a(unsigned char key,int x,int y);
void init_ex_a(void);
/*---------------------------------------------------------*/
void idle(void);
void display(void);
void resize(int w,int h);
void init(void);
void mouse(int button,int state,int x,int y);
void motion(int x,int y);
void keyboard(unsigned char key,int x,int y);
int main(int argc,char* argv[]);
/*---------------------------------------------------------*/


/*------------------temp contrl func----------------------------------*/
void push_mouse(int button,int state,int x,int y){ pos.setmouse_pos(x,y); }
void push_window_middle(int w,int h){  pos.setwindow_middle(w/2.0,h/2.0);}
/*------------------------------------------------------*/
/*----------------- ex_a_func ----------------------------------*/
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
/*------------------------------------------------------*/
/*-------------memory line------------------------------*/
#define MAXPOINTS 100
	int pointnum=0;
	GLint point[MAXPOINTS][2];
	void print_array_point_of_line(void)
	{
		int i;
		if(pointnum>1){
			glColor3d(0.0,0.0,0.0);
			glBegin(GL_LINES);
			for(i=0;i<pointnum;++i){
					glVertex2iv(point[i]);
			}
			glEnd();
		}
	}
	void num_incf(void){ if(pointnum<MAXPOINTS-1)pointnum++; }
	void num_decf(void){ if(1<pointnum)pointnum--; }

/*-------------------------------------------------------*/
/*---------------2D writer----------------------------------*/
void two_line_writerv(int p1[],int p2[])
{
	glBegin(GL_LINES);
	glVertex2iv(p1);
	glVertex2iv(p2);
	glEnd();
}
void two_line_writerw(int p1[],int x1,int y1)
{
	glBegin(GL_LINES);
	glVertex2iv(p1);
	glVertex2i(x1,y1);
	glEnd();
}


void two_line_writer(int x0,int y0,int x1,int y1)
{
	glBegin(GL_LINES);
	glVertex2i(x0,y0);
	glVertex2i(x1,y1);
	glEnd();
}


void square(GLdouble n)
{
	glColor3d(1.0,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2d(n,n);
	glVertex2d(-n,n);
	glVertex2d(-n,-n);
	glVertex2d(n,-n);

	glEnd();
}
/*-----------------------------------------*/
/*---------------3D writer------------------------*/
	void parallelepiped_by_line(void)
{
	static GLdouble vertex[][3]={
	{0.0,0.0,0.0},
	{1.0,0.0,0.0},
	{1.0,1.0,0.0},
	{0.0,1.0,0.0},
	{0.0,0.0,1.0},
	{1.0,0.0,1.0},
	{1.0,1.0,1.0},
	{0.0,1.0,1.0}
	};
#define edge_MAX 12
	static int edge[edge_MAX][2]={
		{0,1},
		{1,2},
		{2,3},
		{3,0},
		{4,5},
		{5,6},
		{6,7},
		{7,4},
		{0,4},
		{1,5},
		{2,6},
		{3,7}
	};
	int i;

	glColor3d(0.0,0.0,0.0);
	glBegin(GL_LINES);
		for(i=0;i<edge_MAX;i++){
			glVertex3dv(vertex[edge[i][0]]);
			glVertex3dv(vertex[edge[i][1]]);
		}
	glEnd();
}
	void parallelepiped_by_face(void)
{
	static GLdouble vertex[][3]={
	{0.0,0.0,0.0},
	{1.0,0.0,0.0},
	{1.0,1.0,0.0},
	{0.0,1.0,0.0},
	{0.0,0.0,1.0},
	{1.0,0.0,1.0},
	{1.0,1.0,1.0},
	{0.0,1.0,1.0}
	};
#define face_MAX 6
	static int face[face_MAX][4]={
		{0,1,2,3},
		{1,5,6,2},
		{5,4,7,6},
		{4,0,3,7},
		{4,5,1,0},
		{3,2,6,7}
	};
	static GLdouble color[face_MAX][3]={
	{1.0,0.0,0.0},
	{0.0,1.0,0.0},
	{0.0,0.0,1.0},
	{1.0,1.0,0.0},
	{1.0,0.0,1.0},
	{0.0,1.0,1.0}
	};

	static GLdouble normal[face_MAX][3]={
	{0.0,0.0,-1.0},
	{1.0,0.0,0.0},
	{0.0,0.0,1.0},
	{-1.0,0.0,0.0},
	{0.0,-1.0,0.0},
	{0.0,1.0,0.0}
	};
int i,j;

	glColor3d(0.0,0.0,0.0);
	glBegin(GL_QUADS);
		for(i=0;i<face_MAX;i++){
//			glColor3dv(color[i]);
			glNormal3dv(normal[i]);
			for(j=0;j<4;j++){
			glVertex3dv(vertex[face[i][j]]);
			}
		}
	glEnd();
}


void figure_and_rotation(void (*func)(void))
{
	static int r=0;
//	glLoadIdentity();
//	gluLookAt(3.0,4.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
//	set_light(green);
	glPushMatrix();
	glRotated((double)r,0.0,1.0,0.0);
	set_light(red);
	func();
	glPopMatrix();
//	glFlush();
	glutSwapBuffers();
	if(++r>=360){ r=0; }
}
void figure_two_appear(void (*func)(void))
{
	static int r=0;
	glPushMatrix();
		glRotated((double)r,0.0,1.0,0.0);
		set_light(red);
		func();
		glPushMatrix();
			glTranslated(1.0,1.0,1.0);
			glRotated((double)(2*r),0.0,1.0,0.0);
			set_light(blue);
			func();
		glPopMatrix();
	glPopMatrix();
//	glFlush();
	glutSwapBuffers();
	if(++r>=360){ r=0; }
}
/*this is nothings*/
/*
void figure_some_appear(void (*func)(void),int n,
						double add_count=1.0,double x=0.0,double y=0.0,double z=0.0)
{
	static int r=0;
		figure_some_appear2(func,n,r,add_count,x,y,z);
	if(++r>=360){ r=0; }
}
void figure_some_appear2(void (*func)(void),int n,int r,
						double add_count=1.0,double x=0.0,double y=0.0,double z=0.0)
{
	if(n==0){ return; }
//	printf("n=%d,r=%d,x=%f,y=%f,z=%f,add=%f\n",n,r,x,y,z,add_count);
	glPushMatrix();
		glTranslated(x,y,z);
		figure_some_appear2(func,n-1,r,add_count,
						x+add_count,y+add_count,z+add_count);
	glPopMatrix();
}
*/
void club_appear(GLdouble n,FLAG flag,GLdouble x,GLdouble y,GLdouble z)
{
	glPushMatrix();
	glTranslated(x,y,z);
	set_light(flag);
	glutSolidCube(n);
	glPopMatrix();
}

void print_3club(void)
{
	club_appear(1.0,red,0.0,0.0,-3.0);
	club_appear(1.0,green,0.0,0.0,3.0);
	club_appear(1.0,blue,-3.0,0.0,0.0);
	club_appear(1.0,yellow,3.0,0.0,0.0);
}
void print_ground(void)
{
	static GLfloat ground[][4]={
		{0.6,0.6,0.6,1.0},
		{0.3,0.3,0.3,1.0}
	};
	int i,j;
	glBegin(GL_QUADS);
	glNormal3d(0.0,1.0,0.0);
	for(i=-5;i<5;i++){
		for(j=-5;j<5;j++){
				glMaterialfv(GL_FRONT,GL_DIFFUSE,ground[(i+j)&1]);
				glVertex3d((GLdouble)i,-0.5,(GLdouble)j);
				glVertex3d((GLdouble)i,-0.5,(GLdouble)(j+1));
				glVertex3d((GLdouble)(i+1),-0.5,(GLdouble)(j+1));
				glVertex3d((GLdouble)(i+1),-0.5,(GLdouble)j);
		}
	}
	glEnd();
}
/*------------------------------------------------*/
/*---------------set light---------------------------------*/
//typedef enum {on,light_up,off,red,green,bule,yellow} FLAG;
void set_light(FLAG flag)
{
	/*-----------light postion----------------*/
	static GLfloat light0pos[]={0.0,3.0,5.0,1.0};
	static GLfloat light1pos[]={5.0,3.0,0.0,1.0};
	/*-----------------------------------------*/
	/*-----------light color--------------------*/
	static GLfloat light_color_green[]={0.2,0.8,0.2,1.0};
	static GLfloat light_color_red[]={0.8,0.2,0.2,1.0};
	static GLfloat light_color_blue[]={0.2,0.2,0.8,1.0};
	static GLfloat light_color_yellow[]={0.8,0.8,0.2,1.0};
	/*-----------------------------------------*/
	switch(flag){
	case on:
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
//		glEnable(GL_LIGHT1);
		break;
	case light_up:
		glLightfv(GL_LIGHT0,GL_POSITION,light0pos);
//		glLightfv(GL_LIGHT1,GL_POSITION,light1pos);
		break;
	case light_green:
		glLightfv(GL_LIGHT1,GL_DIFFUSE,light_color_green);
		glLightfv(GL_LIGHT1,GL_SPECULAR,light_color_green);
	case green:
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,light_color_green);
		break;
	case red:
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,light_color_red);
		break;
	case blue:
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,light_color_blue);
		break;
	case yellow:
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,light_color_yellow);
		break;
	case off:
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		break;
	defalut:
			exit(1);
		break;
	}
}
/*---------------------------------------------------------*/
/*--------------to mouse function----------------------------------*/
//void mouse_play_rubberband(int button,int state,int x,int y){}

void mouse_set_rubber_and_point(int button,int state,int x,int y)
{
	static int x0,y0;
	switch(button){
		case GLUT_LEFT_BUTTON:
				push_array_point(point[pointnum],x,y);
//	printf("push=%d,%d,\n",point[pointnum][0],point[pointnum][1]);
				if(state==GLUT_UP){
					glColor3d(0.0,0.0,0.0);
					two_line_writerv(point[pointnum-1],point[pointnum]);
					glFlush();
					rubberband=0;
				}
				num_incf();
			break;
		case GLUT_MIDDLE_BUTTON: break;
		case GLUT_RIGHT_BUTTON: break;
		default: break;
	}

}
/*-----------------------------------------------------------------*/
/*-------------print to debug------------------------*/
void mouseposition_to_term(int button,int state,int x,int y)
{
	switch(button){
		case GLUT_LEFT_BUTTON: printf("left"); break;
		case GLUT_MIDDLE_BUTTON: printf("middle"); break;
		case GLUT_RIGHT_BUTTON: printf("right"); break;
	}
	printf(" button is ");
	switch(state){
		case GLUT_UP: printf("up"); break;
		case GLUT_DOWN: printf("down"); break;
	}
	printf(" at (%d,%d)\n",x,y);

}
/*---------------------------------------------------------*/
/*-------------------date managment-------------------------*/
void push_array_point(int point[],int x,int y)
{
	point[0]=x;
	point[1]=y;
}
/*---------------------------------------------------------*/
/*-------------------ex-html-------------------------------*/
void scene_ex_a(void)
{
	print_3club();
	print_ground();
}
void display_ex_a_html(void)
{
	static double ex=0.0,ez=0.0;
	static double r=0.0;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotated((double)r,0.0,1.0,0.0);
	glTranslated(ex,0.0,ez);
	set_light(light_up);
	scene_ex_a();
	glFlush();
}


void display_ex_a(void)
{
	static GLfloat lightpos[]={3.0,4.0,5.0,1.0};/*光源の位置*/

	static double ex=0.0,ez=0.0;/*視点の位置*/
	static double r=0.0;/*視点の向き*/

	/*画面クリア*/
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	/*モデルビュー変換行列の初期化*/
	glLoadIdentity();

	/*視点の移動*/
	glRotated(r,0.0,1.0,0.0);
	glTranslated(ex,0.0,ez);

	/*光源の位置を設定*/
	glLightfv(GL_LIGHT0,GL_POSITION,lightpos);


	/*シーンの描画*/
	scene_ex_a();

	glFlush();
}

void resize_ex_a(int w,int h)
{
	/*ウィンドウ全体をビューポートにする*/
	glViewport(0,0,w,h);

	/*透視変換行列の指定*/
	glMatrixMode(GL_PROJECTION);

	/*透視変換行列の初期化*/
	glLoadIdentity();
	gluPerspective(30.0,(double)w/(double)h,1.0,100.0);

	push_window_middle(w,h);

	/*モデルビュー変換行列の指定*/
	glMatrixMode(GL_MODELVIEW);
}

void keyboard_ex_a(unsigned char key,int x,int y)
{
	/*ESCかqをタイプしたら終了*/
	if(key=='\033'||key=='q'){
		exit(0);
	}
}

void init_ex_a(void)
{
	/*初期設定*/
	glClearColor(1.0,1.0,1.0,0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

/*---------------------------------------------------------*/
void idle(void){
	glutPostRedisplay();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
	glTranslated(3.0,0.0,0.0);
	set_light(yellow);
	glutSolidCube(1.0);
	glPopMatrix();
//	club_appear(1.0,yellow,3.0,0.0,0.0);
//	print_ground();
//	figure_two_appear(parallelepiped_by_face);
//	figure_some_appear(parallelepiped_by_face,2);
//	figure_and_rotation(parallelepiped_by_face);
//	figure_and_rotation(parallelepiped_by_line);
//	parallelepiped_by_line();
//	print_array_point_of_line();
	glFlush();

}

void resize(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-0.5,(GLdouble)w-0.5,(GLdouble)h-0.5,-0.5,-1.0,1.0);
//	glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
	gluPerspective(30.0,(double)w/(double)h,1.0,100.0);
//	glTranslated(0.0,0.0,-5.0);
//	gluLookAt(3.0,4.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
	gluLookAt(3.0,4.0,-10.0,0.0,0.0,0.0,0.0,1.0,0.0);
}
void init(void)

{
	glClearColor(1.0,1.0,1.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	set_light(on);
	set_light(light_up);
}

void mouse(int button,int state,int x,int y)
{
	mouseposition_to_term(button,state,x,y);
	push_mouse(button,state,x,y);
//	mouse_set_rubber_and_point(button,state,x,y);
	switch(button){
		case GLUT_LEFT_BUTTON:
//	printf("push=%d,%d,\n",point[pointnum][0],point[pointnum][1]);
				if(state==GLUT_DOWN){
					glutIdleFunc(idle);
				}else{
					glutIdleFunc(0);
				}
			break;
		case GLUT_MIDDLE_BUTTON: break;
		case GLUT_RIGHT_BUTTON:
				if(state==GLUT_DOWN){
					glutPostRedisplay();
				}
			break;
		default: break;
	}

}
void motion(int x,int y)
{
	static GLint savepoint[2];

	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_INVERT);
	if(rubberband){
		two_line_writerv(point[pointnum-1],savepoint);
	}
	two_line_writerw(point[pointnum-1],x,y);
	glFlush();
	glLogicOp(GL_COPY);
	glDisable(GL_COLOR_LOGIC_OP);
	push_array_point(savepoint,x,y);
	rubberband=1;

}
void keyboard(unsigned char key,int x,int y)
{
	switch(key){
		case'q':
		case'Q':
		case'\033':
				exit(0);
		defalut: break;
	}
}
int main(int argc,char* argv[])
{
glutInitWindowPosition(100,400);
glutInitWindowSize(320,240);
glutInit(&argc,argv);
//glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
glutCreateWindow(argv[0]);
glutDisplayFunc(display_ex_a_html);
glutReshapeFunc(resize_ex_a);
glutMouseFunc(mouse);
//glutMotionFunc(motion);
glutKeyboardFunc(keyboard);
init_ex_a();
glutMainLoop();
return(0);
}
