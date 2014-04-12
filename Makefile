#Makefile for vemc2 (c) by Simon Michalke
#this is the overall Makefile

compile-all:

init-all:
	make -C core preinst
	make -C core install

install-libs-local:
	make -C core install-local

install-libs:
	make -C core install

release:
	make -C core release
