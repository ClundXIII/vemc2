#include "sim_thread.h"

#include <iostream>
#include <thread>
#include <unistd.h>

#include "./../universe.h"
#include "./effectthread.h"

using namespace vemc2::simulation;

sim_thread::sim_thread(vemc2::universe *globUniversets)
    {
    globUniverse = globUniversets;

    running = false;
    paused  = true;
    tHelper = 0;

    if (globUniverse->settings.sim_thread.useParaProc){
        //not implemented yet
    }
    else
        paraThreads = 0;
}

sim_thread::~sim_thread(){
    running = false;
    paused = true;
    if (tHelper){
        sleep(1);
        delete tHelper;
        tHelper = 0;
    }
}

void sim_thread::start(){
    if (running) return;

    paused = true;

    if (tHelper){
        sleep(1);
        delete tHelper;
        tHelper = 0;
    }

    running = true;
    tHelper = new std::thread(sim_thread::static_run, this);
}

void sim_thread::run(){

    ///TODO this doesnt work ... make more!!

    sleep(1);
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
