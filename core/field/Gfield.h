#ifndef GFIELD_H_INCLUDED
#define GFIELD_H_INCLUDED

#include "./../effect/effect.h"
#include "./field.h"
#include "./../mymath/vec3bdt.h"

//#include <vector>

using namespace vemc2::simulation;

namespace vemc2{
namespace simulation{

class Gfield : field {
    public:

        Gfield(vemc2::universe *globUniversets);
        ~Gfield();

        //static void setDeadZone(bdt *Zonets);

        //virtual void draw();

        vemc2::mymath::vec3bdt getVecA(bdt posX1, bdt posX2, bdt posX3, bdt mass);
        bdt*             getVecA_array(bdt posX1, bdt posX2, bdt posX3, bdt mass);
        vemc2::mymath::vec3bdt getVecA(vemc2::mymath::vec3bdt posX, bdt mass);

    protected:
    private:

        bdt *DeadZone; // = 0.1;

};

}; /* namespace simulation */
}; /* namespace vemc2 */

#endif // GFIELD_H_INCLUDED
