#include "./effectthread.h"

#include <iostream>
#include <unistd.h>

///TODO: put this 256 into a settings namespace or into some header file!!
#define MAXEFFPERTHREAD 256

using namespace vemc2::simulation;

effectthread::effectthread():
    thread(effectthread::static_run, this)
    {

    effectToRun = new effect*[MAXEFFPERTHREAD];

    for (int i=0; i<MAXEFFPERTHREAD; i++)
        effectToRun[i] = 0;

    singleEffectToRun = 0;

    running     = false;
    effectCount = 0;
    only_one    = true;
    locker.lock();
}

effectthread::effectthread(vemc2::simulation::effect *singleEffectToRunts):
    thread(effectthread::static_run, this)
    {
    singleEffectToRun = singleEffectToRunts;

    effectToRun = 0;

    running     = false;
    effectCount = 1;
    only_one    = true;
    locker.lock();
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

    //wait for constructor to set running=0
    sleep(1);

    std::cout << "Sucessfully started thread with ID " << this->get_id() << std::endl;
    while (true){
        if (running == false)
            sleep(1);         //don't use too much CPU
        if (running == true){
            //we are now taking this serious now
            std::cout << "Thread with ID " << this->get_id() << " is taking this serious now!"<< std::endl;

            //decide between running one or two effects
            //we do this now (with too much obvious code)
            //to get a better performance
            if (only_one == true){
                while (running == true){
                    //--> use full power
                    locker.lock(); //wait for tick
                    singleEffectToRun->tick();
                    locker.unlock(); //we are done for this tick!

                    locker.lock(); //wait for upValues
                    singleEffectToRun->upValues();
                    locker.unlock(); //we are done for this tick!
                }
            }
            else{ //not only_one --> more than one thread
                while (running == true){
                    //--> use full power
                    locker.lock(); //wait for tick
                    for (int i=0; effectToRun[i] != 0; i++)
                        effectToRun[i]->tick();
                    locker.unlock(); //we are done for this tick!

                    locker.lock(); //wait for upValues
                    for (int i=0; effectToRun[i] != 0; i++)
                        effectToRun[i]->upValues();
                    locker.unlock(); //we are done for this tick!
                }
            }
        }

    }
}

void effectthread::stop(){
    running = false;
}

void effectthread::static_run(effectthread *toRun){
    toRun->run();
}
