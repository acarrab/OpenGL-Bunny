//
// This is a demo of vertex arrays (and normal arrays) using VBOs.
// It uses glDrawArrays to zap the entire image to the FB in one call.
//

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <unistd.h>
#include "parser.h"
#include "shader.h"



struct point {
  float x;
  float y;
  float z;
};

void setup_the_viewvol()
{
  struct point eye;
  struct point view;
  struct point up;

  glEnable(GL_DEPTH_TEST);

  // Specify the size and shape of the view volume.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0,1.0,0.1,20.0);

  // Specify the position for the view volume.
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();


  //### These are more appropriate for looking at the bunny.
  eye.x = .2; eye.y = .2; eye.z = .2;
  view.x = 0; view.y = 0.0936605; view.z = 0;
  up.x = 0.0; up.y = 1.0; up.z = 0.0;

  gluLookAt(eye.x,eye.y,eye.z,view.x,view.y,view.z,up.x,up.y,up.z);
}

int vertexCount;
void draw_stuff()
{
  glEnable(GL_MULTISAMPLE);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  // 0 is starting index in the array; 24 is number of indices to be rendered
  glDrawArrays(GL_TRIANGLES,0,vertexCount);
  glutSwapBuffers();
}

void update()
{
  usleep(10000);
  //### This translates the focus to the center of the bunny. Or at least the
  //### average of the min and max for the x and z values.
  glTranslatef(-0.01684,0.0,-0.00153);
  //### we then rotate the bunny once we are there.
  glRotatef(.5,0.0,.1,0.0);
  //### we then have to go back to where we were for the camera and stuff
  glTranslatef(0.01684,0.0,0.00153);
  glutPostRedisplay();
}

void do_lights()
{
  // Key light
  float light0_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
  float light0_diffuse[] = { 0.0, 1.0, 1.0, 0.0 };
  float light0_specular[] = { 1.0, 0.0, 1.0, 0.0 };
  float light0_position[] = { 0.5, 2.0, 0.5, 1.0 };
  float light0_direction[] = { -1.5, -2.0, -2.0, 1.0};

  // Turn off scene default ambient.
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light0_ambient);

  // Make specular correct for spots.
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1);

  glLightfv(GL_LIGHT0,GL_AMBIENT,light0_ambient);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);
  glLightfv(GL_LIGHT0,GL_SPECULAR,light0_specular);
  glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,1.0);
  glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,180.0);
  glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,0.5);
  glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,0.1);
  glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,0.01);
  glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
  glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,light0_direction);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

	// Back light
	float light1_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
  float light1_diffuse[] = { 0.0, .8, .8, 0.0 };
  float light1_specular[] = { 1.0, 1.0, 1.0, 0.0 };
  float light1_position[] = { -0.5, 2.0, -0.5, 1.0 };
  float light1_direction[] = { 0.5, -2.0, 0.5, 1.0};

  // Turn off scene default ambient.
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light1_ambient);

  // Make specular correct for spots.
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1);

  glLightfv(GL_LIGHT1,GL_AMBIENT,light1_ambient);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_diffuse);
  glLightfv(GL_LIGHT1,GL_SPECULAR,light1_specular);
  glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,1.0);
  glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,180.0);
  glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION,0.5);
  glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION,0.1);
  glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,0.01);
  glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
  glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,light1_direction);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT1);
}

void do_material()
{
  float mat_ambient[] = {1.0,1.0,1.0,1.0};
  float mat_diffuse[] = {0.9,0.9,0.9,1.0};
  float mat_specular[] = {0.7,0.7,0.7,1.0};
  float mat_shininess[] = {15.0};

  glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
}

int mybuf = 1;

void initOGL(int argc, char **argv)
{

  //###gets the parsed data from bunnyN.ply, as specified in parser.h
  VertexData *vd = parseFrom("bunnyN.ply");
  if (!vd) {
    printf("The parse failed\n");
    exit(-1);
  }
  //### total triangles is equal to faceCount
  int totalTriangles = vd->faceCount;
  // total points, 3 per triangle
  int totalVertices = totalTriangles * 3;
  //### total floats, 3 per xyz
  int totalPointVals = totalVertices * 3;
  //### total size of our vertexData array
  int dataSize = totalPointVals * 2; //because of normals.

  GLfloat *vertexData = (GLfloat*)malloc(sizeof(GLfloat)*dataSize);
  //### y starts at the half way point in the vertexData array
  int x = 0, y = totalPointVals, i, j, k;

  //### populating the array
  for (i = 0; i < totalTriangles; i++) {
    for(j = 0; j < 3; j++) {
      VertexElement *e = &(vd->vertEle[vd->faceEle[i].indice[j]]);
      for (k = 0; k < 3; k++) {
        vertexData[x++] = e->vertice[k];
        vertexData[y++] = e->normal[k];
      }
    }
  }
  //### this sets the amount of vertices that will be rendered
  vertexCount = totalVertices;




  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|GLUT_MULTISAMPLE);
  glutInitWindowSize(768,768);
  glutInitWindowPosition(100,50);
  glutCreateWindow("Hopefully a bunny");
  setup_the_viewvol();
  do_lights();
  do_material();
  glBindBuffer(GL_ARRAY_BUFFER,mybuf);
  glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*dataSize,vertexData,GL_STATIC_DRAW);
  // When using VBOs, the final arg is a byte offset in buffer, not the address,
  // but gl<whatever>Pointer still expects an address type, hence the NULL.
  glVertexPointer(3,GL_FLOAT,3*sizeof(GLfloat),NULL+0);
  glNormalPointer(GL_FLOAT,3*sizeof(GLfloat),NULL+totalPointVals*sizeof(GLfloat));
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glClearColor(0.35,0.35,0.35,0.0);
}

void getout(unsigned char key, int x, int y) {
  switch(key) {
  case 'q':
    glDeleteBuffers(1,&mybuf);
    exit(1);
  default:
    break;
  }
}

void do_shaders() {
	ShaderProgram *program;
	program->vertexShaderName = "phong.vert";
	program->fragmentShaderName = "phong.frag";\
	// This is here in case we need to access the program's ID again
	program->programID = loadShaders(program);

	loadVariables(program);
}

int main(int argc, char **argv) {
  initOGL(argc,argv);
  do_shaders();
  glutDisplayFunc(draw_stuff);
  glutIdleFunc(update);
  glutKeyboardFunc(getout);
  glutMainLoop();
  return 0;
}
