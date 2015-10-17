#include "secretaria.h"

GLfloat cam[3]={0.0,7.0,5.0};
GLfloat center[3]={0.0,3.0,0.0};
GLfloat tetaxz=5;
GLfloat tetayz=5;
GLfloat raioxz=50;
GLuint texture_id[NUM_TEX];
int door_angle = 0;
GLfloat posicao_luz0[]    = { 10, 25 , 0.0, 1.0};
GLfloat cor_luz0[]        = { 1.0, 1.0, 1.0, 1.0};
GLfloat luz_ambiente[]    = { 0.2, 0.2, 0.2, 0.2};

GLfloat posicao_luz1[]    = { -23, 25	, 0.0, 1.0};
GLfloat cor_luz1[]        = { 1.0, 1.0, 1.0, 1.0};
GLfloat direcao_luz1[]    = { 0.0, 0, -1.0 , 1.0};
GLint   spot_luz1         = 180;
GLfloat spot_brilho[]    = {2};

GLfloat sem_cor[]         = { 0.0, 0.0, 0.0, 1.0};

// Capacidade de brilho do material
GLfloat especularidade[4] = {1.0,1.0,1.0,1.0};
GLint especMaterial = 30;


void draw_wall(float x1,float y1, float z1,
			float x2, float y2, float z2,
			float x3, float y3, float z3,
			float x4, float y4, float z4, int tex_index){

	glBindTexture(GL_TEXTURE_2D, texture_id[tex_index]);
  glBegin(GL_QUADS);
		glNormal3f(0,1,0);
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
		glNormal3f(0,1,0);
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
			glNormal3f(0,1,0);
	    glTranslatef (xpos, ypos, zpos);
	    glScalef (esp, alt, larg);
	    if(wire)
	    	glutWireCube (tam);
	    else
	    	glutSolidCube(tam);
    glPopMatrix();
}

void draw_windows(float x1,float y1, float z1,
			float x2, float y2, float z2,
			float x3, float y3, float z3,
			float x4, float y4, float z4){

   glBegin(GL_QUADS);
			glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
		  glVertex3f( x1, y1, z1 );
	    glVertex3f( x2, y2, z2 );
	    glVertex3f( x3, y3, z3 );
	    glVertex3f( x4, y4, z4 );
		glEnd();


}

