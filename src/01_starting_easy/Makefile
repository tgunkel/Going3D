# Enforce that $CC contains a valid compiler
CPP=g++

# Some variables that our compiler understands
CFLAGS=-c -Wall -O2
LDFLAGS= -L/usr/X11R6/lib -lGLU -lGL -lglut -lm 

# List of all source files
SOURCES=main.cpp Vector3D.cpp ObjectWithMass.cpp RoundObjectWithMass.cpp RBGColor.cpp SystemWithObjects.cpp Camera.cpp WorldModelReaderNasa.cpp PlatteCarrePoint.cpp Tile.cpp

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
	-rm *.o 2>/dev/null
	-rm modelreader/*.o 2>/dev/null
	-rm *~  2>/dev/null
	-rm modelreader/*~  2>/dev/null
	-rm $(EXECUTABLE) 2>/dev/null