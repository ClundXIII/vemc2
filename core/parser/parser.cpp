#include "parser.h"

#include <iostream>
#include <list>
#include <array>

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

    while(!cmds.empty()){
        parentUniverse->out << (string)cmds.front() << eom;
        cmds.pop_front();
    }

}
