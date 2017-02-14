# the compiler we are using
CXX = gcc -L/usr/lib64 -O2
# some warning generators
CXXFLAGS= -Wall
# libraries to include
LDFLAGS = -lX11 -lGL -lGLU -lglut -lm -lXmu -lXi -lm
# objects that will be generated
OBJS = \
	main.o drawStuff.o lighting.o material.o parser.o viewVolume.o
# the executable to create
EXEC = run

# %.o defines a rule that applies to all files ending in .o suffix
# and each depends on the corresponding file ending in a .cpp
# $< is the first item in the dependencies list
# $@ refers to the left side of the :
%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.c parser.h lighting.h material.h drawStuff.h viewVolume.h

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
