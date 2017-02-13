CFLAGS=-lX11 -lGL -lGLU -lglut -lm -lXmu -lXi
CCC=gcc -L/usr/lib64 -O2


run:
	$(CCC) main.c parser.c -o run $(CFLAGS)

clean:
	rm run
