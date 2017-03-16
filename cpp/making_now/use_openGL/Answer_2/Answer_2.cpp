/*  vim: set foldmethod=marker commentstring=//%s foldmarker={{{,}}} : */
#include <cstdio>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

using namespace std;


void display();
void reshape(int w, int h);
void SpecialKey(int key, int x, int y);
void menu(int val);


void DRAW_XYZ();
void DRAW_TRI();



inline void GLUT_INIT()
{
	glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(200,200);
}

inline void GLUT_CALL_FUNC()
{
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutSpecialFunc(SpecialKey);
}


inline void GLUT_SET_MENU()
{
	glutCreateMenu(menu);
	glutAddMenuEntry("NEVER", GL_NEVER);
	glutAddMenuEntry("LESS", GL_LESS);

	glutAddMenuEntry("EQUAL", GL_EQUAL);
	glutAddMenuEntry("LEQUAL", GL_LEQUAL);


	glutAddMenuEntry("GREATER", GL_GREATER);
	glutAddMenuEntry("NOTEQUAL", GL_NOTEQUAL);

	glutAddMenuEntry("GEQUAL", GL_GEQUAL);
	glutAddMenuEntry("ALWAYS", GL_ALWAYS);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}


inline void MY_INIT()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
}


int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	GLUT_INIT();
	glutCreateWindow("window name");
	GLUT_CALL_FUNC();
	GLUT_SET_MENU();
	MY_INIT();
	glutMainLoop();

	return 0;
}

/********[ここからコールバック]****************************************/
double z= 0;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


	DRAW_XYZ();


	glPushMatrix();
	glColor3d(0,1,0);
	DRAW_TRI();
	glPopMatrix();


	glPushMatrix();
	glColor3d(1,1,0);
	glTranslated(0,0,z);
	DRAW_TRI();
	glPopMatrix();


	glutSwapBuffers();


}


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void menu(int val)
{
	glDepthFunc(val);
	glutPostRedisplay();
}



/**********[ここから各種関数]***********************/

void DRAW_XYZ()
{
	glBegin(GL_LINES);

	glColor3d(0,1,0);//x
	glVertex2d(-100,0);
	glVertex2d(100, 0);

	glColor3d(1,0,0);//y
	glVertex2d(0,0);
	glVertex2d(0,100);

	glColor3d(0,0,1);//z
	glVertex3d(0,0,-100);
	glVertex3d(0,0, 100);
	glEnd();

}


void DRAW_TRI()
{
	glBegin(GL_TRIANGLES);

	glVertex2d(0,1);
	glVertex2d(-0.5, 0);
	glVertex2d(0.5, 0);
	glEnd();
}


void SpecialKey(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_UP:
		z-=0.1;
		break;

		case GLUT_KEY_DOWN:
		z+= 0.1;
		break;

		default:
		break;
	}
	glutPostRedisplay();
}
