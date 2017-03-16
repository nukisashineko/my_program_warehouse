/*  vim: set foldmethod=marker commentstring=//%s foldmarker={{{,}}} : */

#include <GL/glut.h>

//------------ 各種データ構造 ------------------//
struct SPOTLIGHT
{
	        //各種パラメータ
	        float pos[4];
	        float amb[4];
	        float diff[4];
	        float spec[4];

	        //スポットライト用のパラメータ
	        float spotDir[3]; //向き
	        float spotExp; //減衰率
	        float spotCutoff; //照らす角度
} ;

SPOTLIGHT SpotLight={
	        {0,1,0,1},//位置
	        {0,0,0,0},
	        {1,1,1,1},
	        {1,1,1,1},
	        //スポットライト用パラメータ
	        {0,-1,0},//向き
	        20, //減衰率
	        20 //角度
};


//---------- プロトタイプ宣言 --------------//
void SET_UP_LIGHT();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void SpecialKey(int key, int x, int y);
void DRAW_XYZ();
void DRAW_FLOOR(float x,float y,float width);
void DRAW_LIGHT_POS(float *position);


//---------------- [OpenGLの初期設定] --------------------//
void GLUT_INIT()
{
	        glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH);
	        glutInitWindowSize(640,480);
	        glutCreateWindow("spot light");
}

void GLUT_CALL_FUNC()
{
	        glutDisplayFunc(display);
	        glutReshapeFunc(reshape);
	        glutKeyboardFunc(keyboard);
	        glutSpecialFunc(SpecialKey);
}

void MY_INIT()
{
	        glClearColor(0.0, 0.0, 0.0, 1.0);
	        SET_UP_LIGHT();
	        glEnable(GL_DEPTH_TEST);
}

//光源の設定
void SET_UP_LIGHT()
{
	        glEnable(GL_LIGHTING);
	        glEnable(GL_LIGHT0);

	        glLightfv(GL_LIGHT0, GL_AMBIENT, SpotLight.amb);
	        glLightfv(GL_LIGHT0, GL_DIFFUSE, SpotLight.diff);
	        glLightfv(GL_LIGHT0, GL_SPECULAR, SpotLight.spec);

	        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, SpotLight.spotExp);
	        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, SpotLight.spotCutoff);
	        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, SpotLight.spotDir);
}

//-------- ここからメイン関数 -------------//
int main(int argc, char **argv)
{
	        glutInit(&argc,argv);
	        GLUT_INIT();

	        GLUT_CALL_FUNC();
	        MY_INIT();
	        glutMainLoop();

	        return 0;
}


//------- ここから各種コールバック -----------//
void display()
{
	        static const float floor_Color[] = { 0.0, 1, 0.0, 1.0 };

	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	        glLoadIdentity();
	        gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	        //スポットライトの設定
	        glLightfv(GL_LIGHT0, GL_POSITION, SpotLight.pos);
	        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, SpotLight.spotDir);
	        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, SpotLight.spotCutoff);
	        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, SpotLight.spotExp);

	        DRAW_XYZ();
	        DRAW_LIGHT_POS(SpotLight.pos);

	        glPushMatrix();
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, floor_Color);
	        glutSolidSphere(0.5,60,60);
	        DRAW_FLOOR(64,64,2);
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


void keyboard(unsigned char key, int x, int y)
{

	        switch(key)
	        {
		        case'u':
		                SpotLight.spotCutoff++;
		        break;

		        case'i':
		                SpotLight.spotCutoff--;
		                if(SpotLight.spotCutoff < 0){
			                        SpotLight.spotCutoff = 0;
			                }
			        break;

			        case'r':
			                SpotLight.spotExp++;
			        break;

			        case'e':
			                SpotLight.spotExp--;
			                if(SpotLight.spotExp < 0){
				                        SpotLight.spotExp = 0;
				                }
				        break;

				        }

				        glutPostRedisplay();
}


void SpecialKey(int key, int x, int y)
{
	        switch (key) 
	        {
		        case GLUT_KEY_UP:
		                SpotLight.spotDir[2]-=0.1;
		        break;

		        case GLUT_KEY_DOWN:
		                SpotLight.spotDir[2]+=0.1;
		        break;

		        case GLUT_KEY_RIGHT:
		                SpotLight.spotDir[0]+=0.1;
		        break;

		        case GLUT_KEY_LEFT:
		                SpotLight.spotDir[0]-=0.1;
		        break;

		        default:
		        break;
		        }

		        glutPostRedisplay();

}

//-------- ここから各種関数 ---------//
void DRAW_XYZ()
{

	        glDisable(GL_LIGHTING);
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
	        glEnable(GL_LIGHTING);

}


void DRAW_FLOOR(float x,float y,float width)
{

	        static float move = width *0.5;

	        glPushMatrix();
	        glRotatef(-90.0, 1, 0, 0);
	        glTranslatef(-move, -move, 0.0);

	        static float dw = width / x;//メッシュの細かさ
	        static float dh = width / y;

	        glNormal3f(0.0, 0.0, 1.0);

	        for (int j = 0; j < y; ++j)
	        {
		                glBegin(GL_TRIANGLE_STRIP);
		                for (int i = 0; i <= x; ++i){
			                        glVertex2f(dw * i, dh * (j + 1));
			                        glVertex2f(dw * i, dh * j);
			                }
			                glEnd();
			        }

			        glPopMatrix();

		}

		void DRAW_LIGHT_POS(float *position)
		{

			        glDisable(GL_LIGHTING);
			        glPointSize(5);
			        glBegin(GL_POINTS);
			        glColor3d(1,1,0);
			        glVertex3fv(position);
			        glEnd();
			        glPointSize(1);
			        glEnable(GL_LIGHTING);

		}
