#include "material.h"
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
