#include "drawStuff.h"

static VertexData *vertexData = NULL;

void draw_stuff() {
  int i, j;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE_ARB);

  glClearColor(0.35,0.35,0.35,0.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  for (i = 0; i < vertexData->faceCount; i++) {
    glBegin(GL_TRIANGLES);
    for (j = 0; j < 3; j++) {
      VertexElement *e = &(vertexData->vertEle[vertexData->faceEle[i].indice[j]]);
      glNormal3f(e->normal[0], e->normal[1], e->normal[2]);
      glVertex3f(e->vertice[0], e->vertice[1], e->vertice[2]);
    }
    glEnd();
  }
  glFlush();
}

int initVertexData() {
  vertexData = parseFrom("bunnyN.ply");
  if (!vertexData) return -1;

  GLfloat min[3], max[3];
  int i, j;
  for (j = 0; j < 3; j++) {
    if (max[j] < vertexData->vertEle[0].vertice[j]) max[j] = vertexData->vertEle[0].vertice[j];
    if (min[j] > vertexData->vertEle[0].vertice[j]) min[j] = vertexData->vertEle[0].vertice[j];
  }
  for (i = 1; i < vertexData->vertCount; i++) {
    for (j = 0; j < 3; j++) {
      if (max[j] < vertexData->vertEle[i].vertice[j]) max[j] = vertexData->vertEle[i].vertice[j];
      if (min[j] > vertexData->vertEle[i].vertice[j]) min[j] = vertexData->vertEle[i].vertice[j];
    }
  }
  fprintf(stdout, "min(x,y,z) = (%f,%f,%f)\n", min[0],min[1],min[2]);
  fprintf(stdout, "max(x,y,z) = (%f,%f,%f)\n", max[0],max[1],max[2]);
  fflush(stdout);
  return 0;
}
