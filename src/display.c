#include "secretaria.h"

GLfloat cam[3]={0.0,7.0,5.0};
GLfloat center[3]={0.0,3.0,0.0};
GLfloat tetaxz=5;
GLfloat tetayz=5;
GLfloat raioxz=50;
GLuint texture_id[NUM_TEX];
int door_angle = 0;

void draw_wall(float x1,float y1, float z1,
			float x2, float y2, float z2,
			float x3, float y3, float z3,
			float x4, float y4, float z4, int tex_index){

	glBindTexture(GL_TEXTURE_2D, texture_id[tex_index]);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( x1, y1, z1 );
    glTexCoord2f(1.0f, 0.0f); glVertex3f( x2, y2, z2 );
    glTexCoord2f(1.0f, 1.0f); glVertex3f( x3, y3, z3 );
    glTexCoord2f(0.0f, 1.0f); glVertex3f( x4, y4, z4 );
  glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void draw_door(float x1,float y1, float z1,
			float x2, float y2, float z2,
			float x3, float y3, float z3,
			float x4, float y4, float z4, int tex_index){

	glBindTexture(GL_TEXTURE_2D, texture_id[tex_index]);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( x1, y1, z1 );
    glTexCoord2f(1.0f, 0.0f); glVertex3f( x2, y2, z2 );
    glTexCoord2f(1.0f, 1.0f); glVertex3f( x3, y3, z3 );
    glTexCoord2f(0.0f, 1.0f); glVertex3f( x4, y4, z4 );
  glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}


void draw(float xpos, float ypos, float zpos,
			  float esp, float alt, float larg,
			  float tam, int wire){

	glPushMatrix();
	    glTranslatef (xpos, ypos, zpos);
	    glScalef (esp, alt, larg);
	    if(wire)
	    	glutWireCube (tam);
	    else
	    	glutSolidCube(tam);
    glPopMatrix();
}

void draw_tv(){
        glColor3f(0.5, 0.5, 0.5);
        glPushMatrix();
        //tras/frente - cima/baixo - direita/esquerda
        glTranslatef (34, 8 , 24.7);
        glRotated(90,0,1,0);
        //espessura, altura, lrgura
        glScalef (0.08, 2, 3.3);
        glutSolidCube (5.0);
        glPopMatrix();

        glColor3f(0, 0, 0);
        glPushMatrix();
        //tras/frente - cima/baixo - direita/esquerda
        glTranslatef (34, 8 , 24.5);
        //espessura, altura, lrgura
        glRotated(90,0,1,0);
        glScalef (0.08, 1.8, 3);
        glutSolidCube (5.0);
        glPopMatrix();
}

void display(){

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
  cam[0]=raioxz*cos(2*PI*tetaxz/360);
  cam[2]=raioxz*sin(2*PI*tetaxz/360);

	//printf("%d %d %d\n", center[0], center[1], center[2]);

  gluLookAt(cam[0],cam[1],cam[2],center[0],center[1],center[2],0.0,1.0,0.0);

  draw(0,0,0,22,10,10,5,1);


  glColor3f(0.9f, 0.9f, 0.9f);
  draw_wall(-55,25,-25,
      -55,25,25,
      55,25,25,
      55,25,-25,0);

  //chao
  draw_wall(-55.0f, -25, -25.0f,
      -55.0f, -25,  25.0f,
      55.0f, -25,  25.0f,
      55.0f, -25, -25.0f,1);


  //parede atras da estante
  draw_wall(-55, -25, 10.0f,
    -55, 25.1f,  10.0f,
    -55, 25.1f,  -25.0f,
      -55, -25, -25.0f,0);

  draw_wall(-55, 25.1, 25.0f,
      -55, 20.0f,  25.0f,
      -55, 20.0f,  10.0f,
      -55, 25.1, 10.0f,0);

  // parede embaixo da janela
  draw_wall(-32, -5,  -25.0f,
       35, -5,  -25.0f,
       35, -25, -25.0f,
      -32, -25, -25.0f,0);

  //parede em cima da janela
  draw_wall(-55, 25,  -25.0f,
       55, 25,  -25.0f,
       55, 20.5, -25.0f,
      -55, 20.5, -25.0f,0);

// parede ao lado da porta principal
	draw_wall(50, 25,  -25.0f,
			 55, 25,  -25.0f,
			 55, -25, -25.0f,
			50, -25, -25.0f,0);

  //parede ao lado da porta secundaria
  draw_wall(-55, -25,  -25.0f,
      -48, -25,  -25.0f,
      -48, 20.5, -25.0f,
      -55, 20.5, -25.0f,0);

  //parede acima das duas portas do fundo
  draw_wall(55.5, 20.3,  25.0f,
      -55, 20.3,  25.0f,
      -55, 25, 25.0f,
      55.5, 25, 25.0f,0);

	//parede entre as duas portas
  draw_wall(-35, 20.3,  25.0f,
      12, 20.3,  25.0f,
      12, -25, 25.0f,
      -35, -25, 25.0f,0);

	// parede entre a porta coordenacao e a porta ao lado da estante
	draw_wall(-50, 20.3,  25.0f,
      -55, 20.3,  25.0f,
      -55, -25, 25.0f,
      -50, -25, 25.0f,0);

  draw_wall(55, 20.5,  25.0f,
      28, 20.5,  25.0f,
      28, -24, 25.0f,
      55, -24, 25.0f,0);

  //parede em cima das janelas externas
  draw_wall(55.2f, 25.2, -25.2f,
      55.2f, 20.5f,  -25.2f,
      55.2f, 20.5f,  25.0f,
      55.2f, 25.2, 25.0f,0);

  draw_wall(55.2f, -24, -25.2f,
      55.2f, 20.5f,  -25.2f,
      55.2f, 20.5f,  -20.0f,
      55.2f, -24, -20.0f,0);

      //balcao
      int cont, cont1 = 0;
      float zpos=-15;
      glColor3f(1,1,1);
      draw(25,-10,0,1.5,2.9,9.7,5,0);
      for(cont = 0; cont < 3; cont++, zpos+=15){
        glColor3f(0.5,0.5,0.5);
        draw(21,-10,zpos,0.1,2.5,0.1,5,0);
      }
      zpos= -17;
      for(cont = 1; cont <= 6; cont++){
        glColor3f(0.5,0.5,0.5);
        draw(21,-8,zpos,0.1,0.5,0.1,5,0);
        if(cont%2 == 0){ zpos += 11; }
        else { zpos	+= 4; }
      }

    // estante
    glColor3f(0.5,0.5,0.5);
    float ypos = -8;

    for(cont = 0; cont < 11; cont ++, ypos += 2){
      draw(-43.5,ypos, -1, 0.5, 0.1, 3.5, 5, 0);
    }
    for(cont1 = 0, ypos=-6; cont1 < 18 ;cont1++, ypos++){
      zpos=7.5;
      for(cont = 0; cont < 5; cont++,zpos-=4){
        draw(-43.5, ypos, zpos,0.5, 0.4, 0.006, 5, 0);
      }
    }


    //tv
    draw_tv();
    glColor3f(1,1,1);

    //janelas externas - maiores
      draw(55,-4,-14, 0.01,8,3,5,1);
      draw(55,-4,1,   0.01,8,3,5, 1);
      draw(55,-4,16,  0.01,8,3,5,1);

      //janelas externas - menores
    draw(23,5.7,-25,2.5,3,0.01,5,1);
    draw(10,5.8,-25,2.5,3,0.01,5,1);
    draw(-3,5.8,-25,2.5,3,0.01,5,1);
    draw(-16,5.8,-25,2.5,3,0.01,5,1);

    // porta principal
    glPushMatrix();
      //glColor3f(1,0,0);
      glTranslatef(50,-6,-25);
      glRotated((GLfloat)door_angle,0,-1,0);
      //draw(-7,0,0,3,7.5,0.01,5,0);
			draw_door(-15, -19,  0,
		            0,  -19,   0,
		            0,   20,   0,
		            -15, 20,  0,2);
    glPopMatrix();

	// porta ao lado da estante
	draw_door(-55, -25, 10.0f,
            -55,  15,  10,
    	 	    -55,  15,  25.0f,
      		  -55, -25,  25.0f,3);

	//porta coordenacao
	 draw_door(-35,  -25,25,
						-50,  -25, 25,
						-50,   15, 25,
						-35,   15, 25,2);

	//porta diretor
	 draw_door(12,  -25,25,
						28,  -25, 25,
						28,   15, 25,
						12,   15, 25,2);

		// porta secundaria
		draw_door(-32,  -25, -25,
							-48,  -25, -25,
							-48,   15, -25,
							-32,   15, -25,2);

  //  draw(-30,-2,-25,3.2,6,0.01,5,0);

    //biros
    glColor3f(1,1,1);
    draw(-2,-4, 15,1.9,0.01,3,5,0);
    draw(4.5,-6.5,-15,0.05, 1, 3,5,0);
    glColor3f(0,0,0);
    draw(2.7, -12, 17,0.09, 2, 0.08,5,0);
    draw(2.7, -12, 10,0.09, 2, 0.08,5,0);

    glColor3f(1,1,1);
    draw(-20,-4,15,1.9,0.01,3,5,0);
    draw(-11.5, -6.5, -15,0.05, 1, 3,5,0);
    glColor3f(0,0,0);
    draw(-16, -12, 10,0.09, 2, 0.08,5,0);
    draw(-16, -12, 17,0.09, 2, 0.08,5,0);

    glColor3f(1,1,1);
    draw(-16,-4,-15,1.9,0.01,3,5,0);
    draw(-15.5, -6.5, 15,0.05, 1, 3,5,0);
    glColor3f(0,0,0);
    draw(4, -12, -13,0.09, 2, 0.08,5,0);
    draw(4, -12, -19,0.09, 2, 0.08,5,0);

    glColor3f(1,1,1);
    draw(0,-4,-15,1.9,0.01,3,5,0);
    draw(2.9, -6.5, 15,0.05, 1, 3,5,0);
    glColor3f(0,0,0);
    draw(-11.9, -12, -19,0.09, 2, 0.08,5,0);
    draw(-11.9, -12, -13,0.09, 2, 0.08,5,0);

    // RELOGIO
    GLUquadricObj *quadric = gluNewQuadric();
    glPushMatrix();
      glTranslatef(-4,10,24.2);
      gluCylinder(quadric, 2, 2, 0.7, 12, 3);
    glPopMatrix();

      draw(-4,10.8,24.2,0.07,0.4,0.01,5,0);
      glPushMatrix();
        glTranslatef(-3.65,9.2,24.2);
        glRotated(45,0,0,1);
        draw(0,0,0,0.07,0.3,0.1,5,0);
      glPopMatrix();

    //PC
    draw(-1,1,15,0.09,1,1.2,5,0);
    glColor3f(0,0,0);
    draw(-1.2,1,15,0.09,0.95,1.1,5,0);
    draw(-2,-1,20,1.5,1,0.5,5,0);
    draw(-5,-3.5,13,0.5,0.05,1.2,5,0);
    draw(-1,-3.5,15,0.7,0.09,0.7,5,0);
    draw(-0.5,-1,15,0.1,1,0.2,5,0);
    glPushMatrix();
      quadric = gluNewQuadric();
      glTranslatef(-5,-3.5,17);
      gluSphere(quadric, 0.5, 75,30);
      glRotated(90,0,1,0);
    glPopMatrix();

    glColor3f(0.5,0.5,0.5);
    draw(-19,1,15,0.09,1,1.2,5,0);
    glColor3f(0,0,0);
    draw(-19.5,1,15,0.09,0.95,1.1,5,0);
    draw(-20,-1,20,1.5,1,0.5,5,0);
    draw(-23,-3.5,14,0.5,0.05,1.2,5,0);
    draw(-19,-3.5,15,0.7,0.09,0.7,5,0);
    draw(-18.5,-1,15,0.1,1,0.2,5,0);
    glPushMatrix();
      quadric = gluNewQuadric();
      glTranslatef(-22,-3.5,18);
      gluSphere(quadric, 0.5, 75,30);
      glRotated(90,0,1,0);
    glPopMatrix();

    glColor3f(0.5,0.5,0.5);
    draw(-15,1,-15,0.09,1,1.2,5,0);
    glColor3f(0,0,0);
    draw(-15.5 ,1,-15,0.09,0.95,1.1,5,0);
    draw(-15,-1.5,-20,1.5,1,0.5,5,0);
    draw(-18,-3.7,-14,0.5,0.05,1.2,5,0);
    draw(-15,-3.5,-15,0.7,0.09,0.7,5,0);
     draw(-14.5,-1,-15,0.1,1,0.2,5,0);
    glPushMatrix();
      quadric = gluNewQuadric();
      glTranslatef(-18,-3.5,-9);
      gluSphere(quadric, 0.5, 75,30);
      glRotated(90,0,1,0);
    glPopMatrix();

    glColor3f(0.5,0.5,0.5);
    draw(0.5,1,-15,0.09,1,1.2,5,0);
    glColor3f(0,0,0);
    draw(0 ,1,-15,0.09,0.95,1.1,5,0);
    draw(0,-1.5,-20,1.5,1,0.5,5,0);
    draw(-3,-3.7,-14,0.5,0.05,1.2,5,0);
    draw(1,-3.5,-15,0.7,0.09,0.7,5,0);
    draw(1,-1,-15,0.1,1,0.2,5,0);
    glPushMatrix();
      quadric = gluNewQuadric();
      glTranslatef(-3,-3.5,-10);
      gluSphere(quadric, 0.5, 75,30);
      glRotated(90,0,1,0);
    glPopMatrix();

    glColor3f(1,1,1);

  glutSwapBuffers();
}

void special(int key, int x, int y){
  float fraction = 1;
  switch (key) {
  case GLUT_KEY_UP:
		cam[1] = cam[1] + fraction;
    glutPostRedisplay();
    break;
  case GLUT_KEY_DOWN:
		cam[1] = cam[1] - fraction;
    glutPostRedisplay();
    break;
  case GLUT_KEY_LEFT:
		tetaxz=tetaxz+2;
    glutPostRedisplay();
    break;
  case GLUT_KEY_RIGHT:
		tetaxz=tetaxz-2;
    glutPostRedisplay();
    break;
  }
}


void keyboard(unsigned char key, int x, int y){

  switch (key) {
    case 27:
      exit(0);
      break;
    case 'r':
      raioxz=raioxz+1;
      glutPostRedisplay();
      break;
    case 'R':
      raioxz=raioxz-1;
      if(raioxz==0){
        raioxz=1;
      }
      glutPostRedisplay();
      break;
    case 'E':
        if(door_angle > -90)
          door_angle = (door_angle - 5) % 360;
        glutPostRedisplay();
        break;
    case 'e':
      if(door_angle  >= -90 && door_angle < 0 ){
         door_angle = (door_angle + 5) % 360;
      }
        glutPostRedisplay();
        break;
    case 'W':
      cam[1]=cam[1]+1;
      glutPostRedisplay();
      break;
    case 'D':
      cam[1] =cam[1]-1;
      glutPostRedisplay();
      break;
  }
}

void init_textures(){

		loadTextureFromFile("textures/wall.jpg",0);
		loadTextureFromFile("textures/FloorTiles2.jpg",1);
		loadTextureFromFile("textures/texture_door.jpg",2);
		loadTextureFromFile("textures/texture_door1.jpg",3);

}

void loadTextureFromFile(char *filename,int index)
{

	 int width, height;
   unsigned char* image =
       SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

			 printf("%d %d\n", width, height);

   glGenTextures(1, &texture_id[index]);
   glBindTexture(GL_TEXTURE_2D, texture_id[index]);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	 glBindTexture(GL_TEXTURE_2D, 0);
}
