#include "drawable.h"

using namespace vemc2::simulation;

drawable::drawable(){
}

drawable::~drawable(){
    //dtor
}

void drawable::draw(){
}

void drawable::setActive(bool activets){
    active = activets;
}

bool drawable::isActive(){
     return active;
}
