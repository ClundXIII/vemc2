#Makefile for vemc2 (c) by Simon Michalke
#this is the libcore Makefile, so we only get a .so

#vesper-dir=/media/simon/simondss/42vesper/fork
vesper-dir=$(HOME)/vesper-libs-fork
cmake-build-path=/bin

CC=g++
#CFLAGS=-I$(vesper-dir) -std=c++0x -fPIC -c -O3#optimized
CFLAGS=-I$(vesper-dir) -std=c++0x -fPIC -c -Wall -g #debugging
LDFLAGS=-pthread -Wl,-rpath=$(vesper-dir)$(cmake-build-path)/bin -l:libvesper-log.so

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
	mkdir -p /opt/lib/vemc2
	touch /opt/lib/vemc2/dummy
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
	     temp/effect.o temp/Gfield.o temp/Efield.o temp/sim_thread.o temp/effectthread.o temp/body.o temp/gravitation.o temp/vector.o
	mkdir -p temp
	cp $(vesper-dir)$(cmake-build-path)/lib*.so ./
	$(CC) -g -shared -Wl,-soname,libvcore.so.`cat version | head -c 1` -o libvcore.so.`cat version` \
	temp/object.o temp/eld.o temp/noobject.o temp/field.o temp/quant.o temp/universe.o temp/drawable.o temp/settings.o temp/ccs.o temp/inertia.o \
	temp/effect.o temp/Gfield.o temp/Efield.o temp/sim_thread.o temp/effectthread.o temp/body.o temp/gravitation.o temp/vector.o \
	$(LDFLAGS)

temp/object.o: object/object.cpp object/object.h
	$(CC) $(CFLAGS) object/object.cpp            -o temp/object.o
temp/body.o: object/body.cpp object/body.h
	$(CC) $(CFLAGS) object/body.cpp              -o temp/body.o
temp/eld.o: mymath/eld.cpp mymath/eld.h
	$(CC) $(CFLAGS) mymath/eld.cpp               -o temp/eld.o
temp/noobject.o: object/noobject.cpp object/noobject.h
	$(CC) $(CFLAGS) object/noobject.cpp          -o temp/noobject.o
temp/field.o: field/field.cpp field/field.h
	$(CC) $(CFLAGS) field/field.cpp              -o temp/field.o
temp/quant.o: object/quant.cpp object/quant.h
	$(CC) $(CFLAGS) object/quant.cpp             -o temp/quant.o
temp/universe.o: universe.cpp universe.h
	$(CC) $(CFLAGS) universe.cpp                 -o temp/universe.o
temp/drawable.o: object/drawable.cpp object/drawable.h
	$(CC) $(CFLAGS) object/drawable.cpp          -o temp/drawable.o
temp/settings.o: settings/settings.cpp settings/settings.h settings/settingdefines.h
	$(CC) $(CFLAGS) settings/settings.cpp        -o temp/settings.o
temp/ccs.o: settings/ccs.cpp settings/settings.h settings/settingdefines.h
	$(CC) $(CFLAGS) settings/ccs.cpp             -o temp/ccs.o
temp/inertia.o: effect/inertia.cpp effect/inertia.h universe.h mymath/math_struct.h
	$(CC) $(CFLAGS) effect/inertia.cpp           -o temp/inertia.o
temp/effect.o: effect/effect.cpp effect/effect.h
	$(CC) $(CFLAGS) effect/effect.cpp            -o temp/effect.o
temp/Gfield.o: field/Gfield.cpp field/Gfield.h
	$(CC) $(CFLAGS) field/Gfield.cpp             -o temp/Gfield.o
temp/Efield.o: field/Efield.cpp field/Efield.h
	$(CC) $(CFLAGS) field/Efield.cpp             -o temp/Efield.o
temp/sim_thread.o: simulation/sim_thread.cpp simulation/sim_thread.h universe.h simulation/effectthread.h
	$(CC) $(CFLAGS) simulation/sim_thread.cpp    -o temp/sim_thread.o
temp/effectthread.o: simulation/effectthread.cpp simulation/effectthread.h
	$(CC) $(CFLAGS) simulation/effectthread.cpp  -o temp/effectthread.o
temp/gravitation.o: effect/gravitation.cpp effect/gravitation.h
	$(CC) $(CFLAGS) effect/gravitation.cpp       -o temp/gravitation.o
temp/vector.o: mymath/vector.cpp mymath/vector.h myMath.h
	$(CC) $(CFLAGS) mymath/vector.cpp             -o temp/vector.o

