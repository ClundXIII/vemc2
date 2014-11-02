#include "body.h"

using namespace vemc2::simulation;

body::body(){
}

body::body(body *toCopy){

    setMass(toCopy->getMass());

    setX1(toCopy->getX1());
    setX2(toCopy->getX2());
    setX3(toCopy->getX3());
}

body::body(bdt posX1ts, bdt posX2ts, bdt posX3ts, bdt massts){
    posX1 = posX1ts;
    posX2 = posX2ts;
    posX3 = posX3ts;

    mass = massts;
}

body::~body(){
}

void body::draw(){}
void body::drawField(){}
void body::newValues(){}
void body::tick(){}

bdt body::getMass(){return mass;}
std::vector<bdt> body::getX(){
    std::vector<bdt> retVec;
    retVec[0] = getX1();
    retVec[1] = getX2();
    retVec[2] = getX3();
    return retVec;
}
bdt body::getX1()  {return posX1;}
bdt body::getX2()  {return posX2;}
bdt body::getX3()  {return posX3;}

void body::setMass(bdt massts){}
void body::setX1(bdt X1ts)    {}
void body::setX2(bdt X2ts)    {}
void body::setX3(bdt X3ts)    {}
