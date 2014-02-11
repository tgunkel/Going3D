# Enforce that $CC contains a valid compiler
ifndef CC
CC=gcc
endif

# Some variables that our compiler understands
CFLAGS=-c -Wall -O2
LDFLAGS= -L/usr/X11R6/lib -lGLU -lGL -lglut -lm 

# List of all source files
SOURCES=main.c

# Replace .cpp with .h the get the header files names
HEADERS=$(SOURCES:.cpp=.h)

# Replace .cpp with .o the get the object file names
OBJECTS=$(SOURCES:.cpp=.o)

# Name of our binary
EXECUTABLE=3d

.PHONY: all
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(HEADERS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	-rm *.o
	-rm *~
	-rm $(EXECUTABLE)