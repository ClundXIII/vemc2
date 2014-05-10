#ifndef SIM_THREAD_H_INCLUDED
#define SIM_THREAD_H_INCLUDED

#include <thread>

namespace vemc2{
namespace simulation{

class universe;

class sim_thread : public std::thread{

    public:

        sim_thread(vemc2::simulation::universe *globUniversets);
        ~sim_thread();

        void run();

    protected:


        vemc2::simulation::universe *globUniverse;

        static void static_run(sim_thread *toRun);

    private:

};

}; /* namespace simulation */
}; /* namespace vemc2 */

#endif /* SIM_THREAD_H_INCLUDED */
