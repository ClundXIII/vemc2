#ifndef SIM_THREAD_H_INCLUDED
#define SIM_THREAD_H_INCLUDED

#include <thread>

namespace vemc2{

class universe;

namespace simulation{

class effectthread;

class sim_thread : public std::thread{

    public:

        sim_thread(vemc2::universe *globUniversets);
        ~sim_thread();

        //void start();

        void run();

        void pause();

        void unpause();

        void stop();

    protected:


        vemc2::universe *globUniverse;

        static void static_run(sim_thread *toRun);

        vemc2::simulation::effectthread **paraThreads;

    private:

        bool paused;
        bool running;

};

}; /* namespace simulation */
}; /* namespace vemc2 */

#endif /* SIM_THREAD_H_INCLUDED */
