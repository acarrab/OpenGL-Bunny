#ifndef BUNNY_H
#define BUNNY_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "parser.h"

typedef struct BUNNYDATA{
  int totalTriangles, totalVertices;
  int vertSize, dataSize, bufferSize;
  int colorPointer;
  GLfloat *data;
} BunnyData;

BunnyData loadBunny();

#endif
