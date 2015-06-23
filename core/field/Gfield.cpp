#include "Gfield.h"

#include "./../universe.h"

using namespace vemc2;
using namespace vemc2::mymath;
using namespace vemc2::simulation;

Gfield::Gfield(vemc2::universe *globUniversets) :
    field::field(globUniversets)
{
    DeadZone = &(globUniverse->settings.sim.DeadZone);
}

Gfield::~Gfield(){
    //
}

/*void Gfield::setDeadZone(bdt *Zonets){
    DeadZone = Zonets;
}*/

vemc2::mymath::vec3bdt Gfield::getVecA(bdt posX1, bdt posX2, bdt posX3, bdt mass){
    vec3bdt posX(posX1, posX2, posX3);

    return getVecA(posX, mass);
}

/**
 * THE NOOB FUNCTION
 */
bdt* Gfield::getVecA_array(bdt posX1, bdt posX2, bdt posX3, bdt mass){
    vec3bdt posX;

    posX[0] = posX1;
    posX[1] = posX2;
    posX[2] = posX3;

    vec3bdt retVec = getVecA(posX, mass);

    bdt *retArray = new bdt[3];

    retArray[0] = retVec[0];
    retArray[1] = retVec[1];
    retArray[2] = retVec[2];

    return retArray;
}

vemc2::mymath::vec3bdt Gfield::getVecA(vec3bdt posX, bdt mass){
    vec3bdt retVec, posXvec;

    retVec = posX;
    posXvec = posX;


    bdt G = globUniverse->settings.sim.NatConst.G;

    body *tempBody = 0;
    vec3bdt dX, e;

    for (int i=0; globUniverse->bodyArray[i] != 0; i++ ){
        tempBody = globUniverse->bodyArray[i];


        dX = posXvec + tempBody->getX();

        //if ( (dX[0]*dX[0]+dX[1]*dX[1]+dX[2]*dX[2]) < deadZoneSq)
        //    continue;
        //nice, but not optimized:
        if (dX.getLength() < globUniverse->settings.sim.DeadZone)
            continue;

//        e = dX.normalize(); //the direction vector

//        retVec = retVec + e * (G * mass / (dX.getLength() * dX.getLength()));

    }

    return retVec;
}
