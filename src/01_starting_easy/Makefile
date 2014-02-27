# Enforce that $CC contains a valid compiler
CPP=g++

# Some variables that our compiler understands
CFLAGS=-c -Wall -O2
LDFLAGS= -L/usr/X11R6/lib -lGLU -lGL -lglut -lm 

# List of all source files
SOURCES=main.cpp Vector3D.cpp ObjectWithMass.cpp RoundObjectWithMass.cpp RBGColor.cpp

# Replace .cpp with .h the get the header files names
HEADERS=$(SOURCES:.cpp=.h)

# Replace .cpp with .o the get the object file names
OBJECTS=$(SOURCES:.cpp=.o)

# Name of our binary
EXECUTABLE=3d

.PHONY: all
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(HEADERS)
	$(CPP) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.cpp
	$(CPP) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	-rm *.o
	-rm *~ 2>/dev/null
	-rm $(EXECUTABLE)