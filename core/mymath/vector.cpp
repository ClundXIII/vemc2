#include "vector.h"

using namespace vemc2;
using namespace vemc2::mymath;

template<class T>
vector<T>::vector(){
    std::vector<T>();
}

template<class T>
vector<T>::vector(int i){
    std::vector<T>()[i];
}

template<class T>
vector<T>::vector(T x1, T x2, T x3){
    std::vector<T>()[3];

    this[1] = x1;
    this[2] = x2;
    this[3] = x3;
}

template<class T>
//template<class T>
/*static */
std::vector<T> vector<T>::addTwo(std::vector<T> vec1,  std::vector<T> vec2){
    if (vec1.size() != vec2.size())
        throw (char*) "error: size not identical in vector.cpp::static_addTwo";

    std::vector<T> retVec[vec1.size()];

    for (int i=0; i<vec1.size(); i++)
        retVec[i] = vec1[i] + vec2[i];

    return retVec;
}

template<>
const std::vector<bdt> vector<bdt>::null(3, 0);

template<class T>
const std::vector<bdt> vector<T>::null = vector<bdt>(3, 0);

template<class T>
void vector<T>::invert(){
    for (int i=0; i<this.size(); i++)
        this[i] *= -1;
}

template<class T>
void vector<T>::mul(bdt toMul){
    for (int i=0; i<this.size(); i++)
        this[i] *= toMul;
}

template<class T>
template<class S>
void vector<T>::add(std::vector<S> toAdd){
    this = addTwo(this, toAdd);
}

template<class T>
std::vector<T> vector<T>::operator*(bdt toMul){
    return multiplicateTo(toMul);
}
template<class T>
std::vector<T> vector<T>::operator/(bdt toDiv){
    return multiplicateTo(1/toDiv);
}
template<class T>
std::vector<T> vector<T>::operator+(std::vector<T> toAdd){
    return additionTo(toAdd);
}
template<class T>
std::vector<T> vector<T>::operator-(std::vector<T> toSub){
    toSub.invert();
    return additionTo(toSub);
}
