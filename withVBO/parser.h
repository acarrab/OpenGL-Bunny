#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <string.h>
typedef struct VERTICE_ELEMENT_DATA {
  GLfloat vertice[3];
  GLfloat normal[3];
} VertexElement;

//it is always 3 for this lab since we are using only triangles.
typedef struct FACE_ELEMENT_DATA {
  GLint indice[3];
} FaceElement;

//Data from the file
typedef struct VERTEX_DATA {
  GLint vertCount;
  VertexElement *vertEle;

  GLint faceCount;
  FaceElement *faceEle;
} VertexData;

VertexData* parseFrom(const char * fileName);

#endif
