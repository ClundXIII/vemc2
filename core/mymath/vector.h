#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <vector>
#include "./../myMath.h"

namespace vemc2{
namespace mymath{

template <class T>
class vector : public std::vector<T>{

    public:
        vector<T>();
        vector<T>(int i); //Count of elements
        vector<T>(T x1, T x2, T x3);

        static std::vector<T> addTwo(std::vector<T> vec1,  std::vector<T> vec2);

        //null vector. May be useful
        static const std::vector<bdt> null;

        void invert();

        //returns the invert
        template <class S>
        static std::vector<T> invert(std::vector<S> toInv);

        //changes this vector
        void mul(bdt toMul);

        //changes this vector
        template <class S>
        void add(std::vector<S> toAdd);

        //these are not changing this vector
        std::vector<T> operator*(bdt toMul);
        std::vector<T> operator/(bdt toDiv);
        std::vector<T> operator+(std::vector<T> toAdd);
        std::vector<T> operator-(std::vector<T> toSub);

        //changes this vector obviously
        std::vector<T> operator=(std::vector<T> toSet);

    protected:
    private:

        //returns this*toMul; does not change this vector
        std::vector<T> multiplicateTo(bdt toMul);
        //returns this+toAdd; does not change this vector
        std::vector<T> additionTo(std::vector<T> toAdd);

};

}; /* namespace mymath */
}; /* namespace vecm2 */

#endif // VECTOR_H_INCLUDED
