#include "parser.h"
//can be changed separately without changing the main file.
#include "lighting.h"
#include "material.h"
#include "drawStuff.h"

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


int main(int argc, char *argv[]) {
  if (initVertexData()) return -1;

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
