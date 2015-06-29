#include <iostream>

#include <vemc2/core/universe.h>

#include <Logging.hpp>

using namespace std;
using namespace vemc2;
using namespace Vesper;
using namespace Vesper::LoggingTypes;
using namespace vemc2::mymath;

int main(int argc, char *argv[]){

    Logging out(Vesper::LoggingTypes::client);

    universe *testWorld = new universe(3);
    testWorld->insertBody(new simulation::body(.5,  5,   5, 50));
    testWorld->insertBody(new simulation::body( 7, -2,  -3, 10));
    testWorld->insertBody(new simulation::body(-1,  0,  21, 42));

    testWorld->setSimulationType(planetSimulation);

    testWorld->run(10);
    delete testWorld;
    /*try {
        vec3bdt test1(1, 2, 3), test2(4, 5, 6), test3;

        test3 = test1 + test2;

        cout << test3[0] << test3[1] << test3[2] << endl;
    }
    catch (char* c){
        cout << c << endl;
    }
    catch (...){
    }*/

    /*out << "Creating World #1" << eom;
    universe *world1 = new universe();

    out << "Creating World #2" << eom;
    universe *world2 = new universe(3);

    out << "Set SimulationType ..." << eom;
    world1->setSimulationType(vemc2::planetSimulation);

    out << "Set SimulationType2..." << eom;
    world2->setSimulationType(vemc2::planetSimulation);

    out << "inserting objects ..." << eom;
    world1->insertBody(new simulation::body(5, 5, 5, 50));
    world2->insertBody(new simulation::body(5, 2, 5, 5));
    world2->insertObject(new simulation::object(5, 2, 5, 5));
    world1->insertBody(new simulation::body(5, 5, 1, 42));

    out << "start World #1" << eom;
    //world1->start();
    //sleep(10);
    world1->stop();
    out << "w1 stopped, run World #2" << eom;
    world2->run(10);

    out << "deleting world #1" << eom;
    delete world1;

    out << "deleting world #2" << eom;
    delete world2;*/

    out << "Client over and out." << eom;
    return 0;
}
