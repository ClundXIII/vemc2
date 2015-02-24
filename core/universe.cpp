#include "universe.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace vemc2;
using namespace vemc2::simulation;
using namespace vemc2::settings;
using namespace Vesper::LoggingTypes;

#define v0 if (verboseLevel >= 0)
#define v1 if (verboseLevel >= 1)
#define v2 if (verboseLevel >= 2)
#define v3 if (verboseLevel >= 3)

universe::universe() :
    out(Vesper::LoggingTypes::server)

    {
    v0 out << "===============================================" << eom;
    v0 out << "Virtual e = m * c^2 (c) by Simon Michalke, 2014" << eom;
    v0 out << "vcore Library, Version 0.0.02-pre / 19022015" << eom;
    v1 out << "Have a lot of fun ...                " << eom;
    v0 out << "    creating new universe         ..." << eom;

    drawableArray =0;
    objectArray   =0;
    bodyArray     =0;
    quantArray    =0;
    fieldArray    =0;
    noobjectArray =0;

    effectArray   =0;

    drawableCount = 2168;
    objectCount   = 2084;
    bodyCount     = 1024;
    quantCount    = 1024;
    fieldCount    =  128;
    noobjectCount =   16;

    effectCount = 16;

    useForSimulation = t_none;
    simulateObjectCount = 0;
    simulateObjects = 0;

    simulateStruct.objectCount = 0;

    setSimulationType(planetSimulation);

    verboseLevel = 0;

    update();

    out << "==================done!========================" << eom;
}


universe::universe(int vLevel) :
    out(Vesper::LoggingTypes::server)
{

    verboseLevel = vLevel;

    v0 out << "===============================================" << eom;
    v0 out << "Virtual e = m * c^2 (c) by Simon Michalke, 2014" << eom;
    v0 out << "vcore Library, Version 0.0.02-pre / 19022015" << eom;
    v1 out << "Have a lot of fun ...                " << eom;
    v0 out << "    creating new universe         ..." << eom;

    drawableArray =0;
    objectArray   =0;
    bodyArray     =0;
    quantArray    =0;
    fieldArray    =0;
    noobjectArray =0;

    effectArray   =0;

    drawableCount = 2168;
    objectCount   = 2084;
    bodyCount     = 1024;
    quantCount    = 1024;
    fieldCount    =  128;
    noobjectCount =   16;

    effectCount = 16;

    useForSimulation = t_none;
    simulateObjectCount = 0;
    simulateObjects = 0;

    simulateStruct.objectCount = 0;

    setSimulationType(planetSimulation);

    update();

    v0 out << "==================done!========================" << eom;
}

universe::~universe(){

    v0 out << "(END) delete() invoked ... cleaning up ..." << eom;

    //cleaning up
    deleteAllDrawables();
    deleteAllEffects();

    v0 out << "... done with cleaning up" << eom;
}

void universe::update(){
    v1 out << "(00)update() invoked!                " << eom;
    v2 out << "(01)getting global settings       ..." << eom;

    getGlobalSettings();

    v2 out << "                                done!" << eom;
    v2 out << "(02)reserving space for drawables ..." << eom;

    resetArrays();

    v2 out << "                                done!" << eom;
    v2 out << "(10)creating simulation           ..." << eom;
    v2 out << "(11)setting up effects            ..." << eom;

    if (effectArray != 0){ //we have to delete the old effects first!
        v2 out << "    deleting old effects ..." << eom;
        for (int i=0; i<effectCount; i++){
            delete effectArray[i];
        }
        delete effectArray;
    }
    effectArray = new effect*[effectCount];
    for (int i=0; i<effectCount; i++)
        effectArray[i] = 0;
    v2 out << "                                done!" << eom;
    v2 out << "(12)creating simThread            ..." << eom;
    v2 out << "                                done!" << eom;

    v0 out << "  sucessfully created a new universe!" << eom;
}

void universe::resetArrays(){
    reserveDrawableArraySpace(\
                              drawableCount,
                              objectCount,
                              bodyCount,
                              quantCount,
                              fieldCount,
                              noobjectCount
                              );
}

