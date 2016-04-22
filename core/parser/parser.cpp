#include "parser.h"
#include "../universe.h"
#include "../effect/gravitation.h"

#include <iostream>
#include <list>

using namespace vemc2;
using namespace std;
using namespace Vesper::LoggingTypes;

parser::parser(vemc2::universe *pUni){
    parentUniverse = pUni;
}

int parser::execute(std::string command){
    try {
        execute_static(parentUniverse, command);
    }
    catch (char *error_msg){

        parentUniverse->out << "Error while parsing command: \"" << command <<\
                               "\"\n Error: \"" << error_msg << "\"" <<\
                               Vesper::LoggingTypes::eom;

        return -1;
    }
    catch (char const* error_msg){

        parentUniverse->out << "Error while parsing command: \"" << command <<\
                               "\"\n Error: \"" << error_msg << "\"" <<\
                               Vesper::LoggingTypes::eom;

        return -1;
    }
    catch (...){

        parentUniverse->out << "Error while parsing command: \"" << command <<\
                               "\"\n Unknown Error datatype"<<\
                               Vesper::LoggingTypes::eom;

        return -2;
    }
    return 0;
}

/**
 * Splits the cmd into segments
 * uses STL, yay!
 */
std::list<std::string> splitInChars(std::string cmd){
    int retcharLength=0, i=0;

    std::string currentSegment="";
    std::list<std::string> retList;


    while (cmd[i]!=0){
        if (cmd[i] == ' '){
            if (currentSegment!=""){
                retList.push_back(currentSegment);
                currentSegment="";
            }
        }
        else{
            currentSegment.append(1, cmd[i]);
        }
        i++;
    }
    retList.push_back(currentSegment);
    return retList;
}

