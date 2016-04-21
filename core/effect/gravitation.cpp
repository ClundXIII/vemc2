#include "gravitation.h"

#include "./../universe.h"

#include <iostream>

using namespace vemc2;
using namespace vemc2::simulation;

gravitation::gravitation(vemc2::universe *globUniversets) :
    effect(globUniversets){
    setPriority(50);
}

gravitation::~gravitation(){
}

void gravitation::tick(){

    body   **tempobjectList = globUniverse->bodyArray;
    Gfield  *tempGfield     = globUniverse->fields.G;
    body    *tempObj;

    for (int i=0; globUniverse->bodyArray[i] != 0; i++){
        tempObj = tempobjectList[i];

        tempObj->addA(tempGfield->getVecA(tempObj->getX(), tempObj->getMass()));
    }


    return;
}


void gravitation::upValues(){

    //this effect does not update any values

    return;
}
