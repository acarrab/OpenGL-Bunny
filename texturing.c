#include "texturing.h"
GLint textureLocation;
int loadTexture(const char *filename)
{
  FILE *fopen(), *fptr;
  char buf[512];
  int im_size, im_width, im_height, max_color;
  unsigned char *texture_bytes, *parse;

  fptr=fopen(filename,"r");
  if (!fptr) return -1;
  fgets(buf,512,fptr);
  do{
    fgets(buf,512,fptr);
	} while(buf[0]=='#');
  parse = strtok(buf," \t");
  im_width = atoi(parse);

  parse = strtok(NULL," \n");
  im_height = atoi(parse);

  fgets(buf,512,fptr);
  parse = strtok(buf," \n");
  max_color = atoi(parse);

  im_size = im_width*im_height;
  texture_bytes = (unsigned char *)calloc(3,im_size);
  fread(texture_bytes,3,im_size,fptr);
  fclose(fptr);
  glGenTextures(1, &textureLocation);
  glBindTexture(GL_TEXTURE_2D,textureLocation);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,im_width,im_height,0,GL_RGB,
               GL_UNSIGNED_BYTE,texture_bytes);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  cfree(texture_bytes);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_GEN_Q);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

  return 0;
}

//passing in the pointer for the shader program
void set_uniform(int p)
{
  int location;
  location = glGetUniformLocation(p,"mytexture");
  glUniform1i(location,0);
}

void activateTexture() {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureLocation);
}
