#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#define fun(key_char,y,new_y,flag) \
if(key==key_char){\
	y=new_y;\
	printf("key=%c,%s=%f\n",key_char,#y,y);\
	if(flag!=1){flag=1;}\
}


void scene(void)
{
	/*物体の色*/
	static GLfloat red[]={0.8,0.2,0.2,1.0};
	static GLfloat green[]={0.2,0.8,0.2,1.0};
	static GLfloat blue[]={0.2,0.2,0.8,1.0};
	static GLfloat yellow[]={0.8,0.8,0.2,1.0};
	static GLfloat ground[][4]={
		{0.6,0.6,0.6,1.0},
		{0.3,0.3,0.3,1.0}
	};

	int i,j;

	/*赤い箱*/
	glPushMatrix();
	glTranslated(0.0,0.0,-3.0);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,red);
	glutSolidCube(1.0);
	glPopMatrix();

	/*緑の箱*/
	glPushMatrix();
	glTranslated(0.0,0.0,3.0);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,green);
	glutSolidCube(1.0);
	glPopMatrix();

	/*青い箱*/
	glPushMatrix();
	glTranslated(-3.0,0.0,0.0);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,blue);
	glutSolidCube(1.0);
	glPopMatrix();

	/*黄色い箱*/
	glPushMatrix();
	glTranslated(3.0,0.0,0.0);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,yellow);
	glutSolidCube(1.0);
	glPopMatrix();

	/*地面*/
	glBegin(GL_QUADS);
	glNormal3d(0.0,1.0,0.0);
	for(j=-5;j<5;++j){
		for(i=-5;i<5;++i){
			glMaterialfv(GL_FRONT,GL_DIFFUSE,ground[(i+j)&1]);
			glVertex3d((GLdouble)i,-0.5,(GLdouble)j);
			glVertex3d((GLdouble)i,-0.5,(GLdouble)(j+1));
			glVertex3d((GLdouble)(i+1),-0.5,(GLdouble)(j+1));
			glVertex3d((GLdouble)(i+1),-0.5,(GLdouble)j);
		}
	}
	glEnd();
}

	static double ex=0.0,ey=0.0,ez=0.0;/*視点の位置*/
	static double r=1.0,rx=0.0,ry=1.0,rz=0.0;/*視点の向き*/

void display(void)
{
	static GLfloat lightpos[]={3.0,4.0,5.0,1.0};/*光源の位置*/


	/*画面クリア*/
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	/*モデルビュー変換行列の初期化*/
	glLoadIdentity();

/*視点の移動*/
//	glRotated(r,rx,ry,rz);
//	glTranslated(ex,ey,ez);
	gluLookAt(ex,ey,ez,0.0,0.0,0.0,rx,ry,rz);

	/*光源の位置を設定*/
	glLightfv(GL_LIGHT0,GL_POSITION,lightpos);

	/*シーンの描画*/
	scene();

	glFlush();
}

void resize(int w,int h)
{
	/*ウィンドウ全体をビューポートにする*/
	glViewport(0,0,w,h);

	/*透視変換行列の指定*/
	glMatrixMode(GL_PROJECTION);

	/*透視変換行列の初期化*/
	glLoadIdentity();
	gluPerspective(30.0,(double)w/(double)h,1.0,100.0);

	/*モデルビュー変換行列の指定*/
	glMatrixMode(GL_MODELVIEW);
}

int flag=0,r_flag=0;
double add_count=0.0;
void keyboard(unsigned char key,int x,int y)
{	/*ESCかqをタイプしたら終了*/
	double localr,t;
	if(key=='\033'||key=='q'){
		exit(0);
	}
	if(key=='w'||key=='e'){
		add_count=(key=='w')?add_count+0.1:add_count - 0.1;
		printf("add_count=%d\n",add_count);
		flag=1;
	}
		if(key=='r'||key=='r'){
		r=ex=ey=ez=rx=ry=rz=0.0;
		add_count=0;
		flag=1;
	}
		fun('4',ex,ex+add_count,flag);
		fun('6',ex,ex-add_count,flag);
		fun('8',ez,ez+add_count,flag);
		fun('2',ez,ez-add_count,flag);
		fun('0',ey,ey+add_count,flag);
		fun('5',ey,ey-add_count,flag);
		fun('z',rx,rx+add_count,flag);
		fun('a',rx,rx-add_count,flag);
		fun('x',rz,rz+add_count,flag);
		fun('s',rz,rz-add_count,flag);
		fun('c',ry,ry+add_count,flag);
		fun('d',ry,ry-add_count,flag);
		fun('v',r,r+add_count*10,flag);
		fun('f',r,r-add_count*10,flag);
		fun('w',add_count,add_count+ 0.5,flag);
		fun('e',add_count,add_count- 0.5,flag);
		fun('7',ex,ex+add_count,flag);
		fun('7',ez,ez+add_count,flag);
		fun('9',ex,ex-add_count,flag);
		fun('9',ez,ez+add_count,flag);
		fun('1',ex,ex+add_count,flag);
		fun('1',ez,ez-add_count,flag);
		fun('3',ex,ex-add_count,flag);
		fun('3',ez,ez-add_count,flag);


if(flag){
		display();
		flag=0;
	}
}

