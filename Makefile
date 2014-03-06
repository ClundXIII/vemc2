#Makefile for vemc2 (c) by Simon Michalke
#this is the overall Makefile


install-libs-local:
	make -C core install-local

install-libs:
	make -C core install
