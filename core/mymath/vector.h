#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <vector>
//#include "./../mymath/vec3bdt.h"
#include "./../myMath.h"

namespace vemc2{
namespace mymath{

template <class T>
class vector : public ::std::vector<T>{

    public:
        vector();
        vector(int i); //Count of elements
        vector(T x1, T x2, T x3);

        static std::vector<T> addTwo(std::vector<T> vec1,  std::vector<T> vec2);

        //null vector. May be useful --> mv'ed to vec3bdt class
        //static const std::vector<bdt> null;

        //void invert();

        //does not change the vector
        vector normalize();
        T      getLength();

        //returns the invert
        static vector invert(std::vector<T> toInv);

        //changes this vector
        void mul(bdt toMul);

        //changes this vector
        template <class S>
        void add(std::vector<S> toAdd);

        //these are not changing this vector
        vector operator*(bdt toMul);
        vector operator/(bdt toDiv);
        vector operator+(std::vector<T> toAdd);
        vector operator-(std::vector<T> toSub);


        //changes this vector obviously
        vector set(std::vector<T> toSet);
        vector operator=(std::vector<T> toSet);

    protected:
        //returns this*toMul; does not change this vector
        vector multiplicateTo(bdt toMul);
        //returns this+toAdd; does not change this vector
        vector additionTo(std::vector<T> toAdd);

    private:

    /* specializing */

    public:

};


//template class vector<long double>;

/*template <class T>
class vector;*/

}; /* namespace mymath */
}; /* namespace vecm2 */

#endif // VECTOR_H_INCLUDED
