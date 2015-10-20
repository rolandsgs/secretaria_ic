#include "secretaria.h"

GLfloat cam[3]={0.0,7.0,5.0};
GLfloat center[3]={0.0,3.0,0.0};
GLfloat tetaxz=5;
GLfloat tetayz=5;
GLfloat raioxz=50;

GLuint texture_id[NUM_TEX];

int door_angle = 0;
int cont, cont1 = 0;
float zpos=-15;
GLUquadricObj *quadric;

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


void draw_quads(float x1,float y1, float z1,
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

void draw_cube(float xpos, float ypos, float zpos,
    float esp, float alt, float larg,
    float rotX, float rotY, float rotZ, float rotAngle,
    float tam, int wire, int tex_index){

	glPushMatrix();
        if(tex_index != NOTTEX)
        {
            glEnable(GL_TEXTURE_GEN_S);
            glEnable(GL_TEXTURE_GEN_T);
            glBindTexture(GL_TEXTURE_2D, texture_id[tex_index]);
        }
        glNormal3f(0,1,0);
	    glTranslatef (xpos, ypos, zpos);
	     glRotated(rotAngle,rotX,rotY,rotZ);
	    glScalef (esp, alt, larg);
	    if(wire) glutWireCube (tam);
	    else glutSolidCube(tam);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);

}

void draw_windows()
{

    glColor4f(1.0, 1.0, 1.0, 0.3);
    //janelas maiores
    draw_quads(70,  20,  25,  70,   10,  25,  70,  10,    10,  70, 20,  10,  NOTTEX);
    draw_quads(70,  20, 9.5,  70,   10, 9.5,  70,  10,   -4.5, 70, 20,  -4.5, NOTTEX);
    draw_quads(70,  20,  -5,  70,   10,  -5,  70,  10,    -20, 70, 20,  -20, NOTTEX);
    draw_quads(70, 9.5,  25,  70, -24.5, 25,  70, -24.5,   10, 70, 9.5,  10, NOTTEX);
    draw_quads(70, 9.5, 9.5,  70, -24.5, 9.5, 70, -24.5, -4.5, 70, 9.5, -4.5, NOTTEX);
    draw_quads(70, 9.5,  -5,  70, -24.5, -5,  70, -24.5,  -20, 70, 9.5,  -20, NOTTEX);

    //janelas menores
    draw_quads( 49.5,-5,-25, 49.5, 14 ,-25, 29,14,-25, 29,-5  ,-25, NOTTEX);
    draw_quads( 28.5,-5,-25, 28.5, 14 ,-25, 10,14,-25, 10,-5  ,-25, NOTTEX);
    draw_quads( 9.5,-5,-25, 9.5, 14 ,-25, -9,14,-25, -9,-5  ,-25,NOTTEX);
    draw_quads( -10,-5,-25, -10, 14 ,-25, -30,14,-25, -30,-5  ,-25, NOTTEX);

    //janelas menores, acima das portas
    draw_quads( 64,20,-25, 64, 14.5 ,-25, 50,14.5,-25, 50,20  ,-25, NOTTEX);
    draw_quads( 49.5,20,-25, 49.5, 14.5 ,-25, 29,14.5,-25, 29,20  ,-25, NOTTEX);
    draw_quads( 28.5,20,-25, 28.5, 14.5 ,-25, 10,14.5,-25, 10, 20  ,-25, NOTTEX);
    draw_quads( 9.5,20,-25, 9.5, 14.5 ,-25, -9,14.5,-25, -9,20  ,-25,  NOTTEX);
    draw_quads( -10,20,-25, -10, 14.5 ,-25, -30,14.5,-25, -30,20  ,-25,  NOTTEX);
    draw_quads( -46.5,20,-25, -46.5, 15 ,-25, -63,15,-25, -63,20  ,-25,  NOTTEX);
    draw_quads( -50,20,  25, -50, 15 ,25,-65,15, 25,-65,20 ,25,  NOTTEX);
    draw_quads( -17,20,  25, -17, 15 ,25, -2,15, 25,-2,20  ,25,  NOTTEX);
    draw_quads( 23,20,  25, 23, 15 ,25, 40,15, 25, 40, 20 ,25, NOTTEX);
    draw_quads( -70,20,  25, -70, 15 ,25, -70,15, 10, -70, 20 ,10,  NOTTEX);
    draw_quads( -31,20,  -25, -31, 15 ,-25, -39,15,  -25, -39,20  ,-25, NOTTEX);
    draw_quads( -40,20,  -25, -40, 15 ,-25, -46,15,  -25, -46,20  ,-25,  NOTTEX);
    draw_quads( -31,14,  -25, -31, -25 ,-25, -39,-25,  -25, -39,14  ,-25,  NOTTEX);
    draw_quads( -40,14,  -25, -40, -25 ,-25, -46,-25,  -25, -46,14  ,-25, NOTTEX);


}

