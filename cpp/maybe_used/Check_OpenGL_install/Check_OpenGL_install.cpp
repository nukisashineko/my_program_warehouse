/*  vim: set foldmethod=marker commentstring=//%s foldmarker={{{,}}} : */
#include<iostream>
#include<GL/glut.h>
#define endl '\n'

char *CheckExtentions="GL_ARB_compatibility";

int main(int argc,char* argv[])
{
glutInitWindowPosition(100,400);
glutInitWindowSize(320,240);
glutInit(&argc,argv);
glutCreateWindow("Check OpenGL");
std::cout << "Vendor :"<<glGetString(GL_VENDOR)<<endl;
std::cout << "GPU :"<<glGetString(GL_RENDERER)<<endl;
std::cout << "OpenGL ver. :"<<glGetString(GL_VERSION)<<endl;

const unsigned char *str=glGetString(GL_EXTENSIONS);
std::string ext =(reinterpret_cast<const char *>(str));
std::cout<<endl;
if(ext.find(CheckExtentions)!=std::string::npos){
	std::cout<<CheckExtentions<<"....[OK]"<<endl;
}else{
	std::cout<<CheckExtentions<<"....[BAD]"<<endl;
}
return(0);
}
