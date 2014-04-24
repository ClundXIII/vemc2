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
         * We don't declare any contructors / destructors so the
         * compiler doesn't search for them ;-)
         */
        //effect();
        //~effect();

        /**
         * This function is being called by the simulation thread.
         * The effects should save the changes theirselves to
         * apply them in the upValues() function.
         */
        virtual void tick();

        /**
         * This function applies the changes / effects / etc
         * which were calculated by the tick() function before.
         */
        virtual void upValues();

    protected:

        vemc2::universe *globUniverse;

    private:
        //

};

}; /* namespace simulation */
}; /* namespace vemc2 */

#endif /* EFFECT_H_INCLUDED */
