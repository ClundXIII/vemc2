#include "parser.h"

#include <iostream>

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

void parser::execute_static(vemc2::universe *parentUniverse, std::string command){
    throw "test exception 123";
}
