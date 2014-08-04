#include "sim_thread.h"

#include <iostream>
#include <thread>
#include <unistd.h>

#include "./../universe.h"
#include "./effectthread.h"

using namespace vemc2::simulation;

sim_thread::sim_thread(vemc2::universe *globUniversets)
    :
    thread(sim_thread::static_run, this)
    {
    globUniverse = globUniversets;

    running = false;
    paused  = false;

    if (globUniverse->settings.sim_thread.useParaProc){
        //getting thread count
        int tCount = globUniverse->settings.sim_thread.countParaThreads;
        //getting effect count
        int eCount = globUniverse->effectCount;

        paraThreads = new effectthread*[tCount];

        //create the threads:
        for (int i=0; i<tCount; i++)
            paraThreads[i] = new effectthread(globUniverse->effectArray[i]);
        //fill in the threads with the effects:
        for (int i=0, j=0; i<eCount; i++){
            paraThreads[i] = new effectthread(globUniverse->effectArray[i]);

            if (j>=tCount) j=0; //starting at thread 0
        }
    }
    else
        paraThreads = 0;
}

sim_thread::~sim_thread(){
    //dtor
}

/*void sim_thread::start(){
    launch();
}*/

void sim_thread::run(){

    ///TODO this doesnt work ... make more!!

    running = true;

    if (globUniverse->settings.sim_thread.useParaProc){
        while (running){
            //tick the parallel things
            //up() the parallel things
        }
    }
    else{ //not parallel
        while (running){
            for (int i=0; i<globUniverse->effectCount; i++)
                globUniverse->effectArray[i]->tick();

            for (int i=0; i<globUniverse->effectCount; i++)
                globUniverse->effectArray[i]->upValues();
            if (paused){
                while (paused) //wait for paused to get false
                    sleep(1);
                //when we reach this point, we are unpaused!
                std::cout << "Sim>SimulationThread unpaused!" << std::endl;
            }
        }
    }

    std::cout << "Sim>Simulation stopped!" << std::endl;
}

void sim_thread::pause(){
    paused = true;
}

void sim_thread::unpause(){
    paused = false;
}

void sim_thread::stop(){
    running = false;
}

void sim_thread::static_run(sim_thread *toRun){
    toRun->run();
}
