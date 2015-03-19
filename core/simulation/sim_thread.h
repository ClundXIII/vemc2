#ifndef SIM_THREAD_H_INCLUDED
#define SIM_THREAD_H_INCLUDED

#include <thread>

namespace vemc2{

class universe;

namespace simulation{

class effectthread;

class sim_thread {

    public:

        sim_thread(vemc2::universe *globUniversets);
        ~sim_thread();

        //starts the threads
        void start();

        //pauses the threads
        void pause();

        //unpauses / continues the threads
        void unpause();

        //terminate all threads
        void stop();

        void run(); //this function simulates stuff.

    protected:


        vemc2::universe *globUniverse;

        static void static_run(sim_thread *toRun);

        vemc2::simulation::effectthread **paraThreads;


    private:

        bool paused;
        bool running;

        std::thread *tHelper;
};

}; /* namespace simulation */
}; /* namespace vemc2 */

#endif /* SIM_THREAD_H_INCLUDED */
