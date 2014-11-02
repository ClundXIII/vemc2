#include "gravitation.h"

#include "./../universe.h"

using namespace vemc2;
using namespace vemc2::simulation;

gravitation::gravitation(vemc2::universe *globUniversets) :
    effect(globUniversets)
{

}

gravitation::~gravitation(){
}

void gravitation::tick(){

    object **tempobjectList = globUniverse->objectArray;
    Gfield  *tempGfield     = globUniverse->fields.G;
    object  *tempObj;
    bdt      dt = globUniverse->settings.sim.dt;

    for (int i=0; i<globUniverse->objectCount; i++){
        tempObj = tempobjectList[i];

        tempObj->addA(tempGfield->getVecA(tempObj->getX1(), tempObj->getX2(), tempObj->getX3(), tempObj->getMass()));
    }


    return;
}


void gravitation::upValues(){

    //this effect does not update any values

    return;
}