void draw_objects()
{


    //lampada
	glColor3f(1,1,1);
	glMaterialfv(GL_FRONT, GL_EMISSION, cor_luz1);
    draw_quads(-23, 24.5, -9, -24, 24.5, -9, -24, 24.5, 10, -23, 24.5, 10, NOTTEX);
    draw_quads(30, 24.5, -9, 31, 24.5, -9, 31, 24.5, 10, 30, 24.5, 10, NOTTEX);
    glMaterialfv(GL_FRONT, GL_EMISSION, sem_cor);

    // TV
    draw_cube(58, 8, 24.7, 0.08, 2, 3.3, 0, 1, 0, 90, 5, 0, NOTTEX);
    draw_cube(58, 8, 24.5, 0.08, 1.8, 3, 0, 1, 0, 90, 5, 0, NOTTEX);


    // marmore embaixo das janelas
    draw_cube(6, -5.3, -23.55, 7.2, 0.05, 0.29, 0, 0, 0, 0 , 10, 0, 7);

    //biros
    //biro 1
    glColor3f(1,1,1);
    draw_cube(16, -10, 14.3, 1.5, 0.2, 4, 0, 0, 0, 0, 5, 0, NOTTEX);
    draw_cube(7, -10, 20.5, 1.5, 0.2, 2.3, 0, 1, 0, 90, 5, 0, NOTTEX);
    draw_cube(18, -15.1, 15, 0.2, 1, 3.7, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(10, -15.1, 23, 0.2, 1, 3, 0, 1, 0, 90, 5,0, NOTTEX);
    //pés biro 1
    glColor3f(0,0,0);
    draw_cube(18, -17.3, 5.5, 0.4, 2.9, 0.2, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(16.5, -24.3, 5.5, 1.3, 0.2, 0.2, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(18, -17.3, 23.8, 0.4, 2.9, 0.2, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(2.5, -17.3, 22.5, 0.2, 2.9, 0.4, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(2.5, -24.3, 20.8, 1.4, 0.2, 0.2, 0, 1, 0, 90, 5,0, NOTTEX);
    draw_cube(18, -11.1, 15, 0.2, 0.6, 3.7, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(10, -11.1, 23, 0.2, 0.6, 3, 0, 1, 0, 90, 5,0, NOTTEX);

    // biro 2
    glColor3f(1,1,1);
    draw_cube(-24, -10, 14.3, 1.5, 0.2, 4, 0, 0, 0, 0, 5, 0, NOTTEX);
    draw_cube(-33, -10, 20.5, 1.5, 0.2, 2.3, 0, 1, 0, 90, 5, 0, NOTTEX);
    draw_cube(-22, -15.1, 15, 0.2, 1, 3.7, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(-30, -15.1, 23, 0.2, 1, 3, 0, 1, 0, 90, 5,0, NOTTEX);
    glColor3f(0,0,0);
    //pés biro 2
    draw_cube(-22 , -17.3, 5.5, 0.4, 2.9, 0.2, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(-23.5, -24.3, 5.5, 1.3, 0.2, 0.2, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(-22, -17.3, 23.8, 0.4, 2.9, 0.2, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(-37.5, -17.3, 22.5, 0.2, 2.9, 0.4, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(-37.5, -24.3, 20.8, 1.4, 0.2, 0.2, 0, 1, 0, 90, 5,0, NOTTEX);
    draw_cube(-22, -11.1, 15, 0.2, 0.6, 3.7, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(-30, -11.1, 23, 0.2, 0.6, 3, 0, 1, 0, 90, 5,0, NOTTEX);

    //biro 3
    glColor3f(1,1,1);
    draw_cube(16, -10, -14.3, 1.5, 0.2, 4, 0, 0, 0, 0, 5, 0, NOTTEX);
    draw_cube(7, -10, -20.5, 1.5, 0.2, 2.3, 0, 1, 0, 90, 5, 0, NOTTEX);
    draw_cube(18, -15.1, -15, 0.2, 1, 3.7, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(10, -15.1, -23, 0.2, 1, 3, 0, 1, 0, 90, 5,0, NOTTEX);
    //pés biro 3
    glColor3f(0,0,0);
    draw_cube(18, -17.3, -5.5, 0.4, 2.9, 0.2, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(16.5, -24.3, -5.5, 1.3, 0.2, 0.2, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(18, -17.3, -23.8, 0.4, 2.9, 0.2, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(2.5, -17.3, -22.5, 0.2, 2.9, 0.4, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(2.5, -24.3, -20.8, 1.4, 0.2, 0.2, 0, 1, 0, 90, 5,0, NOTTEX);
    draw_cube(18, -11.1, -15, 0.2, 0.6, 3.7, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(10, -11.1, -23, 0.2, 0.6, 3, 0, 1, 0, 90, 5,0, NOTTEX);

    // biro 4
    glColor3f(1,1,1);
    draw_cube(-24, -10, -14.3, 1.5, 0.2, 4, 0, 0, 0, 0, 5, 0, NOTTEX);
    draw_cube(-33, -10, -20.5, 1.5, 0.2, 2.3, 0, 1, 0, 90, 5, 0, NOTTEX);
    draw_cube(-22, -15.1, -15, 0.2, 1, 3.7, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(-30, -15.1, -23, 0.2, 1, 3, 0, 1, 0, 90, 5,0, NOTTEX);
    glColor3f(0,0,0);
    //pés biro 4
    draw_cube(-22 , -17.3, -5.5, 0.4, 2.9, 0.2, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(-23.5, -24.3, -5.5, 1.3, 0.2, 0.2, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(-22, -17.3, -23.8, 0.4, 2.9, 0.2, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(-37.5, -17.3, -22.5, 0.2, 2.9, 0.4, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(-37.5, -24.3, -20.8, 1.4, 0.2, 0.2, 0, 1, 0, 90, 5,0, NOTTEX);
    draw_cube(-22, -11.1, -15, 0.2, 0.6, 3.7, 0, 0, 0, 0, 5,0, NOTTEX);
    draw_cube(-30, -11.1, -23, 0.2, 0.6, 3, 0, 1, 0, 90, 5,0, NOTTEX);


    //PC
    // pc 1
    glColor3f(0.5,0.5,0.5);
    draw_cube(17.5, -5, 13, 0.09, 1, 1.2 , 0, 0, 0, 0, 4, 0, NOTTEX);      //TELA
    glColor3f(0,0,0);
    draw_cube(18, -5.2, 13, 0.09, 0.95, 1.1, 0, 0, 0, 0, 5, 0, NOTTEX);    //TELA
    draw_cube(15, -7, 19, 1.5, 1, 0.5, 0, 0, 0, 0, 5, 0, NOTTEX);          //CPU
    draw_cube(13.8, -9.5, 13, 0.5, 0.05, 1.2, 0, 0, 0, 0, 5, 0, NOTTEX);   //TECLADO
    draw_cube(17.5, -9.5, 13, 0.7, 0.09, 0.7, 0, 0, 0, 0, 5, 0, NOTTEX);   //BASE
    draw_cube(18, -7, 13, 0.1, 1, 0.2, 0, 0, 0, 0, 5, 0, NOTTEX);          // BASE
    glPushMatrix(); //MOUSE
        quadric = gluNewQuadric();
        glTranslatef(14, -9.5, 17);
        gluSphere(quadric, 0.5, 75,30);
        glRotated(90,0,1,0);
    glPopMatrix();

    // pc 2
    glColor3f(0.5,0.5,0.5);
    draw_cube(-22.5, -5, 13, 0.09, 1, 1.2 , 0, 0, 0, 0, 4, 0, NOTTEX);     //TELA
    glColor3f(0,0,0);
    draw_cube(-22, -5.2, 13, 0.09, 0.95, 1.1, 0, 0, 0, 0, 5, 0, NOTTEX);   //TELA
    draw_cube(-25, -7, 19, 1.5, 1, 0.5, 0, 0, 0, 0, 5, 0, NOTTEX);         //CPU
    draw_cube(-25.8, -9.5, 13, 0.5, 0.05, 1.2, 0, 0, 0, 0, 5, 0, NOTTEX);  //TECLADO
    draw_cube(-22.5, -9.5, 13, 0.7, 0.09, 0.7, 0, 0, 0, 0, 5, 0, NOTTEX);  //BASE
    draw_cube(-22, -7, 13, 0.1, 1, 0.2, 0, 0, 0, 0, 5, 0, NOTTEX);         //BASE
    glPushMatrix(); //MOUSE
        quadric = gluNewQuadric();
        glTranslatef(-26, -9.5, 17);
        gluSphere(quadric, 0.5, 75,30);
        glRotated(90,0,1,0);
    glPopMatrix();

    // pc 3
    glColor3f(0.5,0.5,0.5);
    draw_cube(17.5, -5, -13, 0.09, 1, 1.2 , 0, 0, 0, 0, 4, 0, NOTTEX);          //TELA
    glColor3f(0,0,0);
    draw_cube(18, -5.2, -13, 0.09, 0.95, 1.1, 0, 0, 0, 0, 5, 0, NOTTEX);      //TELA
    draw_cube(15, -7, -19, 1.5, 1, 0.5, 0, 0, 0, 0, 5, 0, NOTTEX);           //CPU
    draw_cube(13.8, -9.5, -13, 0.5, 0.05, 1.2, 0, 0, 0, 0, 5, 0, NOTTEX);      // TECLADO
    draw_cube(17.5, -9.5, -13, 0.7, 0.09, 0.7, 0, 0, 0, 0, 5, 0, NOTTEX);       //BASE
    draw_cube(18, -7, -13, 0.1, 1, 0.2, 0, 0, 0, 0, 5, 0, NOTTEX);          // BASE
    glPushMatrix(); //MOUSE
        quadric = gluNewQuadric();
        glTranslatef(14, -9.5, -9);
        gluSphere(quadric, 0.5, 75,30);
        glRotated(90,0,1,0);
    glPopMatrix();

    // pc 4
    glColor3f(0.5,0.5,0.5);
    draw_cube(-22.5, -5, -13, 0.09, 1, 1.2 , 0, 0, 0, 0, 4, 0, NOTTEX);          //TELA
    glColor3f(0,0,0);
    draw_cube(-22, -5.2, -13, 0.09, 0.95, 1.1, 0, 0, 0, 0, 5, 0, NOTTEX);      //TELA
    draw_cube(-25, -7, -19, 1.5, 1, 0.5, 0, 0, 0, 0, 5, 0, NOTTEX);           //CPU
    draw_cube(-25.8, -9.5, -13, 0.5, 0.05, 1.2, 0, 0, 0, 0, 5, 0, NOTTEX);      // TECLADO
    draw_cube(-22.5, -9.5, -13, 0.7, 0.09, 0.7, 0, 0, 0, 0, 5, 0, NOTTEX);       //BASE
    draw_cube(-22, -7, -13, 0.1, 1, 0.2, 0, 0, 0, 0, 5, 0, NOTTEX);          // BASE
    glPushMatrix(); //MOUSE
        quadric = gluNewQuadric();
        glTranslatef(-26, -9.5, -9);
        gluSphere(quadric, 0.5, 75,30);
        glRotated(90,0,1,0);
    glPopMatrix();


    //BALCÃO
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
                glTexCoord2f(1.0f, 1.0f);	glVertex3f( 50, -5, -25 );
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
        draw_cube(41,-14,zpos,0.01,3.5,0.1, 0, 0, 0, 0, 5,0, NUM_TEX);
      }
      zpos= -17;
      for(cont = 1; cont <= 6; cont++){
        draw_cube(41,-10,zpos,0.01,0.5,0.1, 0, 0, 0, 0, 5,0, NUM_TEX);
        if(cont%2 == 0){ zpos += 11; }
        else { zpos	+= 4; }
      }

    // estante
    glBindTexture(GL_TEXTURE_2D, texture_id[6]);
    float ypos = -8;

    for(cont = 0; cont < 11; cont ++, ypos += 2){
      draw_cube(-68,ypos, -3, 0.1, 0.1, 4, 0, 0, 0, 0, 5, 0, NOTTEX);
    }
    for(cont1 = 0, ypos=-6; cont1 < 18 ;cont1++, ypos++){
      zpos=7.5;
      for(cont = 0; cont < 6; cont++,zpos-=4){
        draw_cube(-68, ypos, zpos,0.6, 0.4, 0.05, 0, 0, 0, 0, 5, 0, NOTTEX);
      }
    }
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);

}
void draw_walls()
{
    glColor3f(0.9f, 0.9f, 0.9f);
    glMaterialfv(GL_FRONT, GL_EMISSION, cor_luz1);

    //TETO
    draw_quads(-70,25,-25, -70,25,25, 70,25,25, 70,25,-25,0);
    // divisoria do teto
    //draw_cube(-17, 25, -19, 1, 10, 10, 3, 0);
    draw_quads(-17,25,-25, -17,25,   25, -17,21,   25, -17,21,-25,0);
	draw_quads(-19,21,-25, -19, 21,  25, -19, 25,  25, -19, 25, -25,0);
    draw_quads(-17, 21,-25, -17, 21,  25, -19,21,  25, -19,21, -25,0);
    //chao
    draw_quads(-70.0f, -25, -25.0f, -70.0f, -25,  25.0f, 70.0f, -25,  25.0f, 70.0f, -25, -25.0f,1);
    //parede atras da estante
    draw_quads(-70, -25, 10.0f, -70, 25.1f,  10.0f, -70, 25.1f,  -25.0f, -70, -25, -25.0f,0);
    draw_quads(-70, 25.1, 25.0f, -70, 20.0f,  25.0f, -70, 20.0f,  10.0f, -70, 25.1, 10.0f,0);
    // parede embaixo da janela
    draw_quads(-30, -5,  -25.0f, 50, -5,  -25.0f, 50, -25, -25.0f, -30, -25, -25.0f,0);
    //parede em cima da janela
    draw_quads(-70, 25,  -25.0f, 70, 25,  -25.0f, 70, 20.5, -25.0f, -70, 20.5, -25.0f,0);
	draw_quads(65, 25,  -25.0f, 70, 25,  -25.0f, 70, -25, -25.0f, 65, -25, -25.0f,0);
    // parede ao lado da porta principal
    //parede ao lado da porta secundaria
    draw_quads(-70, -25,  -25.0f, -63, -25,  -25.0f, -63, 20.5, -25.0f, -70, 20.5, -25.0f,0);
    //parede acima das duas portas do fundo
    draw_quads(70.5, 20.3,  25.0f, -70, 20.3,  25.0f, -70, 25, 25.0f, 70.5, 25, 25.0f,0);
	//parede entre as duas portas 5 e 6
    draw_quads(-50, 20.3,  25.0f, -17, 20.3,  25.0f, -17, -25, 25.0f, -50, -25, 25.0f,0);
	draw_quads(23, 20.3,  25.0f, -2, 20.3,  25.0f, -2, -25, 25.0f, 23, -25, 25.0f,0);
	// parede entre a porta e a porta ao lado da estante
	draw_quads(-65, 20.3,  25.0f, -70, 20.3,  25.0f, -70, -25, 25.0f, -65, -25, 25.0f,0);
    draw_quads(70, 20.5,  25.0f, 40, 20.5,  25.0f, 40, -25, 25.0f, 70, -25, 25.0f,0);
    //parede em cima das janelas externas
    draw_quads(70.2f, 25.2, -25.2f, 70.2f, 20.5f,  -25.2f, 70.2f, 20.5f,  25.0f, 70.2f, 25.2, 25.0f,0);
    draw_quads(70.2f, -25, -25.2f, 70.2f, 20.5f,  -25.2f, 70.2f, 20.5f,  -20.0f, 70.2f, -25, -20.0f,0);

    glMaterialfv(GL_FRONT, GL_EMISSION, sem_cor);
}

void draw_doors()
{
    // porta principal
    glPushMatrix();
        glTranslatef(65,-6,-25);
        glRotated((GLfloat)door_angle,0,-1,0);
        draw_quads(0, -19,  0, -15,  -19,   0, -15,   20,   0, 0, 20,  0, 2);

    glPopMatrix();

    // porta 2 -- segue em sentido anti horário dado que o ponto inicial é a porta principal
    draw_quads(-47, -25, -25, -63,  -25, -25, -63,   15, -25, -47,   15, -25,2);
	// porta 3
	draw_quads(-70, -25, 10.0f, -70,  15,  10, -70,  15,  25.0f, -70, -25,  25.0f,3);
	//porta 4
    draw_quads(-50, -25, 25, -65, -25, 25, -65, 15, 25, -50, 15, 25,2);
	//porta 5
    draw_quads(-17,  -25,25, -2,  -25, 25, -2,   15, 25, -17,   15, 25,2);
    //porta 6
    draw_quads(23,  -25,25, 40,  -25, 25, 40,   15, 25, 23,   15, 25,2);
}
void display()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    cam[0]=raioxz*cos(2*PI*tetaxz/360);
    cam[2]=raioxz*sin(2*PI*tetaxz/360);
    gluLookAt(cam[0],cam[1],cam[2],center[0],center[1],center[2],0.0,1.0,0.0);

	init_lighting();

	draw_objects();
	draw_windows();
    draw_walls();
    draw_doors();

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
        loadTextureFromFile("textures/marmore.jpg",7);

}

void init_lighting(){

		//Habilita o uso de iluminação
		glEnable(GL_LIGHTING);
		glEnable(GL_BLEND);
	 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Habilita o modelo de colorização de Gouraud
		glEnable(GL_NORMALIZE); 
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

   glGenTextures(1, &texture_id[index]);
   glBindTexture(GL_TEXTURE_2D, texture_id[index]);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	 glBindTexture(GL_TEXTURE_2D, 0);
}
