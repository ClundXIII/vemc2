#include "./effectthread.h"

///TODO: put this 256 into a settings namespace or into some header file!!
#define MAXEFFPERTHREAD 256

using namespace vemc2::simulation;

effectthread::effectthread(){

    effectToRun = new effect*[MAXEFFPERTHREAD];

    for (int i=0; i<MAXEFFPERTHREAD; i++)
        effectToRun[i] = 0;

    singleEffectToRun = 0;

    running     = false;
    effectCount = 0;
    only_one    = true;
}

effectthread::effectthread(vemc2::simulation::effect *singleEffectToRunts){
    singleEffectToRun = singleEffectToRunts;

    effectToRun = 0;

    running     = false;
    effectCount = 1;
    only_one    = true;
}

effectthread::~effectthread(){

    //we are not deleting the effects itselves ... just the array!
    if (!only_one)
        delete effectToRun;
}

void effectthread::insertEffect(vemc2::simulation::effect *effectToRunts){
    if (only_one)
        throw (char*) "unexspected calling of effectthread.cpp::insertEffec()!";

    if (effectCount >= MAXEFFPERTHREAD)
        throw (char*) "MAXEFFPERTHREAD reached in effectthread.cpp::insertEffec()!";

    effectToRun[effectCount] = effectToRunts;
    effectCount++;
}

void effectthread::run(){
}

void effectthread::stop(){
    running = false;
}

void effectthread::static_run(effectthread *toRun){
    toRun->run();
}
