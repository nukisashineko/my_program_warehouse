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

/*------------func declare----------------*/
void idle(void);
void display(void);
void resize(int w,int h);
void init(void);
void mouse(int button,int state,int x,int y);
void motion(int x,int y);
void keyboard(unsigned char key,int x,int y);
/*-------------------------------------*/
/*----------opengl func----------------*/
void idle(void){}
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
void resize(int w,int h){}
void init(void){
	glClearColor(0.0,0.0,1.0,1.0);
}
/*-------------------------------------*/
/*-----------nomal func----------------*/
/*-------------------------------------*/

int main(int argc,char* argv[])
{
glutInitWindowPosition(100,400);
glutInitWindowSize(320,240);
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_RGBA);
glutCreateWindow("Hello OpenGL");
glutDisplayFunc(display);
init();
glutMainLoop();
return(0);
}
