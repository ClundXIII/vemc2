#include "sim_thread.h"

#include <iostream>
#include <thread>

#include "./../universe.h"

using namespace vemc2::simulation;

sim_thread::sim_thread(vemc2::simulation::universe *globUniversets)
    :
    thread(sim_thread::static_run, this)
    {
    globUniverse = globUniversets;
}

sim_thread::~sim_thread(){
    //dtor
}

void sim_thread::run(){
}

void sim_thread::static_run(sim_thread *toRun){
    toRun->run();
}
