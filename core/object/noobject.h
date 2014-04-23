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
 * @version 0.9
 *
 */

class noobject : drawable{
    public:
        noobject();
        ~noobject();

		void setActive(bool activets);
		bool isActive();
		
        void draw();

    protected:
    private:
	
		bool active;

};

} /* namespace simulation */
} /* namespace vemc2 */


#endif // NOOBJECT_H_INCLUDED
