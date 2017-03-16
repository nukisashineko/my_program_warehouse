/*  vim: set foldmethod=marker commentstring=//%s foldmarker={{{,}}} : */
#include <GL/glut.h>

//------ 各種外部変数 --------//
enum { OFF,ON };


//-------------  プロトタイプ宣言  ----------------//
void display();
void reshape(int w, int h);
void SpecialKey(int key, int x, int y);
void menu(int val);

void DRAW_XYZ();
void DRAW_TRI();


//------------ OpenGLの初期設定 ---------------//
void GLUT_INIT()
{
	        glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH);
	        glutInitWindowSize(640,480);
	        glutCreateWindow("Depth Buffer");
}

void GLUT_CALL_FUNC()
{
	        glutDisplayFunc(display);
	        glutReshapeFunc(reshape);
	        glutSpecialFunc(SpecialKey);
}


void GLUT_SET_MENU()
{
	        glutCreateMenu(menu);
	        glutAddMenuEntry("ON", ON);
	        glutAddMenuEntry("OFF", OFF);
	        glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void MY_INIT()
{
	        glClearColor(1.0, 1.0, 1.0, 1.0);
	        glEnable(GL_DEPTH_TEST); //zバッファ有効化
}


int main(int argc, char **argv)
{
	        glutInit(&argc,argv);
	        GLUT_INIT();

	        GLUT_CALL_FUNC();
	        GLUT_SET_MENU();
	        MY_INIT();
	        glutMainLoop();

	        return 0;
}

//------------ ここから各種コールバック -----------------//
double z = 0;
void draw_temp(void)
{
	        glPushMatrix();
	                glColor3d(0,1,0);
	                DRAW_TRI(); //描画
	        glPopMatrix();


	        glPushMatrix();
	                glColor3d(1,1,0);
	                glTranslated(0,0,z);
	                DRAW_TRI();  //描画
	        glPopMatrix();


}
void display()
{
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	        glLoadIdentity();
	        gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	        DRAW_XYZ(); //XYZ軸の描画
	        draw_temp();
	        glutSwapBuffers();

}


void reshape(int w, int h)
{
	        glViewport(0, 0, w, h);
	        glMatrixMode(GL_PROJECTION);
	        glLoadIdentity();
	        gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
	        glMatrixMode(GL_MODELVIEW);
}


void menu(int val)
{
	        switch(val)
	        {
		        case ON:
		                glEnable(GL_DEPTH_TEST);
		        break;

		        case OFF:
		                glDisable(GL_DEPTH_TEST);
		        break;
		        }

		        glutPostRedisplay(); //再描画

}

//キーボード処理
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

		        glutPostRedisplay(); //再描画
}


//----------- ここから各種関数 ---------------//
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
