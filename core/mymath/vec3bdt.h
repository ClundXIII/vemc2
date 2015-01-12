#ifndef VEC3BDT_H_INCLUDED
#define VEC3BDT_H_INCLUDED

#include "vector.h"

namespace vemc2{
namespace mymath{

class vec3bdt : public vector<bdt>{

    public:

        vec3bdt();
        vec3bdt(bdt x1, bdt x2, bdt x3);
        //null is located in vector.cpp
        static std::vector<bdt> null;


        //these are not changing this vector
        std::vector<bdt> operator*(bdt toMul);
        std::vector<bdt> operator/(bdt toDiv);
        std::vector<bdt> operator+(std::vector<bdt> toAdd);
        std::vector<bdt> operator-(std::vector<bdt> toSub);


        //changes this vector obviously
        std::vector<bdt> operator=(std::vector<bdt> toSet);

    protected:
    private:

};

}; /* namespace mymath */
}; /* namespace vecm2 */

#endif /* VEC3BDT_H_INCLUDED */
