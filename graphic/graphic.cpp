#include "graphic.h"

#include <iostream>

using namespace vemc2::graphic;

graphicgl::graphicgl() :
    thread(graphicgl::static_run, this)
    {
    //
}

graphicgl::~graphicgl(){
}

void graphicgl::run(){
    std::cout << "started graphicthread" << std::endl;
}

void graphicgl::stop(){
}

void graphicgl::static_run(vemc2::graphic::graphicgl *toRun){

    toRun->run();

}
