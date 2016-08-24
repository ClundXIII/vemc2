#include "sim_thread.h"

#include <iostream>
#include <thread>
#include <unistd.h>

#include "./../universe.h"
#include "./effectthread.h"
#include "../effect/gravitation.h"
#include "../field/Gfield.h"

using namespace vemc2::simulation;
using namespace Vesper::LoggingTypes;

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

    try {
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
    catch (...){
        globUniverse->out << "Exception while starting Simulation Thread." << eom;
    }
}

void sim_thread::run(){

    try {

        ///TODO this doesnt work ... make more!!

        globUniverse->out << "<--- data begin-->" << eom;
        globUniverse->out << "time is   :" << globUniverse->settings.sim.global_time << eom;
        globUniverse->out << "dt is     :" << globUniverse->settings.sim.dt << eom;
        globUniverse->out << "stopping @:" << time_to_stop << eom;
        globUniverse->out << "effect   #:" << globUniverse->effectCount << eom;
        globUniverse->out << "<--- data end-->" << eom;
        running = true;

        if (!globUniverse->effectArray)
            throw (char*)"effectArray equals 0 in sim_thread.cpp::run()";

        for (int i=0; i<globUniverse->effectCount; i++)
            if (!globUniverse->effectArray[i])
                throw (char*) "effectArray[i] is 0 in sim_thread.cpp::run()";

        globUniverse->out << "         ... and go!" << eom;
        for (int i=0; (globUniverse->objectArray[i] != 0) && (i<globUniverse->objectCount); i++){
            globUniverse->out << i << ":x:" << globUniverse->objectArray[i]->getX1() << " " << globUniverse->objectArray[i]->getX2() << " " << globUniverse->objectArray[i]->getX3() << eom;
            globUniverse->out << i << ":v:" << globUniverse->objectArray[i]->data.v.X1 << " " << globUniverse->objectArray[i]->data.v.X2 << " " << globUniverse->objectArray[i]->data.v.X3 << eom;
        }

        if (globUniverse->settings.sim_thread.useParaProc){
            while (running){
                //tick the parallel things
                //up() the parallel things
            }
        }
        else{ //not parallel
            while (running){

                if (globUniverse->invokedFuncBefore)
                    globUniverse->invokeBeforeSim();

                for (int i=0; i<globUniverse->effectCount; i++)
                    globUniverse->effectArray[i]->tick();

                if (globUniverse->invokedFuncMiddle)
                    globUniverse->invokeMiddleSim();

                for (int i=0; i<globUniverse->effectCount; i++)
                    globUniverse->effectArray[i]->upValues();


                if (globUniverse->invokedFuncAfter)
                    globUniverse->invokeAfterSim();

                if (paused){
                    while (paused){ //wait for paused to get false
                        sleep(1);
                    }
                    //when we reach this point, we are unpaused!
                    globUniverse->out << "Sim>SimulationThread unpaused!" << eom;
                }

                globUniverse->settings.sim.global_time += globUniverse->settings.sim.dt;
                if ((time_to_stop>0)&&(globUniverse->settings.sim.global_time >= time_to_stop))
                    running = false;
            }
        }

        globUniverse->out << "End data: " << eom;
        for (int i=0; globUniverse->objectArray[i] != 0; i++){
            globUniverse->out << i << ":x:" << globUniverse->objectArray[i]->getX1() << " " << globUniverse->objectArray[i]->getX2() << " " << globUniverse->objectArray[i]->getX3() << eom;
            globUniverse->out << i << ":v:" << globUniverse->objectArray[i]->data.v.X1 << " " << globUniverse->objectArray[i]->data.v.X2 << " " << globUniverse->objectArray[i]->data.v.X3 << eom;
        }
    }
    catch (char *error_msg){

        globUniverse->out << "Simulation encountered an Error: \"" << \
                            error_msg << "\"" <<\
                            Vesper::LoggingTypes::eom;
    }
    catch (char const* error_msg){

        globUniverse->out << "Simulation encountered an Error: \"" << \
                            error_msg << "\"" <<\
                            Vesper::LoggingTypes::eom;
    }
    catch (...) {
        globUniverse->out << "Simulation encountered and unknown exception!" << eom;
    }
    globUniverse->out << "Simulation stopped!" << eom;
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
