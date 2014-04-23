#include "./noobject.h"

using namespace vemc2::simulation;

noobject::noobject(){
	active = false;
}

noobject::~noobject(){
	// dtor
}

void noobject::setActive(bool activets){
	active = activets;
}

bool noobject::isActive(){
	return active;
}

void noobject::draw(){
	if (active){
		//
	}
}