void draw_tv(){

	        glPushMatrix();
						glNormal3f(0,1,0);
		        //tras/frente - cima/baixo - direita/esquerda
		        glTranslatef (34, 8 , 24.7);
		        glRotated(90,0,1,0);
		        //espessura, altura, lrgura
		        glScalef (0.08, 2, 3.3);
		        glutSolidCube (5.0);
	        glPopMatrix();

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
  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  cam[0]=raioxz*cos(2*PI*tetaxz/360);
  cam[2]=raioxz*sin(2*PI*tetaxz/360);

  gluLookAt(cam[0],cam[1],cam[2],center[0],center[1],center[2],0.0,1.0,0.0);

	init_lighting();

	//lampada
	glPushMatrix();
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
		glMaterialfv(GL_FRONT, GL_EMISSION, cor_luz1);
		glVertex3f( -23, 24.5, -9 );
		glVertex3f( -24, 24.5, -9 );
		glVertex3f( -24, 24.5, 10 );
		glVertex3f( -23, 24.5, 10 );
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
		glVertex3f( 10, 24.5, -9 );
		glVertex3f( 11, 24.5, -9 );
		glVertex3f( 11, 24.5, 10 );
		glVertex3f( 10, 24.5, 10 );
		glMaterialfv(GL_FRONT, GL_EMISSION, sem_cor);
	glEnd();
	glPopMatrix();
  glColor3f(0.9f, 0.9f, 0.9f);

	//TETO
  draw_wall(-70,25,-25,
      -70,25,25,
      70,25,25,
      70,25,-25,0);

	// divisoria do teto
	draw_wall(-17,25,-25,
		      -17,25,   25,
		      -17,21,   25,
		      -17,21,-25,0);

	draw_wall(-19,21,-25,
		       -19, 21,  25,
		       -19, 25,  25,
		       -19, 25, -25,0);

	 draw_wall(-17, 21,-25,
			       -17, 21,  25,
			       -19,21,  25,
			       -19,21, -25,0);

  //chao
  draw_wall(-70.0f, -25, -25.0f,
      -70.0f, -25,  25.0f,
      70.0f, -25,  25.0f,
      70.0f, -25, -25.0f,1);


  //parede atras da estante
  draw_wall(-70, -25, 10.0f,
    -70, 25.1f,  10.0f,
    -70, 25.1f,  -25.0f,
      -70, -25, -25.0f,0);

  draw_wall(-70, 25.1, 25.0f,
      -70, 20.0f,  25.0f,
      -70, 20.0f,  10.0f,
      -70, 25.1, 10.0f,0);

  // parede embaixo da janela
  draw_wall(-30, -5,  -25.0f,
       50, -5,  -25.0f,
       50, -25, -25.0f,
      -30, -25, -25.0f,0);

  //parede em cima da janela
  draw_wall(-70, 25,  -25.0f,
       70, 25,  -25.0f,
       70, 20.5, -25.0f,
      -70, 20.5, -25.0f,0);

// parede ao lado da porta principal
	draw_wall(65, 25,  -25.0f,
			 70, 25,  -25.0f,
			 70, -25, -25.0f,
			65, -25, -25.0f,0);

  //parede ao lado da porta secundaria
  draw_wall(-70, -25,  -25.0f,
      -63, -25,  -25.0f,
      -63, 20.5, -25.0f,
      -70, 20.5, -25.0f,0);

  //parede acima das duas portas do fundo
  draw_wall(70.5, 20.3,  25.0f,
      -70, 20.3,  25.0f,
      -70, 25, 25.0f,
      70.5, 25, 25.0f,0);

	//parede entre as duas portas 5 e 6
  draw_wall(-50, 20.3,  25.0f,
      -17, 20.3,  25.0f,
      -17, -25, 25.0f,
      -50, -25, 25.0f,0);

	draw_wall(23, 20.3,  25.0f,
      -2, 20.3,  25.0f,
      -2, -25, 25.0f,
      23, -25, 25.0f,0);

	// parede entre a porta e a porta ao lado da estante
	draw_wall(-65, 20.3,  25.0f,
      -70, 20.3,  25.0f,
      -70, -25, 25.0f,
      -65, -25, 25.0f,0);

  draw_wall(70, 20.5,  25.0f,
      40, 20.5,  25.0f,
      40, -25, 25.0f,
      70, -25, 25.0f,0);

  //parede em cima das janelas externas
  draw_wall(70.2f, 25.2, -25.2f,
      70.2f, 20.5f,  -25.2f,
      70.2f, 20.5f,  25.0f,
      70.2f, 25.2, 25.0f,0);

  draw_wall(70.2f, -25, -25.2f,
      70.2f, 20.5f,  -25.2f,
      70.2f, 20.5f,  -20.0f,
      70.2f, -25, -20.0f,0);

      //balcao
      int cont, cont1 = 0;
      float zpos=-15;
      glColor3f(1,1,1);
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, texture_id[4]);
				glNormal3f(0,1,0);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f( 42,  -5, 25 );
					glTexCoord2f(0.0f, 1.0f); glVertex3f( 42, -24.5, 25 );
				  glTexCoord2f(1.0f, 1.0f);	glVertex3f( 42, -24.5, -25 );
				  glTexCoord2f(1.0f, 0.0f);	glVertex3f( 42, -5, -25 );
				glEnd();

				glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f);glVertex3f( 49,  -5, 25 );
					glTexCoord2f(0.0f, 1.0f);glVertex3f( 49, -24.5, 25 );
					glTexCoord2f(1.0f, 1.0f);glVertex3f( 49, -24.5, -25 );
					glTexCoord2f(1.0f, 0.0f);glVertex3f( 49, -5, -25 );
				glEnd();

				glBegin(GL_QUADS);
				  glTexCoord2f(0.0f, 0.0f);	glVertex3f( 42, -5, 25 );
				  glTexCoord2f(0.0f, 1.0f);	glVertex3f( 50, -5,  25 );
			    glTexCoord2f(1.0f, 1.0f);		glVertex3f( 50, -5, -25 );
				  glTexCoord2f(1.0f, 0.0f);	glVertex3f( 42, -5, -25 );
				glEnd();

				glBindTexture(GL_TEXTURE_2D, 0);
			glPopMatrix();

			glBindTexture(GL_TEXTURE_2D, texture_id[5]);

			glNormal3f(0,1,0);
			glBegin(GL_QUADS);
				glVertex3f( 41.8, -5, 24.7 );
				glVertex3f( 41.8, -6,  24.7 );
				glVertex3f( 41.8, -6, -24.7 );
				glVertex3f( 41.8, -5, -24.7 );
			glEnd();

			glBegin(GL_QUADS);
				glVertex3f( 49.5, -14.8, 24.7 );
				glVertex3f( 49.5, -15,  24.7 );
				glVertex3f( 49.5, -15, -24.7 );
				glVertex3f( 49.5, -14.8, -24.7 );
			glEnd();

			glBegin(GL_QUADS);
				glVertex3f( 49.5, -5, -1 );
				glVertex3f( 49.5, -24, -1 );
				glVertex3f( 49.5, -24, -0.8);
				glVertex3f( 49.5, -5,  -0.8 );
			glEnd();

      for(cont = 0; cont < 3; cont++, zpos+=15){
        draw(41,-14,zpos,0.01,3.5,0.1,5,0);
      }
      zpos= -17;
      for(cont = 1; cont <= 6; cont++){
        draw(41,-10,zpos,0.01,0.5,0.1,5,0);
        if(cont%2 == 0){ zpos += 11; }
        else { zpos	+= 4; }
      }

		 glBindTexture(GL_TEXTURE_2D, texture_id[0]);

    // estante
		glBindTexture(GL_TEXTURE_2D, texture_id[6]);
    float ypos = -8;

    for(cont = 0; cont < 11; cont ++, ypos += 2){
      draw(-68,ypos, -3, 0.1, 0.1, 4, 5, 0);
    }
    for(cont1 = 0, ypos=-6; cont1 < 18 ;cont1++, ypos++){
      zpos=7.5;
      for(cont = 0; cont < 6; cont++,zpos-=4){
        draw(-68, ypos, zpos,0.6, 0.4, 0.05, 5, 0);
      }
    }
		glBindTexture(GL_TEXTURE_2D, texture_id[0]);

    // porta principal
    glPushMatrix();
      //glColor3f(1,0,0);
      glTranslatef(65,-6,-25);
      glRotated((GLfloat)door_angle,0,-1,0);
			draw_door(0, -19,  0,
		            -15,  -19,   0,
		            -15,   20,   0,
		            0, 20,  0,2);
    glPopMatrix();

	// porta 3
	draw_door(-70, -25, 10.0f,
            -70,  15,  10,
    	 	    -70,  15,  25.0f,
      		  -70, -25,  25.0f,3);

	//porta 4
	 draw_door(-50,  -25,25,
						-65,  -25, 25,
						-65,   15, 25,
						-50,   15, 25,2);

	//porta 5
	 draw_door(23,  -25,25,
						40,  -25, 25,
						40,   15, 25,
						23,   15, 25,2);

	//porta 6
	 draw_door(-17,  -25,25,
						-2,  -25, 25,
						-2,   15, 25,
						-17,   15, 25,2);

		// porta 2
		draw_door(-47,  -25, -25,
							-63,  -25, -25,
							-63,   15, -25,
							-47,   15, -25,2);

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
      glTranslatef(10,10,24.2);
      gluCylinder(quadric, 2, 2, 0.7, 12, 3);
    glPopMatrix();

      draw(10,10.8,24.2,0.07,0.4,0.01,5,0);
      glPushMatrix();
        glTranslatef(10.5,9.2,24.2);
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


		//tv
		draw_tv();


		//janelas maiores
		draw_windows(70,20,25,
								 70,10,25,
								 70,10,10,
								 70,20,10);

	 draw_windows(70,20,9.5,
								70,10,9.5,
								70,10,-4.5,
								70,20,-4.5);

	 draw_windows(70,20,-5,
								 70,10,-5,
								 70,10,-20,
								 70,20,-20);

		 draw_windows(70,9.5,  25,
									70,-24.5,25,
									70,-24.5,10,
									70,9.5,  10);

		draw_windows(70,9.5,  9.5,
								 70,-24.5,9.5,
								 70,-24.5, -4.5,
								 70,9.5, -4.5);

		draw_windows(70,9.5,-5,
									70,-24.5,-5,
									70,-24.5,-20,
									70,9.5,-20);

		//janelas menores
		draw_windows( 49.5,-5,-25,
									49.5, 14 ,-25,
									29,14,-25,
									29,-5  ,-25);

			draw_windows( 28.5,-5,-25,
										28.5, 14 ,-25,
										10,14,-25,
										10,-5  ,-25);

			draw_windows( 9.5,-5,-25,
										9.5, 14 ,-25,
										-9,14,-25,
										-9,-5  ,-25);

			draw_windows( -10,-5,-25,
										-10, 14 ,-25,
										-30,14,-25,
										-30,-5  ,-25);

			//janelas menores, acima das portas
			draw_windows( 64,20,-25,
										64, 14.5 ,-25,
										50,14.5,-25,
										50,20  ,-25);

			draw_windows( 49.5,20,-25,
										49.5, 14.5 ,-25,
										29,14.5,-25,
										29,20  ,-25);

			draw_windows( 28.5,20,-25,
										28.5, 14.5 ,-25,
										10,14.5,-25,
										10, 20  ,-25);

			draw_windows( 9.5,20,-25,
										9.5, 14.5 ,-25,
										-9,14.5,-25,
										-9,20  ,-25);

			draw_windows( -10,20,-25,
										-10, 14.5 ,-25,
										-30,14.5,-25,
										-30,20  ,-25);

			draw_windows( -46.5,20,-25,
										-46.5, 15 ,-25,
										-63,15,-25,
										-63,20  ,-25);

			draw_windows( -50,20,  25,
										-50, 15 ,25,
										-65,15,    25,
										-65,20  ,25);

			draw_windows( -17,20,  25,
										-17, 15 ,25,
										 -2,15,    25,
										 -2,20  ,25);

			draw_windows( 23,20,  25,
										23, 15 ,25,
										40,15,    25,
										40,20  ,25);

			draw_windows( -70,20,  25,
										-70, 15 ,25,
										-70,15,    10,
										-70,20  ,10);

			draw_windows( -31,20,  -25,
										-31, 15 ,-25,
										-39,15,  -25,
										-39,20  ,-25);

			draw_windows( -40,20,  -25,
										-40, 15 ,-25,
										-46,15,  -25,
										-46,20  ,-25);

			draw_windows( -31,14,  -25,
										-31, -25 ,-25,
										-39,-25,  -25,
										-39,14  ,-25);

			draw_windows( -40,14,  -25,
										-40, -25 ,-25,
										-46,-25,  -25,
										-46,14  ,-25);

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
		loadTextureFromFile("textures/balcao.jpg",4);
		loadTextureFromFile("textures/balcao2.jpg",5);
		loadTextureFromFile("textures/estante.jpg",6);

}

void init_lighting(){

		//Habilita o uso de iluminação
		glEnable(GL_LIGHTING);
		glEnable(GL_BLEND);
	 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Habilita o modelo de colorização de Gouraud
		glShadeModel(GL_SMOOTH);
		// Define a refletância do material
		glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
		// Define a concentração do brilho
		glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

		glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
	  glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz1);
		glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz1);
		glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz0 );
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direcao_luz1);
		glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, spot_brilho);
		glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, spot_luz1);

		glLightfv(GL_LIGHT1, GL_DIFFUSE, cor_luz1 );
		glLightfv(GL_LIGHT1, GL_SPECULAR, cor_luz1);
		glLightfv(GL_LIGHT1, GL_POSITION, posicao_luz1 );
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direcao_luz1);
		glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, spot_brilho);
		glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, spot_luz1);

		// Habilita a definição da cor do material a partir da cor corrente
		glEnable(GL_COLOR_MATERIAL);
		// Habilita a luz de número 0
		glEnable(GL_LIGHT0);
		// Habilita a luz de número 1
		glEnable(GL_LIGHT1);

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
