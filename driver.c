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

#define WITH_TEXTURE true
#define WITH_BUNNY true


//definitions
/* =========================== Base Init Function =========================== */
int init(int argc, char *argv[]);
/* ~~~~~~~~~~~~~~~~ Referenced Functions ~~~~~~~~~~~~~~~~ */
int createViewVolume();
int createLights();
int createMaterials();
int createShaders();
int createTextures();

/* ============================ Passed Into GLUT ============================ */
void displayHandler();
void idleHandler();
void keyboardHandler(unsigned char key, int x, int y);


/* ============================ Helper Functions ============================ */
//simple error printing function
int pterr(int returnValue, const char *message) {
  fprintf(stderr, "%s\n", message);
  return returnValue;
}
/* ============================ Helper Variables ============================ */
//Globally defined
GLuint bunnyPointer;
GLuint bunnyVertices;
GLuint shaderProgramId;



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
            -.01, .0937, 0,  // view xyz,
            0.0, 1.0, 0.0); // up xyz
  return 0;
}

int createLights() {
  // Fill light
  float light0_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
  float light0_diffuse[] = { 0.5, 0.3, 0.8, 1.0 };
  float light0_specular[] = { 1.0, 0.4, 1.3, 1.0 };
  float light0_position[] = { 0.25, 0.3, 0.1, 1.0 };
  float light0_direction[] = { -0.2, -0.3, 0.0, 1.0};

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
  float light1_diffuse[] = { 1.2, 1.0, 0.7, 1.0 };
  float light1_specular[] = { 1.2, 1.0, 0.7, 1.0 };
  float light1_position[] = { -0.2, 0.4, -0.2, 1.0 };
  float light1_direction[] = { 0.2, -0.4, 0.2, 1.0};

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

  // Key light
  float light2_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
  float light2_diffuse[] = { 1.5, 0.0, 0.0, 1.0 };
  float light2_specular[] = { 0.8, 0.0, 0.0, 1.0 };
  float light2_position[] = { 0.1, 0.3, 0.25, 1.0 };
  float light2_direction[] = { -0.1, -0.3, -0.25, 1.0};
  // Turn off scene default ambient.
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light1_ambient);

  // Make specular correct for spots.
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1);

  glLightfv(GL_LIGHT2,GL_AMBIENT,light2_ambient);
  glLightfv(GL_LIGHT2,GL_DIFFUSE,light2_diffuse);
  glLightfv(GL_LIGHT2,GL_SPECULAR,light2_specular);
  glLightf(GL_LIGHT2,GL_SPOT_EXPONENT,1.0);
  glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,180.0);
  glLightf(GL_LIGHT2,GL_CONSTANT_ATTENUATION,0.5);
  glLightf(GL_LIGHT2,GL_LINEAR_ATTENUATION,0.1);
  glLightf(GL_LIGHT2,GL_QUADRATIC_ATTENUATION,0.01);
  glLightfv(GL_LIGHT2,GL_POSITION,light2_position);
  glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,light2_direction);

  glEnable(GL_LIGHT2);

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
  //choose the vertex shader and the fragment shader
  program->vertexShaderName = "phong.vert";
  program->fragmentShaderName = "phongTex.frag";
  // This is here in case we need to access the program's ID again
  program->programID = loadShaders(program);
  shaderProgramId = program->programID;
  return 0;
}
int createTextures() {
  int textureID = loadTexture("probe.ppm");
  int location = glGetUniformLocation(shaderProgramId, "mytexture");
  glUniform1i(location, 0);
  return 0;
}
//where the magic happens
void displayHandler() {
  //background color
  glClearColor(0.9, 0.7, 0.4, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //Texture addition
  glBindVertexArray(bunnyPointer);
  activateTexture();
  glDrawArrays(GL_TRIANGLES, 0, bunnyVertices);
  glutSwapBuffers();
}
//where the spinning happens
void idleHandler() {
  usleep(10000);
  //translates to center of bunny, then rotates the bunny, then goes back to
  //where we were
  //move to center coordinates of bunny
  glTranslatef(-0.01684,0.0,-0.00153);
  //rotate everything
  glRotatef(.3,0.0,.1,0.0);
  //move back to where I should be
  glTranslatef(0.01684,0.0,0.00153);
  glutPostRedisplay();
}
void keyboardHandler(unsigned char key, int x, int y) {
  switch(key) {
  case 'q':
    glDeleteBuffers(1,&bunnyPointer);
    exit(0);
  default:
    break;
  }
}
int init(int argc, char *argv[]) {
  BunnyData bd = loadBunny();

  //Basic GLUT setup

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|GLUT_MULTISAMPLE);
  glutInitWindowSize(768, 768);
  glutInitWindowPosition(1000, 200);
  glutCreateWindow("Hopefully a bunny");

  //Our Custom Setup Functions
  if(createViewVolume()) return pterr(-2, "Failing to make view volume???");
  if(createLights()) return pterr(-3, "Failed to create lights.");
  if(createMaterials()) return pterr(-4, "Failed with materials for bunny.");
  if(createShaders()) return pterr(-5, "Shader failure in init.");
  if(createTextures()) return pterr(-5, "Texture failure in init.");

  //Loading the bunny to the gpu
  glGenBuffers(1,&bunnyPointer);
  glBindBuffer(GL_ARRAY_BUFFER, bunnyPointer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*bd.bufferSize, bd.data, GL_STATIC_DRAW);
  glVertexPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), NULL);
  glNormalPointer(GL_FLOAT, 3 * sizeof(GLfloat), (GLfloat *)(bd.vertSize * sizeof(GLfloat)));
  glTexCoordPointer(4, GL_FLOAT, 4 * sizeof(GLfloat), (GLfloat *)(bd.colorPointer * sizeof(GLfloat)));
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  bunnyVertices = bd.totalVertices;

  // Alpha
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_CULL_FACE);
  // texture is drawn on the back of the vertices, because the bunny is backwards
  glCullFace(GL_BACK);

  // free bunny data, it's the gpu's problem now
  free(bd.data);
  return 0;
}

int main(int argc, char *argv[]) {
  if (init(argc,argv)) return pterr(-1, "Failure in init.");
  glutDisplayFunc(displayHandler);
  glutIdleFunc(idleHandler);
  glutKeyboardFunc(keyboardHandler);
  glutMainLoop();
  return 0;
}
