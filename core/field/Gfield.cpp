#include "Gfield.h"

#include "./../universe.h"

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

std::vector<bdt> Gfield::getVecA(bdt posX1, bdt posX2, bdt posX3, bdt mass){
    std::vector<bdt> posX;

    posX[0] = posX1;
    posX[1] = posX2;
    posX[2] = posX3;

    return getVecA(posX, mass);
}

/**
 * THE NOOB FUNCTION
 */
bdt* Gfield::getVecA_array(bdt posX1, bdt posX2, bdt posX3, bdt mass){
    std::vector<bdt> posX;

    posX[0] = posX1;
    posX[1] = posX2;
    posX[2] = posX3;

    std::vector<bdt> retVec = getVecA(posX, mass);

    bdt *retArray = new bdt[3];

    retArray[0] = retVec[0];
    retArray[1] = retVec[1];
    retArray[2] = retVec[2];

    return retArray;
}

std::vector<bdt> Gfield::getVecA(std::vector<bdt> posX, bdt mass){
    std::vector<bdt> retVec;

    bdt G = globUniverse->settings.sim.NatConst.G;
    bdt deadZoneSq = globUniverse->settings.sim.DeadZone * globUniverse->settings.sim.DeadZone;

    body *tempBody = 0;
    std::vector<bdt> dX, dX_sq;

    for (int i=0; i<globUniverse->bodyCount; i++ ){
        tempBody = globUniverse->bodyArray[i];

        //dX = tempBody->getX() - posX;
        dX[0] = tempBody->getX()[0] - posX[0];
        dX[1] = tempBody->getX()[1] - posX[1];
        dX[2] = tempBody->getX()[2] - posX[2];

        if ( (dX[0]*dX[0]+dX[1]*dX[1]+dX[2]*dX[2]) < deadZoneSq)
            continue;

        dX_sq[0] = dX[0] * dX[0];
        dX_sq[1] = dX[1] * dX[1];
        dX_sq[2] = dX[2] * dX[2];

        dX_sq[0] = 1 / dX_sq[0];
        dX_sq[1] = 1 / dX_sq[1];
        dX_sq[2] = 1 / dX_sq[2];

        retVec[0] += G * tempBody->getMass() * dX_sq[0];
        retVec[1] += G * tempBody->getMass() * dX_sq[1];
        retVec[2] += G * tempBody->getMass() * dX_sq[2];

    }

    return retVec;
}
