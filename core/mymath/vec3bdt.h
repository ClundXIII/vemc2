#ifndef VEC3BDT_H_INCLUDED
#define VEC3BDT_H_INCLUDED

#include "./vector.h"

namespace vemc2{
namespace mymath{

//template <class T>
class vec3bdt : public ::vemc2::mymath::vector<bdt> {

    public:

        vec3bdt();
        vec3bdt(bdt x1, bdt x2, bdt x3);

        static std::vector<bdt> null;
        static vec3bdt to3Bdt(std::vector<bdt> toConvert);

        //these are not changing this vector
        vec3bdt operator*(bdt toMul);
        vec3bdt operator/(bdt toDiv);
        vec3bdt operator+(std::vector<bdt> toAdd);
        vec3bdt operator-(std::vector<bdt> toSub);


        //changes this vector obviously
        vec3bdt operator=(std::vector<bdt> toSet);

    protected:
    private:

};

}; /* namespace mymath */
}; /* namespace vecm2 */

#endif /* VEC3BDT_H_INCLUDED */
