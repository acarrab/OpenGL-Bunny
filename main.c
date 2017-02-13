#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>

VertexData *vd;
struct point { float x, y, z; };
void do_viewvolume() {
  //note that these are the max coordinates in the bunny.
  /*
    min(x,y,z) = (-0.094690,0.000000,-0.061874)
    max(x,y,z) = (0.061009,0.187321,0.058800)
  */

  struct point eye;
  struct point view;
  struct point up;

  // specify size and shape of view volume
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0,1.0,0.1,20.0);

  // specify position for view volume
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  eye.x = .2; eye.y = .2; eye.z = .2;

  view.x = -0.0168405; view.y = 0.0936605; view.z = -0.001537;
  up.x = 0.0; up.y = 1; up.z = 0.0;
  gluLookAt(eye.x,eye.y,eye.z,view.x,view.y,view.z,up.x,up.y,up.z);
}
void draw_stuff() {
  int i, j;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE_ARB);

  glClearColor(0.35,0.35,0.35,0.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  for (i = 0; i < vd->faceCount; i++) {
    glBegin(GL_TRIANGLES);
    for (j = 0; j < 3; j++) {
      VertexElement *e = &(vd->vertEle[vd->faceEle[i].indice[j]]);
      glNormal3f(e->normal[0], e->normal[1], e->normal[2]);
      glVertex3f(e->vertice[0], e->vertice[1], e->vertice[2]);
    }
    glEnd();
  }
  glFlush();
}

void do_lights() {
  float light0_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
  float light0_diffuse[] = { 2.0, 2.0, 2.0, 0.0 };
  float light0_specular[] = { 2.25, 2.25, 2.25, 0.0 };
  float light0_position[] = { 1.5, 2.0, 2.0, 1.0 };
  float light0_direction[] = { -1.5, -2.0, -2.0, 1.0};

  // set scene default ambient
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light0_ambient);

  // make specular correct for spots
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1);
  glLightfv(GL_LIGHT0,GL_AMBIENT,light0_ambient);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);
  glLightfv(GL_LIGHT0,GL_SPECULAR,light0_specular);
  glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,0.1);
  glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,180.0);
  glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,1.0);
  glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,0.2);
  glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,0.01);
  glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
  glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,light0_direction);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void do_material() {
  float mat_ambient[] = {0.0,0.0,0.0,1.0};
  float mat_diffuse[] = {0.9,0.9,0.1,1.0};
  float mat_specular[] = {1.0,1.0,1.0,1.0};
  float mat_shininess[] = {2.0};

  glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
}
int main(int argc, char *argv[]) {
  vd = parseFrom("bunnyN.ply");
  if (!vd) return -1;

  GLfloat min[3], max[3];
  int i, j;
  for (j = 0; j < 3; j++) {
    if (max[j] < vd->vertEle[0].vertice[j]) max[j] = vd->vertEle[0].vertice[j];
    if (min[j] > vd->vertEle[0].vertice[j]) min[j] = vd->vertEle[0].vertice[j];
  }
  for (i = 1; i < vd->vertCount; i++) {
    for (j = 0; j < 3; j++) {
      if (max[j] < vd->vertEle[i].vertice[j]) max[j] = vd->vertEle[i].vertice[j];
      if (min[j] > vd->vertEle[i].vertice[j]) min[j] = vd->vertEle[i].vertice[j];
    }
  }

  fprintf(stdout, "min(x,y,z) = (%f,%f,%f)\n", min[0],min[1],min[2]);
  fprintf(stdout, "max(x,y,z) = (%f,%f,%f)\n", max[0],max[1],max[2]);
  fflush(stdout);

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_MULTISAMPLE);
  glutInitWindowSize(768,768);
  glutInitWindowPosition(100,50);
  glutCreateWindow("my_cool_cube");
  do_viewvolume();
  do_lights();
  do_material();
  glutDisplayFunc(draw_stuff);
  glutMainLoop();


  return 0;
}
