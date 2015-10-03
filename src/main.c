#include "secretaria.h"

void glut_initialization(int *, char **);
void gl_initialization(void);
void initialization();
void reshape(int width, int height);

GLint WIDTH =800;
GLint HEIGHT=600;

int main(int argc,char **argv){

  glut_initialization(&argc,argv);
  gl_initialization();
  initialization();
  glutMainLoop();
  return 0;
}

void glut_initialization(int *argc, char **argv)
{
  glutInit(argc,argv);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
  glutCreateWindow("SECRETARIA IC");
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

}

void gl_initialization(){
  glClearColor(0,0,0,0);
  glEnable(GL_DEPTH_TEST); // VER SIGNIFICADO
  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_SMOOTH);
}

void initialization(){

    init_textures();


}

void reshape(int width, int height){
  glViewport(0,0,(GLint)width,(GLint)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0,width/(float)height,0.1,200.0);
  glMatrixMode(GL_MODELVIEW);
}
