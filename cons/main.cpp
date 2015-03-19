#include <iostream>

#include <vemc2/universe.h>

#include <Logging.hpp>

using namespace std;
using namespace vemc2;
using namespace Vesper;
using namespace Vesper::LoggingTypes;

int main(int argc, char *argv[]){

    Logging out(Vesper::LoggingTypes::client);

    out << "Creating World #1" << eom;
    universe *world1 = new universe();

    out << "Creating World #2" << eom;
    universe *world2 = new universe(3);

    out << "Set SimulationType ..." << eom;
    world1->setSimulationType(vemc2::planetSimulation);

    out << "inserting objects ..." << eom;
    world1->insertBody(new simulation::body(5, 5, 5, 50));
    world2->insertBody(new simulation::body(5, 2, 5, 5));
    world2->insertObject(new simulation::object(5, 2, 5, 5));
    world1->insertBody(new simulation::body(5, 5, 1, 42));

    out << "set Object Type" << eom;
    world2->setObjectType(t_body);
    world1->setObjectType(t_quant);

    out << "start World #1" << eom;
    world1->start();
    //sleep(10);
    world1->stop();
    out << "w1 stopped, run World #2" << eom;
    world2->run(10);

    out << "deleting world #1" << eom;
    delete world1;

    out << "deleting world #2" << eom;
    delete world2;

    out << "Client over and out." << eom;
    return 0;
}
