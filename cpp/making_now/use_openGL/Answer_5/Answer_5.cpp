/*  vim: set foldmethod=marker commentstring=//%s foldmarker={{{,}}} : */

#include <GL/glut.h>

/************* 各種外部変数 ******************/
enum{Idx,Idy,Idz};
float NormalData[]={0,1,0};//


/********* プロトタイプ宣言 *********/
void LIGHT_INIT();

void display();
void reshape(int w, int h);
void specialkeydown(int key, int x, int y);
void DRAW_TRI();
void DRAW_NORMAL();
void SetMaterialGold();

/********** OpenGLの初期設定 ************/
void GLUT_INIT()
{
	        glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH);
	        glutInitWindowSize(640,480);
	        glutCreateWindow("Normal,Light,material");
}

void GLUT_CALL_FUNC()
{
	        glutDisplayFunc(display);
	        glutReshapeFunc(reshape);
	        glutSpecialFunc(specialkeydown);
}


void MY_INIT()
{
	        glClearColor(1.0, 1.0, 1.0, 1.0);

	        LIGHT_INIT();
	        glEnable(GL_NORMALIZE);//法線の有効化
	        glEnable(GL_DEPTH_TEST);
}



//光源の設定
void LIGHT_INIT()
{
	        glEnable(GL_LIGHTING);
	        glEnable(GL_LIGHT0);
}


/*********** メイン関数 ***************/
int main(int argc, char **argv)
{
	        glutInit(&argc,argv);
	        GLUT_INIT();
	        GLUT_CALL_FUNC();
	        MY_INIT();
	        glutMainLoop();

	        return 0;
}

/********[ここからコールバック]****************************************/
void display()
{

	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	        glLoadIdentity();
	        gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //視点の設定

	        static float Light0Pos[]={0,1,0,0}; //光源の位置
	        glLightfv(GL_LIGHT0, GL_POSITION, Light0Pos);//位置だけ設定(あとはデフォルト)

	        SetMaterialGold();
	        DRAW_TRI();  //描画
	        DRAW_NORMAL(); //法線の描画

	        glutSwapBuffers();  //ウィンドウに出力

}


void reshape(int w, int h)
{
	        glViewport(0, 0, w, h);  //ビューポートの設定

	        glMatrixMode(GL_PROJECTION);
	        glLoadIdentity();
	        gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0); //視野の設定
	        glMatrixMode(GL_MODELVIEW);
}

void specialkeydown(int key, int x, int y)
{
	        switch(key)
	        {
		        case GLUT_KEY_UP:
		                NormalData[Idz] -= 0.2;
		                break;

		        case GLUT_KEY_DOWN:
		                NormalData[Idz] += 0.2;
		                break;

		        case GLUT_KEY_RIGHT:
		                NormalData[Idx] += 0.2;
		                break;

		        case GLUT_KEY_LEFT:
		                NormalData[Idx] -= 0.2;
		                break;
		        }
		        display();

}



/**********[ここから各種関数]***********************/
void DRAW_TRI()
{
	        glBegin(GL_TRIANGLES);
	        glNormal3fv(NormalData);
	        glVertex3d(0,0,1);
	        glVertex3d(-1, 0,-1);
	        glVertex3d(1, 0,-1);
	        glEnd();
}

void DRAW_NORMAL()
{       
        glDisable(GL_LIGHTING); //光源効果OFF
        glDisable(GL_LIGHT0);
        
        glColor3d(0,0,0);
        glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3fv(NormalData);
        glEnd();
        glColor3d(1,1,1);

        glEnable(GL_LIGHTING); //光源効果ON
        glEnable(GL_LIGHT0);
}

void SetMaterialGold()
{
	        static GLfloat gold_amb[] = { 0.24725, 0.1995, 0.0745, 1.0 };
	        static GLfloat gold_diff[] = { 0.75164, 0.60648 , 0.22648, 1.0 };
	        static GLfloat gold_spe[] = { 0.628281, 0.555802,0.366065,1.0 };
	        static GLfloat gold_shin[] = { 51.2 };

	        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gold_amb);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gold_diff);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold_spe);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, gold_shin);

}