void parser::execute_static(vemc2::universe *parentUniverse, std::string command){

    std::list<std::string> cmds = splitInChars(command);

    //while(!cmds.empty()){
    //    parentUniverse->out << (string)cmds.front() << eom;
    //    cmds.pop_front();
    //}

    std::string primaryCommand = cmds.front();
    cmds.pop_front();

    if (primaryCommand == "set"){
        if (cmds.empty()){
            parentUniverse->out << "expect at least one Parameter for \"set\"" << eom;
            return;
        }

        std::string secondaryCommand = cmds.front();
        cmds.pop_front();
        if ((secondaryCommand == "vlevel")||
            (secondaryCommand == "vLevel")){
                if (cmds.empty()){
                    parentUniverse->out << "expect at least one Parameter for \"set vlevel\"" << eom;
                    return;
                }
                parentUniverse->setVerboseLevel(atoi( ((std::string)cmds.front()).c_str() ));
        }
        else if (secondaryCommand == "settings.texture.used"){

        }
        else if (secondaryCommand == "settings.texture.Name_Underground"){

        }
        else if (secondaryCommand == "settings.texture.Name_Background"){

        }
        else if (secondaryCommand == "settings.texture.Name_Font"){

        }
        else if (secondaryCommand == "settings.texture.under_heigh"){

        }
        else if (secondaryCommand == "settings.graphic"){

        }
        else if (secondaryCommand == "settings.sim_thread"){

        }
        else if (secondaryCommand == "settings.sim"){

        }
        else if (secondaryCommand == "settings.win"){

        }
        else if (secondaryCommand == "settings.gravPlane"){

        }
        else if (secondaryCommand == "tts"){
                if (cmds.empty()){
                    parentUniverse->out << "expect at least one Parameter for \"set tts\"" << eom;
                    return;
                }
                parentUniverse->simulationThread->time_to_stop = atoi( ((std::string)cmds.front()).c_str() );
        }
        else{
            parentUniverse->out << "unknown parameter for \"set\"" << eom;
        }

    }
    else if (primaryCommand == "get"){
        //
    }
    else if (primaryCommand == "clear"){
        if (cmds.empty()){
            parentUniverse->out << "expect at least one Parameter for \"clear\"" << eom;
            return;
        }

        std::string secondaryCommand = cmds.front();
        cmds.pop_front();
        if ((secondaryCommand == "simStruct")||
            (secondaryCommand == "simstruct")){
                parentUniverse->clearSimulateStruct();
        }
        else{
            parentUniverse->out << "unknown parameter for \"clear\"" << eom;
        }
    }
    else if (primaryCommand == "insert"){
        if (cmds.empty()){
            parentUniverse->out << "expect at least one Parameter for \"insert\"" << eom;
            return;
        }

        std::string secondaryCommand = cmds.front();
        cmds.pop_front();
        if (secondaryCommand == "effect"){
                if (cmds.empty()){
                    parentUniverse->out << "expect at least one Parameter for \"insert effect\"" << eom;
                    return;
                }
                else{
                    if (cmds.front() == "gravitation")
                        parentUniverse->insertEffect((vemc2::simulation::effect*)new vemc2::simulation::gravitation(parentUniverse));
                    else if (cmds.front() == "inertia")
                        parentUniverse->insertEffect((vemc2::simulation::effect*)new vemc2::simulation::inertia(parentUniverse));
                    else if (cmds.front() == "recorder")
                        parentUniverse->insertEffect((vemc2::simulation::effect*)new vemc2::simulation::recorder(parentUniverse));
                    else
                        parentUniverse->out << "unknown effect" << eom;
                }
        }
        else{
            parentUniverse->out << "unknown parameter for \"insert\"" << eom;
        }
    }
    else if (primaryCommand == "start"){
        parentUniverse->start();
    }
    else if (primaryCommand == "stop"){
        parentUniverse->stop();
    }
    else if (primaryCommand == "pause"){
        parentUniverse->pause();
    }
    else if (primaryCommand == "unpause"){
        parentUniverse->unpause();
    }
    else if (primaryCommand == "run"){
        if (cmds.empty())
            parentUniverse->run();
        else{
            bdt secs=0;
            secs = atoi(((std::string)cmds.front()).c_str());
            parentUniverse->run(secs);
        }
    }
    else if (primaryCommand == "update"){
        parentUniverse->update();
    }
    else if (primaryCommand == "reset"){
        if (cmds.empty()){
            parentUniverse->out << "expect at least one Parameter for \"reset\"" << eom;
            return;
        }

        std::string secondaryCommand = cmds.front();
        cmds.pop_front();
        if ((secondaryCommand == "arrays")||
            (secondaryCommand == "Arrays")){
                parentUniverse->resetArrays();
        }
        else if ((secondaryCommand == "world")||
            (secondaryCommand == "World")){
                parentUniverse->resetWorld();
        }
        else{
            parentUniverse->out << "unknown parameter for \"reset\"" << eom;
        }
    }
    else if (primaryCommand == "demo"){

            simulation::body* b1 = new simulation::body(.5,  5,   5, 50);
            simulation::body* b2 = new simulation::body( 7, -2,  -3, 10);
            simulation::body* b3 = new simulation::body(-1,  0,  21, 42);
            parentUniverse->insertBody(b1);
            parentUniverse->insertBody(b2);
            parentUniverse->insertBody(b3);

            parentUniverse->settings.graphic.useSphereForObj = true;

            parentUniverse->setSimulationType(planetSimulation);

            simulation::recorder* rec = new simulation::recorder(parentUniverse);
            rec->push_value(b1->getX1p(), "object 1 x", "m");
            rec->push_value(b1->getX2p(), "object 1 y", "m");
            rec->push_value(b1->getX3p(), "object 1 z", "m");
            rec->push_value(b2->getX1p(), "object 2 x", "m");
            rec->push_value(b2->getX2p(), "object 2 y", "m");
            rec->push_value(b2->getX3p(), "object 2 z", "m");
            rec->push_value(b3->getX1p(), "object 3 x", "m");
            rec->push_value(b3->getX2p(), "object 3 y", "m");
            rec->push_value(b3->getX3p(), "object 3 z", "m");

            rec->console_output = false;

            parentUniverse->insertEffect(rec);

            parentUniverse->settings.sim.dt *= 10;
            parentUniverse->simulationThread->time_to_stop = 100000;

    }
    else{
        parentUniverse->out << "unknown Command: \"" << primaryCommand << "\"" << eom;
    }

    cmds.clear();

}
