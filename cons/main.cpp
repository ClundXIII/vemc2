#include <iostream>

#include "universe.h"

using namespace std;
//using namespace vemc2;

int main(int argc, char *argv[]){

    vemc2::universe *world = new vemc2::universe();

    //world->setSimulationType(vemc2::planetSimulation);
    world->insertBody(new vemc2::simulation::body(5, 5, 5, 50));
    world->insertBody(new vemc2::simulation::body(5, 2, 5, 5));
    world->insertObject(new vemc2::simulation::object(5, 2, 5, 5));
    world->insertBody(new vemc2::simulation::body(5, 5, 1, 42));

    delete world;

    return 0;
}
