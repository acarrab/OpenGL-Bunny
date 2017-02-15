
#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

/*
	Reads data from file into a string
*/
char *readShader(char *filename) 
{
	char *content = NULL;
	int fd, count;
	fd = open(filename, O_RDONLY);
	count = lseek(fd, 0, SEEK_END);
	content = (char *)calloc(1, (count+1));
	lseek(fd, 0, SEEK_SET);
	count = read(fd, content, count*sizeof(char));
	content[count] = '\0';
	close(fd);
	return content;
}

/*
	Attaches shaders to a program, returns the program's ID,
	and sets this shader program as the active program in OpenGL
*/
int loadShaders(ShaderProgram *program)
{
	GLint vertCompiled, fragCompiled;
	char *vs, *fs;
	GLuint p;
	program->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	program->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	vs = readShader(program->vertexShaderName);
	fs = readShader(program->fragmentShaderName);

	glShaderSource(program->vertexShaderID, 1, (const char **)&vs, NULL);
	glShaderSource(program->fragmentShaderID, 1, (const char **)&fs, NULL);
	free(vs);
	free(fs);

	glCompileShader(program->vertexShaderID);
	glCompileShader(program->fragmentShaderID);
	p = glCreateProgram();
	glAttachShader(p, program->fragmentShaderID);
	glAttachShader(p, program->vertexShaderID);
	glLinkProgram(p);
	glUseProgram(p);
	return p;
}

/*
	Loads any variables that need to be passed into the shaders
*/
void loadVariables(ShaderProgram *program)
{
	
}
