#Makefile for vemc2 (c) by Simon Michalke, 2014

CC=g++
#CFLAGS=-c -O3 -I./../core #optimized
CFLAGS=-c -Wall -g -I./../core #debugging
LDFLAGS=-L/opt/lib/vemc2/ -lvcore


all: vemc2_nogui

clean:
	@touch temp/dummy
	rm temp/*

vemc2_nogui: temp/main.o
	$(CC) -o vemc2_nogui temp/main.o $(LDFLAGS)

#all source files:

temp/main.o: main.cpp includesfm.h
	$(CC) $(CFLAGS) main.cpp      -o temp/main.o

#all header files:
includesfm.h:

