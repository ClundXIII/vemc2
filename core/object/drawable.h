#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

#include "./../define.h"

namespace vemc2{
namespace simulation{

/**
 * This is the mother class of all
 * things that will appear on the screen
 * classes, that extend vemc2::simulation::drawable:
 * ─drawable    //mother
 *  ├─object    //everything that is being simulated
 *  │ ├─body    //planets and other bigger stuff
 *  │ └─quant   //quant objects
 *  ├─field     //fields that can be drawn (active or non-active)
 *  └─noobject  //something, that is not simulated (active or non-active)
 *
 * @author Simon Michalke
 * @version 0.0.01
 *
 */

class drawable{
    public:

        drawable();
        ~drawable();

		void setActive(bool activets);
		bool isActive();

        virtual void draw()=0;

    protected:

		bool active;

    private:

};

} /* namespace simulation */
} /* namespace vemc2 */

#endif // DRAWABLE_H_INCLUDED
