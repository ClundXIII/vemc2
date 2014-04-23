#include "universe.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace vemc2;
using namespace std;

universe::universe(){
    cout << "Virtual e = m * c^2 (c) by Simon Michalke, 2014" << endl;
    cout << "vcore Library, Version 0.0.01-pre / 23042014" << endl;
    cout << "Have a lot of fun ..." << endl;
    cout << "    creating new universe         ..."   << endl;
    cout << "(01)getting global settings       ..."   << endl;
    getGlobalSettings();
    cout << "                                  done!" << endl;
    cout << "(02)reserving space for drawables ..."   << endl;
    reservDrawableArraySpace(\
                                      2168, //drawableCount
                                      2048, //objectCount
                                      1024, //bodyCount
                                      1024, //quantCount
                                       128, //fieldCount
                                        16  //noobjectCount
                                      );
    cout << "                                  done!" << endl;
    cout << "(10)creating simulation           ..."   << endl;
    cout << "(11)creating simThread            ..."   << endl;
    cout << "                                  done!" << endl;
}

universe::~universe(){
    //dtor
}

void universe::start(){

}

void universe::run(){
}

void universe::run(double secondsToRun){
}

void universe::getGlobalSettings(){
    settings.texture.used               = settings::Texture::used;
    settings.texture.Name_Underground   = new char[256];
    settings.texture.Name_Background    = new char[256];
    settings.texture.Name_Font          = new char[256];
    strcpy(settings.texture.Name_Underground, settings::Texture::Name_Underground);
    strcpy(settings.texture.Name_Background,  settings::Texture::Name_Background);
    strcpy(settings.texture.Name_Font,        settings::Texture::Name_Font);

    settings.texture.UndergroundNr      = 0;
    settings.texture.BackgroundNr       = 0;
    settings.texture.Underground_Heigh  = 0;

    settings.graphic.useColoredObjs     = settings::Graphic::useColoredObjs;
    settings.graphic.vLines             = settings::Graphic::vLines;
    settings.graphic.countPointsBuffer  = settings::Graphic::countPointsBuffer;
    settings.graphic.fps                = settings::Graphic::fps;
    settings.graphic.LoghLevel          = settings::Graphic::LoghLevel;
    settings.graphic.scale              = settings::Graphic::scale;
    settings.graphic.useGravPlane       = settings::Graphic::useGravPlane;
    //settings.graphic.fMode              = settings::Graphic::fMode;
    settings.graphic.fProbeSize         = settings::Graphic::fProbeSize;
    settings.graphic.useSFML2overlay    = settings::Graphic::useSFML2overlay;
    settings.graphic.useSphereForObj    = settings::Graphic::useSphereForObj;

    settings.graphic.sphere.countX      = settings::Graphic::Sphere::countX;
    settings.graphic.sphere.countY      = settings::Graphic::Sphere::countY;
    settings.graphic.sphere.mode        = settings::Graphic::Sphere::mode;

    settings.sim.actIntervall           = settings::Sim::actIntervall;
    settings.sim.useSimTimeToDump       = settings::Sim::useSimTimeToDump;
    settings.sim.showDebText            = settings::Sim::showDebText;
    settings.sim.useParaProc            = settings::Sim::useParaProc;
    settings.sim.countParaThreads       = settings::Sim::countParaThreads;
    settings.sim.quant_Simulation       = settings::Sim::quant_Simulation;

    settings.win.SPSreal                = settings::Win::SPSreal;

    settings.gravPlane.countX           = settings::gravPlane::countX;
    settings.gravPlane.countY           = settings::gravPlane::countY;
    settings.gravPlane.countZ           = settings::gravPlane::countZ;
    settings.gravPlane.offX             = settings::gravPlane::offX;
    settings.gravPlane.offY             = settings::gravPlane::offY;
    settings.gravPlane.offZ             = settings::gravPlane::offZ;
    settings.gravPlane.stretch          = settings::gravPlane::stretch;
    settings.gravPlane.Ver_Richt        = settings::gravPlane::Ver_Richt;
    settings.gravPlane.MaxFieldAct      = settings::gravPlane::MaxFieldAct;
}

void universe::reservDrawableArraySpace(\
                              int drawableCount, \
                              int objectCount,   \
                              int bodyCount,     \
                              int quantCount,    \
                              int fieldCount,    \
                              int noobjectCount  \
                              ){
    drawableArray = new drawable*[drawableCount];
    for (int i=0; i<drawableCount; i++)
        drawableArray[i] = 0;
    cout << "    " << drawableCount << " drawables" << endl;

    objectArray   = new object*[objectCount];
    for (int i=0; i<objectCount; i++)
        objectArray[i] = 0;
    cout << "    " << objectCount << " objects" << endl;

    bodyArray     = new body*[bodyCount];
    for (int i=0; i<bodyCount; i++)
        bodyArray[i] = 0;
    cout << "    " << bodyCount << " bodies" << endl;

    quantArray    = new quant*[quantCount];
    for (int i=0; i<quantCount; i++)
        quantArray[i] = 0;
    cout << "    " << quantCount << " quants" << endl;

    fieldArray    = new field*[fieldCount];
    for (int i=0; i<fieldCount; i++)
        fieldArray[i] = 0;
    cout << "    " << fieldCount << " fields" << endl;

    noobjectArray = new noobject*[noobjectCount];
    for (int i=0; i<noobjectCount; i++)
        noobjectArray[i] = 0;
    cout << "    " << noobjectCount << " noobjects" << endl;

}

void universe::invokeBeforeSim(){}
void universe::invokeMiddleSim(){}
void universe::invokeAfterSim(){}

