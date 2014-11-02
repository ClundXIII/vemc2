#include "effect.h"

using namespace vemc2::simulation;

effect::effect(vemc2::universe *globUniversets){
    globUniverse = globUniversets;
}

effect::~effect(){
}

void effect::tick(){}
void effect::upValues(){}