void universe::resetWorld(){

    clearSimulateStruct();

    switch (useForSimulation){
      case vemc2::t_body:
        simulateStruct.objectCount = bodyCount;
        simulateStruct.objects.b = new simulation::body*[bodyCount];
        for (int i=0; i<bodyCount; i++){
            simulateStruct.objects.b[i] = new simulation::body(bodyArray[i]);
        }
       break;

      case vemc2::t_quant:
        simulateStruct.objectCount = quantCount;
        simulateStruct.objects.q = new simulation::quant*[quantCount];
        for (int i=0; i<quantCount; i++){
            simulateStruct.objects.q[i] = new simulation::quant(quantArray[i]);
        }
       break;

      default:
        ///TODO: add error!
       break;
    }

}

void universe::start(){
    if (simulationThread == 0)
        simulationThread = new simulation::sim_thread(this);

    simulationThread->stop();
    simulationThread->start();
}

void universe::stop(){

    simulationThread->stop();
}

void universe::pause(){
    if (simulationThread == 0) return;
    else
        simulationThread->pause();
}

void universe::unpause(){
    if (simulationThread == 0) return;
    else
        simulationThread->unpause();
}

void universe::clearSimulateStruct(){
    if (simulateStruct.objectCount == 0) return;

    if (simulateStruct.objects.b == 0) return;

    for (int i=0; i<simulateStruct.objectCount; i++)
        delete simulateStruct.objects.b[i];

    delete simulateStruct.objects.b;

}

void universe::run(){
}

void universe::run(double secondsToRun){
}

/**
 *
 *
 *
 *
 *
 */
int universe::setSimulationType(vemc2::simulation_type simTypets){
    simType = simTypets;
    switch (simType){
      case vemc2::planetSimulation:
        setObjectType(vemc2::t_body);
       break;

      case vemc2::quantumSimulation:
        setObjectType(vemc2::t_quant);
       break;

      case vemc2::feynmanSimulation:
        setObjectType(vemc2::t_quant);
       break;

      case vemc2::bodySimulation:
        setObjectType(vemc2::t_body);
       break;

      default:
        ///TODO: add error!
       break;

    }

    return 0;
}

void universe::setObjectType(objectType typets){
    useForSimulation = typets;

    switch (useForSimulation){
      case vemc2::t_body:
        simulateObjects = reinterpret_cast<simulation::object**>(bodyArray);
       break;

      case vemc2::t_quant:
        simulateObjects = reinterpret_cast<simulation::object**>(quantArray);
       break;

      default:
        ///TODO: add error!
       break;

    }
}

/**
 * just a quick define to get a nicer code within
 * the *insert() functions ;-)
 */
#define sTAE(a) scrollToArrayEnd(a)

int universe::insertDrawable(vemc2::simulation::drawable *toInsert){

    int pos = sTAE( (void**)drawableArray);
    if (pos >= (drawableCount - 1) ){
        v0 out << "drawableCount exceed limits in universe.cpp::insertDrawable!" << eom;
        return 1;
    }

    drawableArray[pos] = toInsert;

    v1 out << "Inserted drawable at position " << pos << eom;

    return 0;
}

int universe::insertObject(vemc2::simulation::object *toInsert){

    int ret;

    //first insert this in the mother class array:
    ret = insertDrawable( (drawable*) toInsert);
    if (ret != 0){
        v0 out << "insertDrawable returned " << ret << " in universe.cpp::insertObject" << eom;
        return 2;
    }


    int pos = sTAE( (void**)objectArray);
    if (pos >= (objectCount - 1) ){
        v0 out << "objectCount exceed limits in universe.cpp::insertObject!" << eom;
        return 1;
    }

    objectArray[pos] = toInsert;

    v1 out << "Inserted object at position " << pos<< eom;

    return 0;
}

int universe::insertBody(vemc2::simulation::body *toInsert){

    int ret;

    //first insert this in the mother class array:
    ret = insertObject( (object*) toInsert);
    if (ret != 0){
        v0 out << "insertObject returned " << ret << " in universe.cpp::insertBody" << eom;
        return 2;
    }


    int pos = sTAE( (void**)bodyArray);
    if (pos >= (bodyCount - 1) ){
        v0 out << "bodyCount exceed limits in universe.cpp::insertBody!" << eom;
        return 1;
    }

    bodyArray[pos] = toInsert;

    v1 out << "Inserted body at position " << pos << eom;

    return 0;
}

int universe::insertQuant(vemc2::simulation::quant *toInsert){

    int ret;

    //first insert this in the mother class array:
    ret = insertObject( (object*) toInsert);
    if (ret != 0){
        //out << "insertObject returned ";
        //out << ret;
        //out << " in universe.cpp::insertQuant";
        //out << endl;
        return 2;
    }


    int pos = sTAE( (void**)quantArray);
    if (pos >= (quantCount - 1) ){
        //out << "quantCount exceed limits in universe.cpp::insertQuant!";
        //out << endl;
        return 1;
    }

    quantArray[pos] = toInsert;

    //out << "Inserted quant at position ";
    //out << pos;
    //out << endl;

    return 0;
}

int universe::insertField(vemc2::simulation::field *toInsert){

    int ret;

    //first insert this in the mother class array:
    ret = insertDrawable( (drawable*) toInsert);
    if (ret != 0){
        //out << "insertDrawable returned ";
        //out << ret;
        //out << " in universe.cpp::insertField";
        //out << endl;
        return 2;
    }


    int pos = sTAE( (void**)fieldArray);
    if (pos >= (fieldCount - 1) ){
        //out << "fieldCount exceed limits in universe.cpp::insertField!";
        //out << endl;
        return 1;
    }

    fieldArray[pos] = toInsert;

    //out << "Inserted field at position ";
    //out << pos;
    //out << endl;


    return 0;
}

int universe::insertNoobject(vemc2::simulation::noobject *toInsert){

    int ret;

    //first insert this in the mother class array:
    ret = insertDrawable( (drawable*) toInsert);
    if (ret != 0){
        //out << "insertDrawable returned ";
        //out << ret;
        //out << " in universe.cpp::insertNoobject";
        //out << endl;
        return 2;
    }


    int pos = sTAE( (void**)noobjectArray);
    if (pos >= (noobjectCount - 1) ){
        //out << "noobjectCount exceed limits in universe.cpp::insertNoobject!";
        //out << endl;
        return 1;
    }

    noobjectArray[pos] = toInsert;

    //out << "Inserted noobject at position ";
    //out << pos;
    //out << endl;

    return 0;
}

void universe::getGlobalSettings(){
    settings.texture.used               = settings::Texture::used;
    settings.texture.Name_Underground   = new char[256];
    settings.texture.Name_Background    = new char[256];
    settings.texture.Name_Font          = new char[256];
    strcpy(settings.texture.Name_Underground, settings::Texture::Name_Underground);
    strcpy(settings.texture.Name_Background,  settings::Texture::Name_Background);
    strcpy(settings.texture.Name_Font,        settings::Texture::Name_Font);

    settings.texture.UndergroundNr          = 0;
    settings.texture.BackgroundNr           = 0;
    settings.texture.Underground_Heigh      = 0;

    settings.graphic.useColoredObjs         = settings::Graphic::useColoredObjs;
    settings.graphic.vLines                 = settings::Graphic::vLines;
    settings.graphic.countPointsBuffer      = settings::Graphic::countPointsBuffer;
    settings.graphic.fps                    = settings::Graphic::fps;
    settings.graphic.LoghLevel              = settings::Graphic::LoghLevel;
    settings.graphic.scale                  = settings::Graphic::scale;
    settings.graphic.useGravPlane           = settings::Graphic::useGravPlane;
    //settings.graphic.fMode                  = settings::Graphic::fMode;
    settings.graphic.fProbeSize             = settings::Graphic::fProbeSize;
    settings.graphic.useSFML2overlay        = settings::Graphic::useSFML2overlay;
    settings.graphic.useSphereForObj        = settings::Graphic::useSphereForObj;

    settings.graphic.sphere.countX          = settings::Graphic::Sphere::countX;
    settings.graphic.sphere.countY          = settings::Graphic::Sphere::countY;
    settings.graphic.sphere.mode            = settings::Graphic::Sphere::mode;

    settings.sim_thread.useSimTimeToDump    = settings::Sim::useSimTimeToDump;
    settings.sim_thread.showDebText         = settings::Sim::showDebText;
    settings.sim_thread.useParaProc         = settings::Sim::useParaProc;
    settings.sim_thread.countParaThreads    = settings::Sim::countParaThreads;
    settings.sim_thread.paraLevel           = 0;

    settings.sim.dt                         = settings::Sim::actIntervall;
    settings.sim.quant_Simulation           = settings::Sim::quant_Simulation;

    settings.win.SPSreal                    = settings::Win::SPSreal;

    settings.gravPlane.countX               = settings::gravPlane::countX;
    settings.gravPlane.countY               = settings::gravPlane::countY;
    settings.gravPlane.countZ               = settings::gravPlane::countZ;
    settings.gravPlane.offX                 = settings::gravPlane::offX;
    settings.gravPlane.offY                 = settings::gravPlane::offY;
    settings.gravPlane.offZ                 = settings::gravPlane::offZ;
    settings.gravPlane.stretch              = settings::gravPlane::stretch;
    settings.gravPlane.Ver_Richt            = settings::gravPlane::Ver_Richt;
    settings.gravPlane.MaxFieldAct          = settings::gravPlane::MaxFieldAct;
}

