#Makefile for vemc2 (c) by Simon Michalke, 2014

#vesper-dir=/media/simon/simondss/42vesper/fork
vesper-dir=$(HOME)/vesper-libs-fork
cmake-build-path=/bin

CC=g++
#CFLAGS=-I$(vesper-dir) -std=c++0x -c -O3 -I./../core #optimized
CFLAGS=-I$(vesper-dir) -std=c++0x -c -Wall -g -I./../core #debugging
LDFLAGS=-L/opt/lib/vemc2/ -lvcore -Wl,-rpath=$(vesper-dir)$(cmake-build-path) -l:libvesper-log.so


all: vemc2_nogui

clean:
	@touch temp/dummy
	rm temp/*

vemc2_nogui: temp/main.o
	cp $(vesper-dir)$(cmake-build-path)/lib*.so ./
	$(CC) -o vemc2_nogui temp/main.o $(LDFLAGS)

#all source files:

temp/main.o: main.cpp includesfm.h
	$(CC) $(CFLAGS) main.cpp      -o temp/main.o

#all header files:
includesfm.h:

