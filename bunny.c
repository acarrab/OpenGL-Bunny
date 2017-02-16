#include "bunny.h"
BunnyData* loadBunny() {
  VertexData *vd = parseFrom("bunnyN.ply");
  if (!vd) {
    fprintf(stderr, "Bunny Parse failed.\n");
    return NULL;
  }
  BunnyData * bd = (BunnyData *)malloc(sizeof(BunnyData));

  bd->totalTriangles = vd->faceCount;
  bd->totalVertices  = vd->faceCount * 3;
  bd->vertSize       = vd->faceCount * 3 * 3;
  bd->dataSize       = vd->faceCount * 3 * 3 * 2;

  bd->data = (GLfloat *)malloc(sizeof(GLfloat)*bd->dataSize);


  int x = 0, y = bd->vertSize;
  int i,j,k;
  for (i = 0; i < bd->totalTriangles; i++) {
    for (j = 0; j < 3; j++) {
      VertexElement *e = &(vd->vertEle[vd->faceEle[i].indice[j]]);
      for (k = 0; k < 3; k++) {
        bd->data[x++] = e->vertice[k];
        bd->data[y++] = e->normal[k];
      }
    }
  }
  return bd;
}