void universe::reserveDrawableArraySpace(\
                              int drawableCountts, \
                              int objectCountts,   \
                              int bodyCountts,     \
                              int quantCountts,    \
                              int fieldCountts,    \
                              int noobjectCountts  \
                              ){

    deleteAllDrawables();

    drawableArray = new drawable*[drawableCountts];
    for (int i=0; i<drawableCountts; i++)
        drawableArray[i] = 0;
    //out << "    ";
    //out << drawableCountts;
    //out << " drawables";
    //out << endl;

    objectArray   = new object*[objectCountts];
    for (int i=0; i<objectCountts; i++)
        objectArray[i] = 0;
    //out << "    ";
    //out << objectCountts;
    //out << " objects";
    //out << endl;

    bodyArray     = new body*[bodyCountts];
    for (int i=0; i<bodyCountts; i++)
        bodyArray[i] = 0;
    //out << "    ";
    //out << bodyCountts;
    //out << " bodies";
    //out << endl;

    quantArray    = new quant*[quantCountts];
    for (int i=0; i<quantCountts; i++)
        quantArray[i] = 0;
    //out << "    ";
    //out << quantCountts;
    //out << " quants";
    //out << endl;

    fieldArray    = new field*[fieldCountts];
    for (int i=0; i<fieldCountts; i++)
        fieldArray[i] = 0;
    //out << "    ";
    //out << fieldCountts;
    //out << " fields";
    //out << endl;

    noobjectArray = new noobject*[noobjectCountts];
    for (int i=0; i<noobjectCountts; i++)
        noobjectArray[i] = 0;
    //out << "    ";
    //out << noobjectCountts;
    //out << " noobjects";
    //out << endl;

    drawableCount = drawableCountts;
    objectCount   = objectCountts;
    bodyCount     = bodyCountts;
    quantCount    = quantCountts;
    fieldCount    = fieldCountts;
    noobjectCount = noobjectCountts;
}

void universe::invokeBeforeSim(){}
void universe::invokeMiddleSim(){}
void universe::invokeAfterSim(){}


void universe::deleteAllDrawables(){
    if (drawableArray != 0){
        //out << "    deleting old drawables ...";
        //out << endl;
        for (int i=0; i<drawableCount; i++)
            if (drawableArray[i])
                delete(drawableArray[i]);
        delete drawableArray;
        delete objectArray;
        delete bodyArray;
        delete quantArray;
        delete fieldArray;
        delete noobjectArray;
    }
}

void universe::deleteAllEffects(){
    if (effectArray != 0){
        for (int i=0; i<effectCount; i++)
            if (effectArray[i] != 0)
                delete (effectArray[i]);

        effectArray = 0;
    }
}


int universe::scrollToArrayEnd(void **a){
    int i=0;
    for (; a[i]!=0; i++){}
    return i;
}
