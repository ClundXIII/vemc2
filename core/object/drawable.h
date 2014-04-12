#ifndef DRAWABLE_H
#define DRAWABLE_H

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
 *  └─noobject  //something, that is not simulated
 *
 * You can't create an object of this class,
 * because this hasn't got any source file.
 * If you want to have anything that doesn't
 * affect the simulation, use simulation::noobject
 * instead!
 *
 * @author Simon Michalke
 * @version 0.9
 *
 */

class drawable{
    public:
        drawable();
        ~drawable();

        virtual void draw();

    protected:
    private:

};

} /* namespace simulation */
} /* namespace vemc2 */

#endif // DRAWABLE_H
