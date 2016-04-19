CC=g++
CFLAGS=-g -c -Wall -I./ -I/usr/include/ 
LDFLAGS= -lX11
SOURCES=main.cc XditorInit.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=Xpplication

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@



clean:
	rm *o  $(EXECUTABLE)