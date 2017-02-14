#include "lighting.h"

void do_lights() {
  float light0_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
  float light0_diffuse[] = { 1.0, 1.0, 1.0, 0.0 };
  float light0_specular[] = { 1.25, 1.25, 1.25, 0.0 };
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