void keyboard2(unsigned char key,int x,int y)
{	/*ESCかqをタイプしたら終了*/
	double localr,t;
	if(key=='\033'||key=='q'){
		exit(0);
	}
	if(key=='w'||key=='e'){
		add_count=(key=='w')?add_count+0.1:add_count - 0.1;
		printf("add_count=%d\n",add_count);
		flag=1;
	}
		if(key=='r'||key=='r'){
		r=ex=ey=ez=rx=ry=rz=0.0;
		add_count=0;
		flag=1;
	}
	if(key=='v'||key=='f'){
		r=(key=='v')?r+add_count*10:r-add_count*10;
		printf("r=%f\n",r);
		flag=1;
	}
	if(key=='z'||key=='a'){
		rx=(key=='z')?rx+add_count:rx-add_count;
		printf("rx=%f\n",rx);
		flag=1;
	}
	if(key=='x'||key=='s'){
		ry=(key=='x')?ry+add_count:ry-add_count;
		printf("ry=%f\n",ry);
		flag=1;
	}
	if(key=='c'||key=='d'){
		rz=(key=='c')?rz+add_count:rz-add_count;
		printf("rz=%f\n",rz);
		flag=1;
	}
	if(key=='4'||key=='6'){
		ex=(key=='4')?ex+add_count:ex-add_count;
		printf("ex=%f\n",ex);
		flag=1;
	}
	if(key=='8'||key=='2'){
		ez=(key=='8')?ez+add_count:ez-add_count;
		printf("ez=%f\n",ez);
		flag=1;
	}
	if(key=='0'||key=='5'){
		ey=(key=='0')?ey+add_count:ey-add_count;
		printf("ey=%f\n",ey);
		flag=1;
	}
	if(key=='7'){
		ex=ex+add_count;
		ez=ez+add_count;
		printf("ex=%f\n",ex);
		printf("ez=%f\n",ez);
		flag=1;
	}
	if(key=='9'){
		ex=ex-add_count;
		ez=ez+add_count;
		printf("ex=%f\n",ex);
		printf("ez=%f\n",ez);
		flag=1;
	}
	if(key=='1'){
		ex=ex+add_count;
		ez=ez-add_count;
		printf("ex=%f\n",ex);
		printf("ez=%f\n",ez);
		flag=1;
	}
	if(key=='3'){
		ex=ex-add_count;
		ez=ez-add_count;
		printf("ex=%f\n",ex);
		printf("ez=%f\n",ez);
		flag=1;
	}
	if(key=='g'){
		localr=sqrt(ex*ex+ez*ez);
		t=acos(ex/localr)+0.314;
	     if(0<ex&&0<ez)r_flag=1;
	else if(ex<0&&0<ez)r_flag=2;
	else if(ex<0&&ez<0)r_flag=3;
	else if(ex<0&&0<ez)r_flag=4;
	if(r_flag==1){
		ex= localr*cos(t);ez= localr*sin(t);
	}if(r_flag==2){
		ex=-localr*cos(t);ez= localr*sin(t);
	}if(r_flag==3){
		ex=-localr*cos(t);ez=-localr*sin(t);
	}if(r_flag==4){
		ex= localr*cos(t);ez=-localr*sin(t);
	}

		printf("localr=%f\n",localr);
		printf("t=%f\n",t);
		printf("ex=%f\n",ex);
		printf("ez=%f\n",ez);
		flag=1;
	}


if(flag){
		display();
		flag=0;
	}

}
void keyboard3(unsigned char key,int x,int y)
{
	/*ESCかqをタイプしたら終了*/
	if(key=='\033'||key=='q'){
		exit(0);
	}
	if(key=='a'||key=='A'){
		add_count=(key=='a')?add_count+0.1:add_count-0.1;
		printf("add_count=%d\n",add_count);
		flag=1;
	}
	if(key=='r'||key=='R'){
		r=(key=='r')?r+add_count:r-add_count;
		printf("r=%f\n",r);
		flag=1;
	}
	if(key=='x'||key=='X'){
		ex=(key=='x')?ex+add_count:ex-add_count;
		printf("ex=%f\n",ex);
		flag=1;
	}
	if(key=='z'||key=='Z'){
		ez=(key=='z')?ez+add_count:ez-add_count;
		printf("ez=%f\n",ez);
		flag=1;
	}
	if(key=='y'||key=='Y'){
		ey=(key=='y')?ey+add_count:ey-add_count;
		printf("ey=%f\n",ey);
		flag=1;
	}
	if(key=='u'||key=='U'){
		rx=(key=='u')?rx+add_count:rx-add_count;
		printf("rx=%f\n",rx);
		flag=1;
	}
	if(key=='i'||key=='I'){
		ry=(key=='i')?ry+add_count:ry-add_count;
		printf("ry=%f\n",ry);
		flag=1;
	}
	if(key=='o'||key=='O'){
		rz=(key=='o')?rz+add_count:rz-add_count;
		printf("rz=%f\n",rz);
		flag=1;
	}
	if(key=='s'||key=='S'){
		ex=ey=ez=rx=ry=rz=0.0;
		add_count=0;
		flag=1;
	}
if(flag){
		gluLookAt(ex,ey,ez,0.0,0.0,0.0,rx,ry,rz);
		display();
		flag=0;
	}
}

void init(void)
{
	/*初期設定*/
	glClearColor(1.0,1.0,1.0,0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

int main(int argc,char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
	return(0);
}
