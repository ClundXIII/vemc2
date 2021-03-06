#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED

#include "./../object/object.h"

/**
 * This is the mother class of all effects.
 *
 *
 *
 * @author Simon Michalke
 * @version 0.0.01
 */

namespace vemc2{

class universe;

namespace simulation{

class effect{

    public:

        /**
         *
         */
        effect(vemc2::universe *globUniversets);
        virtual ~effect();

        /**
         * This function is being called by the simulation thread.
         * The effects should save the changes themselves to
         * apply them in the upValues() function.
         */
        virtual void tick(); // =0;

        /**
         * This function applies the changes / effects / etc
         * which were calculated by the tick() function before.
         */
        virtual void upValues(); //  =0;

        int getPriority();

    protected:

        /**
         * This is a pointer to the universe the effect belongs to.
         */
        vemc2::universe *globUniverse;

        void setPriority(int pToSet);

    private:

        int priority;
        bool prioIsSet;

};

}; /* namespace simulation */
}; /* namespace vemc2 */

#endif /* EFFECT_H_INCLUDED */
