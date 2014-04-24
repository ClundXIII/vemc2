#ifndef NOOBJECT_H_INCLUDED
#define NOOBJECT_H_INCLUDED

#include "drawable.h"


namespace vemc2{
namespace simulation{

/**
 * This is not an object that takes
 * part in the simulation
 * this will just be drawn by the graphics
 * to visulize something
 *
 * @author Simon Michalke
 * @version 0.0.01
 *
 */

class noobject : drawable{
    public:
        noobject();
        ~noobject();

        void draw();

    protected:
    private:

};

} /* namespace simulation */
} /* namespace vemc2 */


#endif // NOOBJECT_H_INCLUDED
