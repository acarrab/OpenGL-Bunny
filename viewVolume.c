#include "viewVolume.h"

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
