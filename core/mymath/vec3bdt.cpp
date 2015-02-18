#include "./vec3bdt.h"

using namespace vemc2::mymath;

vec3bdt::vec3bdt() : vector<bdt>(3) {
}

vec3bdt::vec3bdt(bdt x1, bdt x2, bdt x3) : vector<bdt>(3) {
    (*this)[0] = x1;
    (*this)[1] = x2;
    (*this)[2] = x3;
}

vec3bdt vec3bdt::to3Bdt(std::vector<bdt> toConvert){
    return vec3bdt(toConvert[0], toConvert[1], toConvert[2]);
}

vec3bdt vec3bdt::operator*(bdt toMul){return to3Bdt(multiplicateTo(toMul));}
vec3bdt vec3bdt::operator/(bdt toDiv){return to3Bdt(multiplicateTo(1/toDiv));}
vec3bdt vec3bdt::operator+(std::vector<bdt> toAdd){return to3Bdt(additionTo(toAdd));}
vec3bdt vec3bdt::operator-(std::vector<bdt> toSub){return to3Bdt(additionTo(invert(toSub)));}
vec3bdt vec3bdt::operator=(std::vector<bdt> toSet){return to3Bdt(set(toSet));}
