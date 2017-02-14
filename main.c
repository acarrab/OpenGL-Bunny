#include "parser.h"
//can be changed separately without changing the main file.
#include "lighting.h"
#include "material.h"
#include "drawStuff.h"
#include "viewVolume.h"

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
