#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
//gets rid of implicit declaration problems or at least some of them
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


typedef struct SHADER_PROGRAM {
	char *vertexShaderName;
	char *fragmentShaderName;
	int vertexShaderID;
	int fragmentShaderID;

	int programID;
} ShaderProgram;

char *readShader(char *filename);
int loadShaders(ShaderProgram *program);


#endif
