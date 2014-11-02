#include <iostream>

#include <universe.h>

using namespace std;
//using namespace vemc2;

int main(int argc, char *argv[]){

    Vesper::Vout::init();

    vemc2::universe *world1 = new vemc2::universe();
    vemc2::universe *world2 = new vemc2::universe();

    //world->setSimulationType(vemc2::planetSimulation);
    world1->insertBody(new vemc2::simulation::body(5, 5, 5, 50));
    world2->insertBody(new vemc2::simulation::body(5, 2, 5, 5));
    world2->insertObject(new vemc2::simulation::object(5, 2, 5, 5));
    world1->insertBody(new vemc2::simulation::body(5, 5, 1, 42));

    world2->setObjectType(vemc2::t_body);
    world1->setObjectType(vemc2::t_quant);

    world1->start();
    //sleep(10);
    world1->stop();
    //world2->run(10);

    delete world1;

    delete world2;

    return 0;
}
