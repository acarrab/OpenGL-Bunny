//
// This GLSL example illustrates Phong shading.  The shader is not complete,
// in that it does not include things like distance attenuation, ambient light,
// spot effects, etc., but it does do diffuse and specular on a per-pixel
// basis, rather than a per-vertex (Gouraud) basis.

// Light specifications, if made here, can also be accessed from the .frag
// program as, e.g.,
// gl_LightSource[0].position,
// gl_LightSource[0].constantAttenuation,
// gl_LightSource[0].linearAttenuation,
// gl_LightSource[0].quadraticAttenuation,
// gl_LightSource[0].spotDirection, etc.
// Distance from any point (fragment) to the light(s) is easy: length() is a
// built-in .frag function; so, apply it to the difference vector.
//
// But caution: this is lighting in world coordinates.  In general, light
// positions, when specified, are modified by the current ModelviewMatrix,
// i.e., are put into eye coordinates.  So, if you specify a light postion
// after a gluLookAt(), you'll need to do the lighting in eye coordinates,
// not world coordinates.
//
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char *read_shader_program(char *filename)
{
  FILE *fp;
  char *content = NULL;
  int fd, count;
  fd = open(filename,O_RDONLY);
  count = lseek(fd,0,SEEK_END);
  close(fd);
  content = (char *)calloc(1,(count+1));
  fp = fopen(filename,"r");
  count = fread(content,sizeof(char),count,fp);
  content[count] = '\0';
  fclose(fp);
  return content;
}

float eye[3] = {3.0,3.0,3.0};
float viewpt[3] = {0.0,0.0,0.0};
float up[3] = {0.0,1.0,0.0};
float light_position[3] = {3.0,3.0,3.0};

void set_uniform_parameters(unsigned int p)
{
  int location;
  location = glGetUniformLocation(p,"eye_position");
  glUniform3fv(location,1,eye);
  location = glGetUniformLocation(p,"light_position");
  glUniform3fv(location,1,light_position);
}

void set_material()
{
  float mat_diffuse[] = {0.1,0.9,0.0,1.0};
  float mat_specular[] = {0.9,0.1,0.0,1.0};
  float mat_shininess[] = {2.0};

  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
}

void renderScene(void)
{
  set_material();
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.5,0.4,0.3,1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0,1.0,1.0,20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye[0],eye[1],eye[2],viewpt[0],viewpt[1],viewpt[2],up[0],up[1],up[2]);
  glutSolidTorus(0.4,0.8,128,128);
  glutSwapBuffers();
}

unsigned int set_shaders()
{
  GLint vertCompiled, fragCompiled;
  char *vs, *fs;
  GLuint v, f, p;

  v = glCreateShader(GL_VERTEX_SHADER);
  f = glCreateShader(GL_FRAGMENT_SHADER);
  vs = read_shader_program("phong.vert");
  fs = read_shader_program("phong.frag");
  glShaderSource(v,1,(const char **)&vs,NULL);
  glShaderSource(f,1,(const char **)&fs,NULL);
  free(vs);
  free(fs);
  glCompileShader(v);
  glCompileShader(f);
  p = glCreateProgram();
  glAttachShader(p,f);
  glAttachShader(p,v);
  glLinkProgram(p);
  glUseProgram(p);
  return(p);
}

void getout(unsigned char key, int x, int y)
{
  switch(key) {
  case 'q':
    exit(1);
  default:
    break;
  }
}

int main(int argc, char **argv)
{
  unsigned int p;
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA|GLUT_MULTISAMPLE);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(768,768);
  glutCreateWindow("phong-shaded donut");
  glEnable(GL_MULTISAMPLE_ARB);
  p = set_shaders();
  set_uniform_parameters(p);
  glutDisplayFunc(renderScene);
  glutKeyboardFunc(getout);
  glutMainLoop();
  return 0;
}
