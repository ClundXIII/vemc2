#Makefile for vemc2 (c) by Simon Michalke
#this is the libcore Makefile, so we only get a .so

CC=g++
#FLAGS=-c #optimized
FLAGS=-c -Wall -g #debugging

all: libvcore.so

preinst:
	mkdir -p /opt/lib
	mkdir -p /opt/lib/vemc2
	chown 1000:1000 /opt/lib/vemc2
	echo "/opt/lib/vemc2" > /etc/ld.so.conf.d/vemc2.conf

install: all
	cp libvcore.so /opt/lib/vemc2/
	mv /opt/lib/vemc2/libvcore.so /opt/lib/vemc2/libvcore.so.`cat version`
	ln -fs /opt/lib/vemc2/libvcore.so.`cat version`              /opt/lib/vemc2/libvcore.so.`cat version | head -c 3`
	ln -fs /opt/lib/vemc2/libvcore.so.`cat version | head -c 3`  /opt/lib/vemc2/libvcore.so.`cat version | head -c 1`
	ln -fs /opt/lib/vemc2/libvcore.so.`cat version | head -c 1`  /opt/lib/vemc2/libvcore.so

install-local: all
	sudo echo "$pwd" > /etc/ld.so.conf.d/vemc2.conf
	
	ln -fs libvcore.so.`cat version`             libvcore.so.0.0`cat version | head -c 3`
	ln -fs libvcore.so.`cat version | head -c 3` libvcore.so.0`cat version | head -c 1`
	ln -fs libvcore.so.`cat version | head -c 1` libvcore.so

uninstall:
	rm -f  /etc/ld.so.conf.d/vemc2.conf
	rm -rf /opt/lib/vemc2

libcore.so:


