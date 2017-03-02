#include "bunny.h"
BunnyData loadBunny() {
  BunnyData  bd;
  VertexData *vd = parseFrom("bunnyN.ply");
  if (!vd) {
    fprintf(stderr, "Bunny Parse failed.\n");
    return bd;
  }

  bd.totalTriangles = vd->faceCount;
  bd.totalVertices  = vd->faceCount * 3;
  bd.vertSize       = vd->faceCount * 3 * 3;
  bd.dataSize       = vd->faceCount * 3 * 3 * 2;
  bd.colorPointer   = vd->faceCount * 3 * 3 * 2;
                       //4 color params
  bd.bufferSize     = vd->faceCount * 3 * 3 * 2 + vd->faceCount * 3 * 4;


  bd.data = (GLfloat *)malloc(sizeof(GLfloat)*bd.bufferSize);


  int x = 0, y = bd.vertSize;
  int i,j,k;
  for (i = 0; i < bd.totalTriangles; i++) {
    for (j = 0; j < 3; j++) {
      VertexElement *e = &(vd->vertEle[vd->faceEle[i].indice[j]]);
      for (k = 0; k < 3; k++) {
        bd.data[x++] = e->vertice[k];
        bd.data[y++] = e->normal[k];
      }
    }
  }
  for (i = 0; i < bd.totalTriangles; i++) {
    for (j= 0; j < 3; j++) {
      bd.data[y++] = 0.5;//r
      bd.data[y++] = 0.5;//g
      bd.data[y++] = 0.5;//b
      bd.data[y++] = 1.0;//a
    }
  }
  return bd;
}