#Header files please:
copy-header:
	cp myMath.h                      ./../header/core/myMath.h
	cp mymath/eld.h                  ./../header/core/mymath/eld.h
	cp mymath/math_struct.h          ./../header/core/mymath/math_struct.h
	cp object/drawable.h             ./../header/core/object/drawable.h
	cp object/object.h               ./../header/core/object/object.h
	cp object/body.h                 ./../header/core/object/body.h
	cp object/noobject.h             ./../header/core/object/noobject.h
	cp object/quant.h                ./../header/core/object/quant.h
	cp field/field.h                 ./../header/core/field/field.h
	cp field/Gfield.h                ./../header/core/field/Gfield.h
	cp field/Efield.h                ./../header/core/field/Efield.h
	cp universe.h                    ./../header/core/universe.h
	cp effect/effect.h               ./../header/core/effect/effect.h
	cp effect/inertia.h              ./../header/core/effect/inertia.h
	cp effect/gravitation.h          ./../header/core/effect/gravitation.h
	cp settings/settings.h           ./../header/core/settings/settings.h
	cp settings/settingdefines.h     ./../header/core/settings/settingdefines.h
	cp simulation/sim_thread.h       ./../header/core/simulation/sim_thread.h
	cp simulation/effectthread.h     ./../header/core/simulation/effectthread.h
	cp simulation.h                  ./../header/core/simulation.h
	cp define.h                      ./../header/core/define.h


myMath.h:
	@#cp myMath.h                      ./../header/core/myMath.h
mymath/eld.h: define.h myMath.h
	@#@mkdir -p ./../header/core/mymath
	@#cp mymath/eld.h                  ./../header/core/mymath/eld.h
mymath/math_struct.h: myMath.h mymath/eld.h
	@#@mkdir -p ./../header/core/mymath
	@#cp mymath/math_struct.h          ./../header/core/mymath/math_struct.h
mamath/vector.h: myMath.h

object/drawable.h: define.h
	@#@mkdir -p ./../header/core/object
	@#cp object/drawable.h             ./../header/core/object/drawable.h
object/object.h: object/drawable.h define.h myMath.h
	@#@mkdir -p ./../header/core/object
	@#cp object/object.h               ./../header/core/object/object.h
object/body.h: object/object.h define.h
	@#@mkdir -p ./../header/core/object
	@#cp object/body.h                 ./../header/core/object/body.h
object/noobject.h: object/drawable.h
	@#@mkdir -p ./../header/core/object
	@#cp object/noobject.h             ./../header/core/object/noobject.h
object/quant.h: object/object.h
	@#@mkdir -p ./../header/core/object
	@#cp object/quant.h                ./../header/core/object/quant.h

field/field.h: object/drawable.h effect/effect.h
	@#@mkdir -p ./../header/core/field
	@#cp field/field.h                 ./../header/core/field/field.h
field/Gfield.h: field/field.h
	@#@mkdir -p ./../header/core/field
	@#cp field/Gfield.h                ./../header/core/field/Gfield.h
field/Efield.h: field/field.h
	@#@mkdir -p ./../header/core/field
	@#cp field/Efield.h                ./../header/core/field/Efield.h

universe.h: simulation.h settings/settings.h
	@#cp universe.h                    ./../header/core/universe.h

effect/effect.h:
	@#@mkdir -p ./../header/core/effect
	@#cp effect/effect.h               ./../header/core/effect/effect.h
effect/inertia.h: effect/effect.h
	@#@mkdir -p ./../header/core/effect
	@#cp effect/inertia.h              ./../header/core/effect/inertia.h
effect/gravitation.h: effect/effect.h
	@#@mkdir -p ./../header/core/effect
	@#cp effect/gravitation.h          ./../header/core/effect/gravitation.h

settings/settings.h: define.h myMath.h
	@#@mkdir -p ./../header/core/settings
	@#cp settings/settings.h           ./../header/core/settings/settings.h
settings/settingdefines.h:
	@#@mkdir -p ./../header/core/settings
	@#cp settings/settingdefines.h     ./../header/core/settings/settingdefines.h

simulation/sim_thread.h:
	@#@mkdir -p ./../header/core/simulation
	@#cp simulation/sim_thread.h       ./../header/core/simulation/sim_thread.h
simulation/effectthread.h: effect/effect.h
	@#@mkdir -p ./../header/core/simulation
	@#cp simulation/effectthread.h     ./../header/core/simulation/effectthread.h

simulation.h:mymath/math_struct.h effect/effect.h effect/inertia.h object/object.h object/noobject.h object/body.h object/quant.h field/field.h
	@#cp simulation.h                  ./../header/core/simulation.h
define.h:
	@#cp define.h                      ./../header/core/define.h

