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

            u->insertBody(new simulation::body(.5,  5,   5, 50));
            u->insertBody(new simulation::body( 7, -2,  -3, 10));
            u->insertBody(new simulation::body(-1,  0,  21, 42));

            u->settings.graphic.useSphereForObj = true;

            u->setSimulationType(planetSimulation);

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
