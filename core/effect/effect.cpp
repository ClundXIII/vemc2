#include "effect.h"
#include "./../universe.h"

using namespace vemc2::simulation;

effect::effect(vemc2::universe *globUniversets){
    globUniverse = globUniversets;

    priority = 50;
    prioIsSet = false;
}

effect::~effect(){
}

void effect::tick(){}
void effect::upValues(){}

int effect::getPriority(){
    return priority;
}

void effect::setPriority(int pToSet){

    if (prioIsSet){
        globUniverse->out << "cannot re-set priority" << Vesper::LoggingTypes::eom;
        return;
    }

    prioIsSet = true;

    priority = pToSet;
}
