#Makefile for vemc2 (c) by Simon Michalke
#this is the libcore Makefile, so we only get a .so

CC=g++
#CFLAGS=-std=c++0x -fPIC -c -O3#optimized
CFLAGS=-std=c++0x -fPIC -c -Wall -g #debugging
LDFLAGS=-pthread

all: libvcore.so

clean:
	@touch temp/dummy
	rm temp/* 

preinst:
	mkdir -p /opt/lib
	mkdir -p /opt/lib/vemc2
	echo "/opt/lib/vemc2" > /etc/ld.so.conf.d/vemc2.conf

install:
	sudo echo "/opt/lib/vemc2/" > /etc/ld.so.conf.d/vemc2.conf
	@echo "cleaning up lib dir ..."
	rm /opt/lib/vemc2/*
	cp libvcore.so.`cat version` /opt/lib/vemc2/
	ln -fs /opt/lib/vemc2/libvcore.so.`cat version`              /opt/lib/vemc2/libvcore.so.`cat version | head -c 3`
	ln -fs /opt/lib/vemc2/libvcore.so.`cat version | head -c 3`  /opt/lib/vemc2/libvcore.so.`cat version | head -c 1`
	ln -fs /opt/lib/vemc2/libvcore.so.`cat version | head -c 1`  /opt/lib/vemc2/libvcore.so
	chmod +r /opt/lib/vemc2/*
	chmod +x /opt/lib/vemc2/*
	@#ldconfig -v | grep vcore

install-local:
	sudo echo "$pwd" > /etc/ld.so.conf.d/vemc2.conf
	
	ln -fs libvcore.so.`cat version`             libvcore.so`cat version | head -c 3`
	ln -fs libvcore.so.`cat version | head -c 3` libvcore.so`cat version | head -c 1`
	ln -fs libvcore.so.`cat version | head -c 1` libvcore.so

uninstall:
	rm -f  /etc/ld.so.conf.d/vemc2.conf
	rm -rf /opt/lib/vemc2

#not anymore ... we will make this opensource ...
#release:
#	mkdir -p temp

libvcore.so: temp/object.o temp/eld.o temp/noobject.o temp/field.o temp/quant.o temp/universe.o temp/drawable.o temp/settings.o temp/ccs.o temp/inertia.o \
	     temp/effect.o temp/Gfield.o temp/Efield.o temp/sim_thread.o
	mkdir -p temp
	$(CC) -g -shared -Wl,-soname,libvcore.so.`cat version | head -c 1` -o libvcore.so.`cat version` \
	temp/object.o temp/eld.o temp/noobject.o temp/field.o temp/quant.o temp/universe.o temp/drawable.o temp/settings.o temp/ccs.o temp/inertia.o \
	temp/effect.o temp/Gfield.o temp/Efield.o temp/sim_thread.o \
	$(LDFLAGS)

temp/object.o: object/object.cpp object/object.h
	$(CC) $(CFLAGS) object/object.cpp      -o temp/object.o
temp/eld.o: mymath/eld.cpp mymath/eld.h
	$(CC) $(CFLAGS) mymath/eld.cpp         -o temp/eld.o
temp/noobject.o: object/noobject.cpp object/noobject.h
	$(CC) $(CFLAGS) object/noobject.cpp    -o temp/noobject.o
temp/field.o: field/field.cpp field/field.h
	$(CC) $(CFLAGS) field/field.cpp        -o temp/field.o
temp/quant.o: object/quant.cpp object/quant.h
	$(CC) $(CFLAGS) object/quant.cpp       -o temp/quant.o
temp/universe.o: universe.cpp universe.h
	$(CC) $(CFLAGS) universe.cpp           -o temp/universe.o
temp/drawable.o: object/drawable.cpp object/drawable.h
	$(CC) $(CFLAGS) object/drawable.cpp    -o temp/drawable.o
temp/settings.o: settings/settings.cpp settings/settings.h settings/settingdefines.h
	$(CC) $(CFLAGS) settings/settings.cpp  -o temp/settings.o
temp/ccs.o: settings/ccs.cpp settings/settings.h settings/settingdefines.h
	$(CC) $(CFLAGS) settings/ccs.cpp       -o temp/ccs.o
temp/inertia.o: effect/inertia.cpp effect/inertia.h universe.h mymath/math_struct.h
	$(CC) $(CFLAGS) effect/inertia.cpp     -o temp/inertia.o
temp/effect.o: effect/effect.cpp effect/effect.h
	$(CC) $(CFLAGS) effect/effect.cpp      -o temp/effect.o
temp/Gfield.o: field/Gfield.cpp field/Gfield.h
	$(CC) $(CFLAGS) field/Gfield.cpp       -o temp/Gfield.o
temp/Efield.o: field/Efield.cpp field/Efield.h
	$(CC) $(CFLAGS) field/Efield.cpp       -o temp/Efield.o
temp/sim_thread.o: simulation/sim_thread.cpp simulation/sim_thread.h
	$(CC) $(CFLAGS) simulation/sim_thread.cpp    -o temp/sim_thread.o

#Header files please:
myMath.h:
mymath/eld.h: define.h myMath.h
mymath/math_struct.h: myMath.h mymath/eld.h

object/drawable.h: define.h
object/object.h: object/drawable.h define.h myMath.h
object/body.h: object/object.h define.h
object/noobject.h: object/drawable.h
object/quant.h: object/object.h

field/field.h: object/drawable.h effect/effect.h
field/Gfield.h: field/field.h
field/Efield.h: field/field.h

universe.h: simulation.h settings/settings.h

effect/effect.h:
effect/inertia.h: effect/effect.h

settings/settings.h: define.h myMath.h
settings/settingdefines.h:

simulation/sim_thread.h:
simulation.h:mymath/math_struct.h effect/effect.h effect/inertia.h object/object.h object/noobject.h object/body.h object/quant.h field/field.h
define.h:

