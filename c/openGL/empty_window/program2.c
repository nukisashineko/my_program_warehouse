#include<stdlib.h>
#include<GL/glut.h>

GLdouble vertex[][3]={
	{0.0,0.0,0.0},
	{1.0,0.0,0.0},
	{1.0,1.0,0.0},
	{0.0,1.0,0.0},
	{0.0,0.0,1.0},
	{1.0,0.0,1.0},
	{1.0,1.0,1.0},
	{0.0,1.0,1.0}
};
/*
int edge[][2]={
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
*/
int face[][4]={
	{0,1,2,3},
	{1,5,6,2},
	{5,4,7,6},
	{4,0,3,7},
	{4,5,1,0},
	{3,2,6,7}
};
/*
GLdouble color[][3]={
	{1.0,0.0,0.0},
	{0.0,1.0,0.0},
	{0.0,0.0,1.0},
	{1.0,1.0,0.0},
	{1.0,0.0,1.0},
	{0.0,1.0,1.0}
};
*/
GLdouble normal[][3]={
	{0.0,0.0,-1.0},
	{1.0,0.0,0.0},
	{0.0,0.0,1.0},
	{-1.0,0.0,0.0},
	{0.0,-1.0,0.0},
	{0.0,1.0,0.0}
};
GLfloat light0pos[]={0.0,3.0,5.0,1.0};
GLfloat light1pos[]={5.0,3.0,0.0,1.0};
GLfloat green[]={0.0,1.0,0.0,1.0};
GLfloat red[]={0.8,0.2,0.2,1.0};
GLfloat blue[]={0.2,0.2,0.8,1.0};
void cube(void)
{
	int i;
	int j;

	glBegin(GL_QUADS);
	for(j=0;j<6;++j){
		glNormal3dv(normal[j]);
		for(i=0;i<4;++i){
			glVertex3dv(vertex[face[j][i]]);
		}
	}
	glEnd();
}

void idle(void)
{
	glutPostRedisplay();
}

void display(void)
{
	int i;
	int j;
	static int r=0;/*回転角*/
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
/*
glRotated(25.0,0.0,1.0,0.0);
glBegin(GL_POLYGON);
glColor3d(1.0,0.0,0.0);
glVertex2d(-0.9,-0.9);
glColor3d(0.0,1.0,0.0);
glVertex2d(0.9,-0.9);
glColor3d(0.0,0.0,1.0);
glVertex2d(0.9,0.9);
glColor3d(1.0,1.0,0.0);
glVertex2d(-0.9,0.9);
*/
glClear(GL_COLOR_BUFFER_BIT);
glLoadIdentity();
/*視点位置と視線方向*/
gluLookAt(3.0,4.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
/*光源の位置設定*/
glLightfv(GL_LIGHT0,GL_POSITION,light0pos);
glLightfv(GL_LIGHT1,GL_POSITION,light1pos);
/*モデルビュー変換行列の保存*/
glPushMatrix();
/*図形の回転*/
glRotated((double)r,0.0,1.0,0.0);
/*図形の描画*/
/*glColor3d(0.0,0.0,0.0);*/
/*図形の描画*/
cube();
/* 二つ目の図形の描画 */
	glPushMatrix();
	glTranslated(1.0,1.0,1.0);
	glRotated((double)(2*r),0.0,1.0,0.0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,blue);
	cube();
	glPopMatrix();
	/*モデルビュー変換行列の復帰*/
	glPopMatrix();

/*図形の色(赤)*/
glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,red);
/*
glBegin(GL_LINES);
for(i=0;i<12;++i){
	glVertex3dv(vertex[edge[i][0]]);
	glVertex3dv(vertex[edge[i][1]]);
}
glEnd();
*/
glBegin(GL_QUADS);
for(j=0;j<6;++j){
	glNormal3dv(normal[j]);
	for(i=0;i<4;++i){
		glVertex3dv(vertex[face[j][i]]);
	}
}
glEnd();

/*glFlush();*/
glutSwapBuffers();
/*一周回ったら回転角を0に戻す*/
if(++r>=360)r=0;
}
void resize(int w,int h)
{
/*ウィンドウ全体をビューポートにする*/
glViewport(0,0,w,h);
/*透視変換行列の設定*/
glMatrixMode(GL_PROJECTION);
/*変換行列の初期化*/
glLoadIdentity();
/*スクリーン上の表示領域をビューポートの大きさに比例させる*/
/*glOrtho(-w/200.0,w/200.0,-h/200.0,h/200.0,-1.0,1.0);*/
/*glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);*/
gluPerspective(30.0,(double)w/(double)h,1.0,100.0);
/*
glTranslated(0.0,0.0,-5.0);
gluLookAt(3.0,4.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
*/
/*モデルビュー変換行列の設定*/
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(3.0,4.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
}
void mouse(int button,int state,int x,int y)
{
	switch(button){
		case GLUT_LEFT_BUTTON:
		if(state==GLUT_DOWN){
			/*アニメーション開始*/
			glutIdleFunc(idle);
		}
		else{
			/*アニメーション停止*/
			glutIdleFunc(0);
		}
		break;
		case GLUT_RIGHT_BUTTON:
		if(state==GLUT_DOWN){
			/*コマ送り(1ステップだけ進める)*/
			glutPostRedisplay();
		}
		break;
		default:
		break;
	}
}
void keyboard(unsigned char key,int x,int y)
{
	switch(key){
		case 'q':
		case 'Q':
		case '\033':/*'\033'はESCのASCIIコード*/
		exit(0);
		default:
		break;
	}
}


void init(void)
{
glClearColor(1.0, 1.0, 1.0, 1.0);
glEnable(GL_DEPTH_TEST);
glEnable(GL_CULL_FACE);
/*
glCullFace(GL_BACK);
*/
glCullFace(GL_FRONT);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_LIGHT1);
glLightfv(GL_LIGHT1,GL_DIFFUSE,green);
glLightfv(GL_LIGHT1,GL_SPECULAR,green);
}

int main(int argc,char *argv[])
{
glutInitWindowPosition(100,100);
glutInitWindowSize(320,240);
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
glutCreateWindow(argv[0]);
glutDisplayFunc(display);
glutReshapeFunc(resize);
glutMouseFunc(mouse);
glutKeyboardFunc(keyboard);
init();
glutMainLoop();
return 0;
}
