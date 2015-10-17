#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SOIL.h>
#define PI 3.1415
#define NUM_TEX 7

void draw_wall(float x1,float y1, float z1,
			float x2, float y2, float z2,
			float x3, float y3, float z3,
			float x4, float y4, float z4, int tex_index);

void display();
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void init_textures();
void loadTextureFromFile(char *filename,int index);
void init_lighting();
