#include <iostream>
#include <math.h>

#include "eld.h"

#define ELD_DEBUG_ON

using namespace vemc2::simulation;

eld retEld(bdt base, int exponent){
    eld ret(base, exponent);
    return ret;
}

eld::eld(){
    base = 0;
    exp = 0;
}

eld::eld(eld *c){
    base = c->gB();
    exp = c->gE();
}

eld::eld(bdt basets, int expts){
    base = basets;
    exp = expts;
    #ifdef ELD_DEBUG_ON
        std::cout << "sB: " << base << std::endl;
        std::cout << "sE: " << exp << std::endl;
    #endif
    optimize();
}

eld::~eld(){
    //dtor
}

void eld::sB(bdt basets){
    base = basets;
    optimize();
}

void eld::sE(int expts){
    exp = expts;
}

void eld::sBE(bdt basets, int expts){
    base = basets;
    exp = expts;
    optimize();
}

bdt eld::getV(){
    return base * pow(10, exp);
}

bdt eld::getVbyExp(int P){
    return base * pow(10, (P+exp));
}

bdt eld::gB(){
    return base;
}

int eld::gE(){
    return exp;
}

eld* eld::getNewEld(){
    return new eld(base, exp);
}

/*eld eld::getEld(){
    eld retEld;
    retEld.sgE(base, exp);
    return retEld;
}*/

void eld::optimize(){
    if (base > 0){
        while (base >= 10){
            #ifdef ELD_DEBUG_ON
                std::cout << "/10;+1" << std::endl;
            #endif
            exp++;
            base /= 10;
        }
        while (base < 1){
            #ifdef ELD_DEBUG_ON
                std::cout << "*10;-1" << std::endl;
            #endif
            exp--;
            base *= 10;
        }
    }
    else if (base < 0){
        while (base <= -10){
            #ifdef ELD_DEBUG_ON
                std::cout << "/10;+1" << std::endl;
            #endif
            exp++;
            base /= 10;
        }
        while (base > -1){
            #ifdef ELD_DEBUG_ON
                std::cout << "*10;-1" << std::endl;
            #endif
            exp--;
            base *= 10;
        }
    }
}

eld eld::Add(eld toAdd){

    int middlePot = (toAdd.gE()+exp) / 2;
    #ifdef ELD_DEBUG_ON
        std::cout << "middlePot: " << middlePot << std::endl;
    #endif

    bdt WertA =  base * pow( 10, exp     - middlePot );
    bdt WertB = toAdd.gB() * pow( 10, toAdd.gE() - middlePot );

    #ifdef ELD_DEBUG_ON
        std::cout << "ValueA: " << WertA << std::endl;
        std::cout << "ValueB: " << WertB << std::endl;
    #endif


    eld retEld;

    retEld.sBE( WertA+WertB , middlePot );

    #ifdef ELD_DEBUG_ON
        std::cout << "Value: " << retEld.getV() << std::endl;
    #endif

    return retEld;
}

eld eld::Mul(eld toMul){
    eld retEld;
    retEld.sBE(base * toMul.gB(), exp + toMul.gE());
    return retEld;
}

///operators:

void eld::operator=(eld toSet){

    base = toSet.gB();
    exp = toSet.gE();
}

void eld::operator=(bdt toSet){
    base = toSet;
    exp = 0;
    optimize();
}

//basic operations:

eld eld::operator+(eld toAdd){

    return Add(toAdd);
}

eld eld::operator-(eld toSub){
    toSub.sB(-toSub.gB());
    return Add(toSub);
}

eld eld::operator*(eld toMul){
    return Mul(toMul);
}

eld eld::operator/(eld toDiv){
    toDiv.sB(toDiv.gB()*(-1));
    toDiv.sE(-toDiv.gE());
    return Mul(toDiv);
}

//now, with bdt's as input:
///TODO: OPTIMIZE!!!

eld eld::operator+(bdt toAdd){
    eld temp;
    temp.sBE(toAdd, 0);
    return Add(temp);
}

eld eld::operator-(bdt toSub){
    eld temp;
    temp.sBE(-toSub, 0);
    return Add(temp);
}

eld eld::operator*(bdt toMul){
    eld temp;
    temp.sBE(toMul, 0);
    return Mul(temp);
}

eld eld::operator/(bdt toDiv){
    eld temp;
    temp.sBE( (toDiv*(-1)), 0);
    return Mul(temp);
}

