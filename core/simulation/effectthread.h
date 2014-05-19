#ifndef EFFECTTHREAD_H_INCLUDED
#define EFFECTTHREAD_H_INCLUDED

#include <thread>

#include "./../effect/effect.h"

namespace vemc2{

namespace simulation{

//class effect;

class effectthread : public std::thread{

    public:

        /**
         * use default constructor only if multiple effects are
         * binded to one effectthread
         */
        effectthread();

        /**
         * use this if the thread holds only one effect!
         */
        effectthread(vemc2::simulation::effect *singleEffectToRunts);

        ~effectthread();

        /**
         * this only works when the default constructor is used
         * if not, an (char*) exeption is thrown!
         */
        void insertEffect(vemc2::simulation::effect *effectToRunts);

        void run();

        void stop();

        std::mutex locker;

    protected:


        vemc2::simulation::effect **effectToRun;
        vemc2::simulation::effect  *singleEffectToRun;

        static void static_run(effectthread *toRun);

    private:

        int effectCount;

        /**
         * This is true if
         * effectthread(vemc2::simulation::effect *effectToRunts);
         * is invoked!
         * (for performance)
         */
        bool only_one;

        bool running;

};

}; /* namespace simulation */
}; /* namespace vemc2 */

#endif /* EFFECTTHREAD_H_INCLUDED */
