//gets rid of implicit declaration problems or at least some of them
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "shader.h"
#include "texturing.h"
#include "bunny.h"

#define WITH_TEXTURE false
#define WITH_BUNNY true

//Global variables
GLuint bunnyPointer;
GLuint bunnyVertices;
GLuint shaderProgramId;

//simple error printing function
int pterr(int returnValue, const char *message) {
  fprintf(stderr, "%s\n", message);
  return returnValue;
}

int createViewVolume() {
  glEnable(GL_DEPTH_TEST);


  // Specify shape and size of the view volume.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); //load identity matrix into GL_PROJECTION
  gluPerspective(45.0, 1.0, 0.1, 20.0);

  // Specify the position for the view volume
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.2, 0.2, 0.2,  // eye xyz,
            0.0, .0937, 0,  // view xyz,
            0.0, 1.0, 0.0); // up xyz
  return 0;
}

int createLights() {
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

  return 0;
}

int createMaterials() {
  float mat_ambient[] = {1.0,1.0,1.0,1.0};
  float mat_diffuse[] = {0.9,0.9,0.9,1.0};
  float mat_specular[] = {0.7,0.7,0.7,1.0};
  float mat_shininess[] = {15.0};

  glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
  return 0;
}

int createShaders() {
	ShaderProgram *program = (ShaderProgram *)malloc(sizeof(ShaderProgram));

	program->vertexShaderName = "phong.vert";
  if (WITH_TEXTURE)
    program->fragmentShaderName = "phongTex.frag";
  else
    program->fragmentShaderName = "phong.frag";
	// This is here in case we need to access the program's ID again
	program->programID = loadShaders(program);
	loadVariables(program);
  shaderProgramId = program->programID;
  return 0;
}
int createTextures() {
  loadTexture("space.ppm");
  int location = glGetUniformLocation(shaderProgramId, "mytexture");
  glUniform1i(location,0);
  return 0;
}
//where the magic happens
void displayHandler() {
  glClearColor(0.1, 0.1, 0.4, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //Texture addition
  if (WITH_BUNNY) glBindVertexArray(bunnyPointer);
  if (WITH_TEXTURE) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 1);
  }
  if (WITH_BUNNY) {
    glDrawArrays(GL_TRIANGLES, 0, bunnyVertices);
  } else {
    glTranslatef(-.01,0.06,0);
    glutSolidTeapot(.07);
    glTranslatef(.01,-0.06,0);
  }
  glutSwapBuffers();
}
//where the spinning happens
void idleHandler() {
  usleep(10000);
  //translates to center of bunny, then rotates the bunny, then goes back to
  //where we were
  if (WITH_BUNNY) {
    glTranslatef(-0.01684,0.0,-0.00153);
    glRotatef(.5,0.0,.1,0.0);
    glTranslatef(0.01684,0.0,0.00153);
  } else {
    glTranslatef(-.01,0.0,0);
    glRotatef(.5,0.0,.1,0.0);
    glTranslatef(.01,0.0,0);
  }
  glutPostRedisplay();
}
void keyboardHandler(unsigned char key, int x, int y) {
  switch(key) {
  case 'q':
    glDeleteBuffers(1,&bunnyPointer);
    exit(1);
  default:
    break;
  }
}
int init(int argc, char *argv[]) {
  BunnyData *bd = loadBunny();//should probably free this stuff at some point+++
  if (!bd) return pterr(-1, "Bunny Failure, all hope is lost...");

  //Basic GLUT setup

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|GLUT_MULTISAMPLE);
  glutInitWindowSize(768, 768);
  glutInitWindowPosition(4000, 200);
  glutCreateWindow("Hopefully a bunny");

  //Our Custom Setup Functions
  if(createViewVolume()) return pterr(-2, "Failing to make view volume???");
  if(createLights()) return pterr(-3, "Failed to create lights.");
  if(createMaterials()) return pterr(-4, "Failed with materials for bunny.");
  if(createShaders()) return pterr(-5, "Shader failure in init.");
  if (WITH_TEXTURE && createTextures()) return pterr(-5, "Texture failure in init.");

  //Loading the bunny to the gpu
  glGenBuffers(1,&bunnyPointer);
  glBindBuffer(GL_ARRAY_BUFFER, bunnyPointer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*bd->dataSize, bd->data, GL_STATIC_DRAW);
  glVertexPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), NULL);
  glNormalPointer(GL_FLOAT, 3 * sizeof(GLfloat), (GLfloat *)(bd->vertSize * sizeof(GLfloat)));
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  bunnyVertices = bd->totalVertices;

  return 0;
}

int main(int argc, char *argv[]) {
  if (init(argc,argv)) pterr(-1, "Failure in init.");
  glutDisplayFunc(displayHandler);
  glutIdleFunc(idleHandler);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();
  return 0;
}
