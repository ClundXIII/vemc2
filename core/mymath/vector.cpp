#include "vector.h"
#include "vec3bdt.h"

using namespace vemc2;
using namespace vemc2::mymath;

template<class T>
vector<T>::vector() /*: std::vector<T>()*/ {

}

template<class T>
vector<T>::vector(int i) /*: std::vector<T>()*/ {
    this->resize(i);
}

template<class T>
vector<T>::vector(T x1, T x2, T x3) /*: std::vector<T>()*/ {
    this->resize(3);

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

    std::vector<T> retVec;
    retVec.resize(vec1.size());

    for (int i=0; i<vec1.size(); i++)
        retVec[i] = vec1[i] + vec2[i];

    return retVec;
}

template<class T>
vector<T> vector<T>::normalize(){
    T length = getLength();
    if (length == 0) return (*this);
    return (*this)/length;
}

template<class T>
T vector<T>::getLength(){
    T sum = 0;

    for (int i=0; i<this->size(); i++)
        sum += (*this)[i] * (*this)[i];

    return pow(sum, 0.5);
}

/*template<>
const std::vector<bdt> vector<bdt>::null = vector<bdt>(3, 0);

template<class T>
const std::vector<bdt> vector<T>::null = vector<bdt>(3, 0);*/

template<class T>
vector<T> vector<T>::invert(std::vector<T> toInv){
    vector<T> retV;
    retV.resize(toInv.size());
    for (int i=0; i<toInv.size(); i++)
        retV[i] = -1 * toInv[i];

    return retV;
}

template<class T>
void vector<T>::mul(bdt toMul){
    for (int i=0; i<this->size(); i++)
        (*this)[i] *= toMul;
}

template<class T>
template<class S>
void vector<T>::add(std::vector<S> toAdd){
    this = addTwo(this, toAdd);
}

template<class T>
vector<T> vector<T>::operator*(bdt toMul){
    return multiplicateTo(toMul);
}
template<class T>
vector<T> vector<T>::operator/(bdt toDiv){
    if (toDiv == 0) throw (char*) "toDiv is 0 in vector.cpp::operator/()";
    return multiplicateTo(1/toDiv);
}
template<class T>
vector<T> vector<T>::operator+(std::vector<T> toAdd){
    return additionTo(toAdd);
}
template<class T>
vector<T> vector<T>::operator-(std::vector<T> toSub){
    return additionTo(invert(toSub));
}

template<class T>
vector<T> vector<T>::set(std::vector<T> toSet){
    if (toSet.size() != this->size())
        throw (char*) "error: size not identical in vector.cpp::set()";

    if (toSet.size() == 0)
        throw (char*) "error: size is 0 in vector.cpp::set()";

    for (int i=0; i<this->size(); i++)
        (*this)[i] = toSet[i];

    return *this;
}

template<class T>
vector<T> vector<T>::operator=(std::vector<T> toSet){
    return this->set(toSet);
}

template<class T>
vector<T> vector<T>::multiplicateTo(bdt toMul){
    vector<T> retVec;
    retVec.resize(this->size());

    for (int i=0; i<this->size(); i++)
        retVec[i] = (*this)[i] * toMul;

    return retVec;
}

template<class T>
vector<T> vector<T>::additionTo(std::vector<T> toAdd){
    vector<T> retV;
    retV.resize(this->size());
    retV.set(addTwo(*this, toAdd));
    return retV;
}

template class vector<bdt>;
