#ifndef MATH_STRUCT_INCLUDED
#define MATH_STRUCT_INCLUDED

#include "eld.h"

///Define our constants we can use
namespace vemc2{
namespace simulation{class eld;};
namespace mymath{

    struct math_struct{

        vemc2::simulation::eld e;
        vemc2::simulation::eld h;
        vemc2::simulation::eld angstroem;

        struct{
            vemc2::simulation::eld m_p;
            vemc2::simulation::eld l_p;
            vemc2::simulation::eld t_p;
            vemc2::simulation::eld q_p;
            vemc2::simulation::eld T_p;
        }planck;
    };

};
}; /*namespace vemc2 */

#endif /* MATH_STRUCT_INCLUDED */
