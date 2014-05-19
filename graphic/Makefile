#Makefile for graphiclib for vemc2
#Simon Michalke, (c) 2014

CC=g++
#CFLAGS=-std=c++0x -fPIC -c -O3#optimized
CFLAGS=-std=c++0x -fPIC -c -Wall -g #debugging
LDFLAGS=-pthread
INCLDIR=-L./../header

all: libvgl main

libvgl: temp/graphic.o
	$(CC) -g -shared -Wl,-soname,libvgl.so.`cat version | head -c 1` -o libvgl.so.`cat version` \
	temp/graphic.o \
	$(LDFLAGS) -L/opt/lib/vemc2/ -lvcore

main: temp/main.o temp/graphic.o
	$(CC) -g -o graphicgl \
	temp/main.o temp/graphic.o \

#all source files:
temp/main.o: main.cpp graphic.h
	$(CC) $(CFLAGS) $(INCLDIR) main.cpp      -o temp/main.o
temp/graphic.o: graphic.cpp graphic.h
	$(CC) $(CFLAGS) $(INCLDIR) graphic.cpp   -o temp/graphic.o


#header files:
graphic.h:
