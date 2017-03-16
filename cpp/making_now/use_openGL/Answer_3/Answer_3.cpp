/*  vim: set foldmethod=marker commentstring=//%s foldmarker={{{,}}} : */

#include <GL/glut.h>

//----------- プロトタイプ宣言 --------------//
void display();
void reshape(int w, int h);
void timer(int value);

void DRAW_XYZ();
void DRAW_TRI();

//------------- OpenGLの初期設定 ------------------//
void GLUT_INIT()
{
	        glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH); //ダブルバッファ、Zバッファ
	        glutInitWindowSize(640,480);
	        glutCreateWindow("Basic Animation");
}

void GLUT_CALL_FUNC()
{
	        glutDisplayFunc(display);
	        glutReshapeFunc(reshape);
	        glutTimerFunc(0,timer,17);
}

void MY_INIT()
{
	        glClearColor(1.0, 1.0, 1.0, 1.0);
}

//------------- メイン関数 ----------------//
int main(int argc, char **argv)
{
	        glutInit(&argc,argv);
	        
	        GLUT_INIT();
	        GLUT_CALL_FUNC();
	        MY_INIT();

	        glutMainLoop();

	        return 0;
}

//------------ ここからコールバック関数 ------------------//
void display()
{
	        static int r = 0;
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	        glEnable(GL_DEPTH_TEST);  //Zバッファ有効化
	        DRAW_XYZ();  //XYZ軸の描画


	        glPushMatrix();   //行列退避
	        glRotated(double(r), 0.0, 1.0, 0.0); //[2].回転
	        glTranslated(1,0,0); //[1].並行移動
	        glColor3d(0,1,0);
	        DRAW_TRI();
	        glPopMatrix(); //行列を戻す


	        glPushMatrix();
	        glTranslated(1,0,0); //[2].並行移動
	        glRotated(double(r), 0.0, 1.0, 0.0); //[1].回転
	        glColor3d(1,0,0);
	        DRAW_TRI();
	        glPopMatrix();


	        glColor3d(1,1,1); //色のリセット


	        glutSwapBuffers();

	        r = r + 1;
	        if(r > 360)
	        {
		                r= 0;
		        }
}

void reshape(int w, int h)
{
	        glViewport(0, 0, w, h);

	        glMatrixMode(GL_PROJECTION); //行列モード切替
	        glLoadIdentity();  //行列初期化
	        gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
	        
	        glMatrixMode(GL_MODELVIEW); //行列モード切替
	        glLoadIdentity();
	        gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

void timer(int t)
{
	        glutPostRedisplay();
	        glutTimerFunc(t,timer,17); //タイマー関数
}

//--------------- ここから各種関数 ----------------//
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
