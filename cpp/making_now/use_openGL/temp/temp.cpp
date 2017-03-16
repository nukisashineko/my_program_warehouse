/*  vim: set foldmethod=marker commentstring=//%s foldmarker={{{,}}} : */
#include<cstdio>
#include<cstdlib>
#include<GL/glut.h>
using namespace std;
class Temp{
private:
protected:
public:
Temp (void){ return;}
};

/*------------value declare----------------*/
enum {ON,OFF};
double z_over_flag;
/*---------------------------------------*/
/*------------func declare----------------*/
void idle(void);
void display(void);
void reshape(int w,int h);
void init(void);
void mouse(int button,int state,int x,int y);
void motion(int x,int y);
void keyboard(unsigned char key,int x,int y);
void write_x_line_2Dd(double n);
void draw_tri_model(void);
void draw_two_models(void);
void draw_xyz(void);
/*-------------------------------------*/
/*----------opengl func----------------*/
void idle(void){}
void display(void){//{{{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER);
	glLoadIdentity();
	gluLookAt(3.0,4.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
//	draw_xyz();
//	draw_two_models();
	write_x_line_2Dd(1.0);
	glColor3d(0.0,1.0,0.0);
	glutSwapBuffers();
}//}}}
void reshape(int w,int h){//{{{
	glViewport(0,0,w/2,h/2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0,(GLdouble)w/(GLdouble)h,1.0,100.0);
	glMatrixMode(GL_MODELVIEW);
}//}}}
void init(void){//{{{
	//back color white
	glClearColor(1.0,1.0,1.0,1.0);
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_DEPTH);
//	glutIgnoreKeyRepeat(GL_TRUE);
}//}}}
void mouse(int button,int state,int x,int y){//{{{
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
		printf("(%d,%d)で左ボタンが押されました。\n",x,y);
	}
}//}}}
// drug and passive motion funcs//{{{
void PassiveMotion(int x,int y){
	printf("PassiveMotion ! (%d,%d)\n",x,y);
}
void DrugMotion(int x,int y){
	printf("DrugMotion ! (%d,%d)\n",x,y);
}//}}}
// pressed and up keybord funcs //{{{
void keyboard(unsigned char key,int x,int y){
	printf("%c is pressed at (%d,%d)\n",key,x,y);
}
void keyboardup(unsigned char key,int x,int y){
	printf("%c is up at (%d,%d)\n",key,x,y);
}
#define case_specialkey_press_print(X) \
		case X: printf("specialkey is %s\n",#X); break
void specialkeydown(int key,int x,int y){
	switch(key){
	case GLUT_KEY_UP: z_over_flag-=0.1; break;
	case GLUT_KEY_DOWN: z_over_flag+=0.1; break;
	case_specialkey_press_print(GLUT_KEY_LEFT);
	case_specialkey_press_print(GLUT_KEY_RIGHT);
	}
	glutPostRedisplay();
}//}}}
void menu(int val){//{{{
	switch(val){
		case ON:
			glEnable(GL_DEPTH_TEST);
		break;
		case OFF:
			glDisable(GL_DEPTH_TEST);
		break;
	}
	glutPostRedisplay();
}//}}}
/*-------------------------------------*/


/*-----------nomal func----------------*/
void draw_xyz(void)//{{{
{
	glBegin(GL_LINES);
	glColor3d(0,1,0);
	glVertex2d(-100,0);
	glVertex2d(100,0);
	glColor3d(1,0,0);
	glVertex2d(0,0);
	glVertex2d(0,100);
	glColor3d(0,0,1);
	glVertex3d(0,0,-100);
	glVertex3d(0,0,100);
	glEnd();
}//}}}
void draw_two_models(void){//{{{
		glPushMatrix();
		glColor3d(0,1,0);
		draw_tri_model();
	glPopMatrix();
	glPushMatrix();
		glColor3d(1,1,0);
		glTranslated(0,0,z_over_flag);
		draw_tri_model();
	glPopMatrix();
}//}}}
void draw_tri_model(void){//{{{
	glColor3d(1,1,0);
	glBegin(GL_TRIANGLES);
	glVertex3d(0.0,1.0,0.0);
	glVertex3d(-0.5,0.0,0.0);
	glVertex3d(0.5,0.0,0.0);
	glEnd();
}//}}}
void write_x_line_2Dd(double n){/*{{{*/
	glBegin(GL_LINES);
	glVertex2d(-n,-n);
	glVertex2d(n,n);
	glVertex2d(-n,n);
	glVertex2d(n,-n);
	glEnd();
}/*}}}*/
/*-------------------------------------*/
void glut_my_init(void)
{
glutInitWindowPosition(100,400);
glutInitWindowSize(320,240);
glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
glutCreateWindow("Hello OpenGL");
}
void glut_call_func(void)
{
glutDisplayFunc(display);
glutMouseFunc(mouse);
glutReshapeFunc(reshape);
//glutPassiveMotionFunc(PassiveMotion);
glutMotionFunc(DrugMotion);
//glutKeyboardFunc(keyboard);
//glutKeyboardUpFunc(keyboardup);
glutSpecialFunc(specialkeydown);

}
void glut_set_menu(void)
{
	glutCreateMenu(menu);
	glutAddMenuEntry("ON",ON);
	glutAddMenuEntry("OFF",OFF);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc,char* argv[])
{
glutInit(&argc,argv);
glut_my_init();

glut_call_func();
glut_set_menu();
init();
glutMainLoop();
return(0);
}
