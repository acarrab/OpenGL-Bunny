//
// GLSL example 1, basic.c, a nearly trivial displacement and re-coloring.
//
// Without the GLSL shader hooked in, this draws a black square,
// centrally placed, on a red background.  With the shader hooked in, the
// square is reduced to quarter size, placed in the northeast quadrant, and
// rendered in green.
//
// The compile line is the standard OpenGL line:
// gcc -I/usr/include -I/usr/X11R6/include -L/usr/lib -L/usr/X11R6/lib -O2
//     $1.c -lX11 -lGL -lGLU -lglut -lm -lXmu -lXi -o $1

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char *read_shader_program(char *filename)
{
char *content = NULL;
int fd, count;
fd = open(filename,O_RDONLY);
count = lseek(fd,0,SEEK_END);
content = (char *)calloc(1,(count+1));
lseek(fd,0,SEEK_SET);
count = read(fd,content,count*sizeof(char));
content[count] = '\0';
close(fd);
return content;
}

unsigned int set_shaders()
{
GLint vertCompiled, fragCompiled;
char *vs, *fs;
GLuint v, f, p;

v = glCreateShader(GL_VERTEX_SHADER);
f = glCreateShader(GL_FRAGMENT_SHADER);
vs = read_shader_program("basic.vert");
fs = read_shader_program("basic.frag");
glShaderSource(v,1,(const char **)&vs,NULL);
glShaderSource(f,1,(const char **)&fs,NULL);
free(vs);
free(fs);
glCompileShader(v);
glCompileShader(f);
p = glCreateProgram();
glAttachShader(p,f);
glAttachShader(p,v);
glLinkProgram(p);
glUseProgram(p);
return(p);
}

void renderScene(void)
{
// Clear the background to red.
glClearColor(1.0,0.0,0.0,0.0);
glClear(GL_COLOR_BUFFER_BIT);

// Draw a 2D square in black.
glColor3f(0.0,0.0,0.0);
glBegin(GL_QUADS);
glVertex2f(-0.5,-0.5);
glVertex2f(-0.5,0.5);
glVertex2f(0.5,0.5);
glVertex2f(0.5,-0.5);
glEnd();
glFlush();
}

void getout(unsigned char key, int x, int y)
{
switch(key) {
        case 'q':
                exit(1);
        default:
                break;
    }
}

int main(int argc, char **argv)
{
unsigned int p;
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_RGBA);
glutInitWindowPosition(100, 100);
glutInitWindowSize(768, 768);
glutCreateWindow("basic GLSL demo");
// Comment this out to see default operation, without shaders:
set_shaders();
glutDisplayFunc(renderScene);
glutKeyboardFunc(getout);
glutMainLoop();
return 0;
}
