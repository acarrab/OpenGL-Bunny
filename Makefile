# the compiler we are using
CXX = gcc -I/usr/include -I/usr/X11R6/include -L/usr/lib -L/usr/X11R6/lib -O0
# some warning generators
CXXFLAGS= -g
# libraries to include
LDFLAGS = -lX11 -lGL -lGLU -lglut -lm -lXmu -lXi
# objects that will be generated
OBJS = \
	driver.o parser.o
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

driver.o: driver.c parser.h

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
