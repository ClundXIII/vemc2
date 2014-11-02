#ifndef GFIELD_H_INCLUDED
#define GFIELD_H_INCLUDED

#include "./../effect/effect.h"

#include <vector>

using namespace vemc2::simulation;

namespace vemc2{
namespace simulation{

class Efield : field {
    public:

        Efield(vemc2::universe *globUniversets);
        ~Efield();

        static void setDeadZone(bdt Zonets);

        std::vector<bdt> getVecA(bdt posX, bdt posY, bdt posZ, bdt mass);

    protected:
    private:

        static bdt DeadZone; // = 0.1;

};

}; /* namespace simulation */
}; /* namespace vemc2 */

#endif // GFIELD_H_INCLUDED
