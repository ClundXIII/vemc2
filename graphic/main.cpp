#include <iostream>

#include "graphic.h"
#include <core/universe.h>
#include <Logging.hpp>
#include <string>
#include <chrono>

using namespace std;
using namespace vemc2;
using namespace Vesper;
using namespace Vesper::LoggingTypes;

int main(int argc, char **argv){

    Logging out(LoggingTypes::client);

    out << "create graphic thread ..." << eom;

    graphic::graphicgl *g = new graphic::graphicgl(argc, argv);
    universe           *u = new universe(3);

    std::thread *glutThread = new std::thread(graphic::graphicgl::attachUniverse, u);

    //g->attachUniverse(u);

    out << "done!" << eom;

    string in;
    while (in != "exit"){
        cout << ">";
        cin >> in;

        if (in == "stop"){
            delete g;
            g=0;
        }
        else if (in == "start"){
            if (g) delete g;
            g = new graphic::graphicgl(argc, argv);
        }
        else if (in == "attach"){
        }
        else if (in == "test"){

            simulation::body b1(.5,  5,   5, 50);
            simulation::body b2( 7, -2,  -3, 10);
            simulation::body b3(-1,  0,  21, 42);
            u->insertBody(&b1);
            u->insertBody(&b2);
            u->insertBody(&b3);

            u->settings.graphic.useSphereForObj = true;

            u->setSimulationType(planetSimulation);

            simulation::recorder rec(u);
            rec.push_value(b1.getX1p(), "object 1 x", "m");
            rec.push_value(b1.getX2p(), "object 1 y", "m");
            rec.push_value(b1.getX3p(), "object 1 z", "m");
            rec.push_value(b2.getX1p(), "object 2 x", "m");
            rec.push_value(b2.getX2p(), "object 2 y", "m");
            rec.push_value(b2.getX3p(), "object 2 z", "m");
            rec.push_value(b3.getX1p(), "object 3 x", "m");
            rec.push_value(b3.getX2p(), "object 3 y", "m");
            rec.push_value(b3.getX3p(), "object 3 z", "m");

            u->insertEffect(&rec);

            u->settings.sim.dt *= 10;

            u->run(1000000000000);
        }
        else if (in == "restart"){
            delete g;
            g = new graphic::graphicgl(argc, argv);
        }
        else
            cout << "unknown command" << endl;

    }

    out << "     ... goodbye!" << eom;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return 0;
}
