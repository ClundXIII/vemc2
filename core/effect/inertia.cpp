#include "inertia.h"
#include "./../universe.h"
#include "./../mymath/math_struct.h"

#include <iostream>

using namespace vemc2::simulation;

inertia::inertia(vemc2::universe *globUniversets) :
    effect(globUniversets)
{
}

inertia::~inertia(){
}

void inertia::tick(){
    /**
     * well, nothing here, inertia doesn't tick
     */
}

void inertia::upValues(){

    object **tempobjectList = globUniverse->objectArray;
    object  *tempObj;
    bdt      dt = globUniverse->settings.sim.dt;

    if (tempobjectList == 0){
        std::cout << "fatal error: \"objectList == 0\" in effect/inertia.cpp" << std::endl;
        throw("fatal error!");
    }

    for (int i=0; tempobjectList[i] !=0; i++){
        tempObj = tempobjectList[i];

        //add accelaration from force
        tempObj->data.a.X1 += tempObj->data.F.X1 / tempObj->getMass();
        tempObj->data.a.X2 += tempObj->data.F.X2 / tempObj->getMass();
        tempObj->data.a.X3 += tempObj->data.F.X3 / tempObj->getMass();

        //add velocity from accelaration
        tempObj->data.v.X1 += tempObj->data.a.X1 * dt;
        tempObj->data.v.X2 += tempObj->data.a.X2 * dt;
        tempObj->data.v.X3 += tempObj->data.a.X3 * dt;

        //change position from velocity
        tempObj->setX1(tempObj->getX1() + tempObj->data.v.X1 * dt);
        tempObj->setX2(tempObj->getX2() + tempObj->data.v.X2 * dt);
        tempObj->setX3(tempObj->getX3() + tempObj->data.v.X3 * dt);

        //reset force, velocity and accelaration
        tempObj->setDataNull();
    }

}
