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

    for (int i=0; i<globUniverse->objectCount; i++){
        tempObj = tempobjectList[i];

        tempObj->addA(tempGfield->getVecA(tempObj->getX(), tempObj->getMass()));
    }


    return;
}


void gravitation::upValues(){

    //this effect does not update any values

    return;
}
