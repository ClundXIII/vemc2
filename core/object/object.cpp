#include "./object.h"

#include <iostream>
#include <iomanip>
#include <vector>

using namespace vemc2::simulation;

object::object(){
    posX1 = 0;
    posX2 = 0;
    posX3 = 0;

    setDataNull();

    return;
}

object::object(object *toCopy){
    posX1 = toCopy->getX1();
    posX2 = toCopy->getX2();
    posX3 = toCopy->getX3();

    mass = toCopy->getMass();

    setDataNull();
}

object::object(bdt posX1ts, bdt posX2ts, bdt posX3ts, bdt massts){
    posX1 = posX1ts;
    posX2 = posX2ts;
    posX3 = posX3ts;

    mass = massts;

    setDataNull();
}

object::~object(){
    //dtor
}

void object::draw(){

}

void object::drawField(){

}

bdt object::getMass(){return mass;}
vemc2::mymath::vec3bdt object::getX(){
    vemc2::mymath::vec3bdt retVec;
    retVec[0] = getX1();
    retVec[1] = getX2();
    retVec[2] = getX3();
    return retVec;
}
bdt object::getX1()  {return posX1;}
bdt object::getX2()  {return posX2;}
bdt object::getX3()  {return posX3;}

void object::setMass(bdt massts){mass  = massts;}
void object::setX1(bdt X1ts)    {posX1 = X1ts;}
void object::setX2(bdt X2ts)    {posX2 = X2ts;}
void object::setX3(bdt X3ts)    {posX3 = X3ts;}

void object::setDataNull(){
    data.F.X1 = 0;
    data.F.X2 = 0;
    data.F.X3 = 0;

    data.a.X1 = 0;
    data.a.X2 = 0;
    data.a.X3 = 0;

    //data.v.X1 = 0;
    //data.v.X2 = 0;
    //data.v.X3 = 0;
}

void object::addF(std::vector<bdt> Fta){
    data.F.X1 += Fta[0];
    data.F.X2 += Fta[1];
    data.F.X3 += Fta[2];
}

void object::addA(std::vector<bdt> Ata){
    data.a.X1 += Ata[0];
    data.a.X2 += Ata[1];
    data.a.X3 += Ata[2];
}

void object::addV(std::vector<bdt> Vta){
    data.v.X1 += Vta[0];
    data.v.X2 += Vta[1];
    data.v.X3 += Vta[2];
}

