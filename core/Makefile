#Makefile for vemc2 (c) by Simon Michalke
#this is the libcore Makefile, so we only get a .so

CC=g++
#CFLAGS=-c -O3#optimized
CFLAGS=-c -Wall -g #debugging
LDFLAGS=

all: libvcore.so

preinst:
	mkdir -p /opt/lib
	mkdir -p /opt/lib/vemc2
	chown 1000:1000 /opt/lib/vemc2
	echo "/opt/lib/vemc2" > /etc/ld.so.conf.d/vemc2.conf

install:
	cp libvcore.so /opt/lib/vemc2/
	mv /opt/lib/vemc2/libvcore.so /opt/lib/vemc2/libvcore.so.`cat version`
	ln -fs /opt/lib/vemc2/libvcore.so.`cat version`              /opt/lib/vemc2/libvcore.so.`cat version | head -c 3`
	ln -fs /opt/lib/vemc2/libvcore.so.`cat version | head -c 3`  /opt/lib/vemc2/libvcore.so.`cat version | head -c 1`
	ln -fs /opt/lib/vemc2/libvcore.so.`cat version | head -c 1`  /opt/lib/vemc2/libvcore.so

install-local:
	sudo echo "$pwd" > /etc/ld.so.conf.d/vemc2.conf
	
	ln -fs libvcore.so.`cat version`             libvcore.so.0.0`cat version | head -c 3`
	ln -fs libvcore.so.`cat version | head -c 3` libvcore.so.0`cat version | head -c 1`
	ln -fs libvcore.so.`cat version | head -c 1` libvcore.so

uninstall:
	rm -f  /etc/ld.so.conf.d/vemc2.conf
	rm -rf /opt/lib/vemc2

#not anymore ... we will make this opensource ...
#release:
#	mkdir -p temp

libvcore.so: temp/object.o
	mkdir -p temp
	$(CC) -g -shared Wl,-soname,libvcore.so.`cat version` -o libvcore.so.`cat version` \
	temp/object.o temp/eld.o temp/noobject.o

temp/object.o: object/object.cpp object/object.h
	$(CC) $(CFLAGS) object/object.cpp    -o temp/object.o
temp/eld.o: mymath/eld.cpp mymath/eld.h
	$(CC) $(CFLAGS) mymath/eld.cpp       -o temp/eld.o
temp/noobject.o: object/noobject.cpp object/noobject.h
	$(CC) $(CFLAGS) object/noobject.cpp  -o temp/noobject.o


#Header files please:
myMath.h: mymath/eld.h
mymath/eld.h:
object/drawable.h:
object/object.h: object/drawable.h define.h
object/body.h: object/object.h
object/noobject.h:
define.h:
