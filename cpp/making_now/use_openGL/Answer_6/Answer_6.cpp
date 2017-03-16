/*  vim: set foldmethod=marker commentstring=//%s foldmarker={{{,}}} : */

#include <GL/glut.h>


//---------- プロトタイプ宣言 --------------//
void display();
void reshape(int w, int h);


//------------ OpenGLの初期化 ------------------//

void GLUT_CALL_FUNCs()
{
	        glutDisplayFunc(display);
	        glutReshapeFunc(reshape);
}


void OtherMyInit()
{
	        glClearColor(1.0, 1.0, 1.0, 1.0);
	        glEnable(GL_DEPTH_TEST);

}

void GLUT_INITs(int *argcp, char **argv)
{
	        glutInit(argcp,argv);
	        glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH);
	        glutInitWindowSize(640,480);
	        glutCreateWindow("glColorMaterial");
	        GLUT_CALL_FUNCs();

	        OtherMyInit();

}

//--------- メイン関数 ----------------//
int main(int argc, char **argv)
{

	        GLUT_INITs(&argc,argv);

	        glutMainLoop();

	        return 0;
}

//------------- ここから各種コールバック -----------------//
void display()
{
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	        glLoadIdentity();
	        gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	        glEnable(GL_LIGHTING);//光源の有効化
	        glEnable(GL_LIGHT0);
	        static float Light0Pos[]={-1,1,1,0}; //光源の位置
	        glLightfv(GL_LIGHT0, GL_POSITION, Light0Pos);//位置だけ設定(あとはデフォルト)

	        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	        glEnable(GL_COLOR_MATERIAL);
	        glColor3f(1,0,1);

	        glutSolidSphere(0.5,60,60);


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
