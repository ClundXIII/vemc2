#Makefile for graphiclib for vemc2
#Simon Michalke, (c) 2014

CC=g++
CFLAGS=-pthread -std=c++11 -fPIC -c -O3 #optimized
#CFLAGS=-pthread -std=c++11 -fPIC -c -Wall -g -fsanitize=address #debugging
LDFLAGS=-pthread -std=c++11 -lvesper-log -lvcore -lGL -lGLU -lglut #-fsanitize=address
INCLDIR=-I./..

all: libvgl main

clean:
	@touch temp/dummy
	rm temp/*

libvgl: temp/graphic.o temp/draws.o
	$(CC) -g -shared -Wl,-soname,libvgl.so.`cat version | head -c 1` -o libvgl.so.`cat version` \
	temp/graphic.o temp/draws.o \
	$(LDFLAGS) -L/opt/lib/vemc2/ -lvcore

install: libvgl
	mkdir -p /usr/local/lib
	cp libvgl.so.`cat version` /usr/local/lib/libvgl.so
	rm /usr/local/lib/libvgl.so.0
	ln -s /usr/local/lib/libvgl.so /usr/local/lib/libvgl.so.0
	mkdir -p /usr/local/include/vemc2/graphic
	cp graphic.h /usr/local/include/vemc2/graphic/
	cp draws.h   /usr/local/include/vemc2/graphic/
	ldconfig

main: temp/main.o temp/graphic.o temp/draws.o
	$(CC) -g -o graphicgl \
	temp/main.o temp/graphic.o temp/draws.o \
	$(LDFLAGS)

#all source files:
temp/main.o: main.cpp graphic.h
	$(CC) $(CFLAGS) $(INCLDIR) main.cpp      -o temp/main.o
temp/graphic.o: graphic.cpp graphic.h
	$(CC) $(CFLAGS) $(INCLDIR) graphic.cpp   -o temp/graphic.o
temp/draws.o: draws.cpp draws.h
	$(CC) $(CFLAGS) $(INCLDIR) draws.cpp     -o temp/draws.o


#header files:
graphic.h:
draws.h:
