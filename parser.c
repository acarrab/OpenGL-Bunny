#include "parser.h"

bool there(FILE *f, const char *previous, const char *current) {
  static char prev[50] = "\0", curr[50] = "\0";
  strcpy(prev, curr);
  if (!fscanf(f, "%s", curr)) return NULL;
  return (strcmp(prev, previous) || strcmp(curr, current)) == 0;
}

VertexData* parseFrom(const char * fileName) {
  FILE *f = fopen(fileName, "r");
  int i;
  VertexData *vd = (VertexData *)malloc(sizeof(VertexData));
  char curr[50] = "\0";

  //get to vertex count
  while (!there(f, "element\0", "vertex\0"));
  if (!fscanf(f, "%d", &vd->vertCount)) return NULL;
  //get to face count.
  while (!there(f, "element\0", "face\0"));
  if (!fscanf(f, "%d", &vd->faceCount)) return NULL;
  //get to end of header
  while (strcmp(curr, "end_header\0"))
    if (!fscanf(f, "%s", curr)) return NULL;



  //allocate memory
  vd->vertEle = (VertexElement*)malloc(sizeof(VertexElement)*vd->vertCount);
  vd->faceEle = (FaceElement*)malloc(sizeof(FaceElement)*vd->faceCount);

  //now to read vertices
  for (i = 0; i < vd->vertCount; i++) {
    if (!fscanf(f,"%f %f %f",
                &(vd->vertEle[i].vertice[0]),
                &(vd->vertEle[i].vertice[1]),
                &(vd->vertEle[i].vertice[2]))) {
      return NULL;
    }
    if (!fscanf(f,"%f %f %f",
                &(vd->vertEle[i].normal[0]),
                &(vd->vertEle[i].normal[1]),
                &(vd->vertEle[i].normal[2])))  {
      return NULL;
    }
  }

  //now for the element face
  int throwOut;
  for (i = 0; i < vd->faceCount; i++) {
    if (!fscanf(f,"%d %d %d %d",
                &throwOut,
                &(vd->faceEle[i].indice[0]),
                &(vd->faceEle[i].indice[1]),
                &(vd->faceEle[i].indice[2]))) {
      return NULL;
    }
  }

  return vd;
}
