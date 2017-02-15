#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <GL/gl.h>
#include <GL/glut.h>

typedef struct SHADER_PROGRAM {
	char *vertexShaderName;
	char *fragmentShaderName;
	int vertexShaderID;
	int fragmentShaderID;

	int programID;
} ShaderProgram;

char *readShader(char *filename);
int loadShaders(ShaderProgram *program);
void loadVariables(ShaderProgram *program);


#endif
