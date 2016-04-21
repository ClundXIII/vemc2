#include "universe.h"
#include "effect/gravitation.h"
#include "effect/inertia.h"
#include "parser/parser.h"

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
    v0 out << "vcore Library, Version 0.0.1-alpha / 29062015" << eom;
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

    command_helper = new vemc2::parser(this);

    out << "==================done!========================" << eom;
}


universe::universe(int vLevel) :
    out(Vesper::LoggingTypes::server)
{

    verboseLevel = vLevel;

    v0 out << "===============================================" << eom;
    v0 out << "Virtual e = m * c^2 (c) by Simon Michalke, 2014" << eom;
    v0 out << "vcore Library, Version 0.0.1-alpha / 29062015" << eom;
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

    command_helper = new vemc2::parser(this);

    v0 out << "==================done!========================" << eom;
}

universe::~universe(){

    v0 out << "(END) delete() invoked ... cleaning up ..." << eom;

    //cleaning up
    deleteAllDrawables();
    deleteAllEffects();

    v0 out << "... done with cleaning up" << eom;
}

void universe::parse(std::string command){
    command_helper->execute(command);
}

void universe::setVerboseLevel(int l){
    verboseLevel = l;
    v2 out << "set vlevel to " << l << eom;
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
        delete[] effectArray;
    }
    effectArray = new effect*[effectCount+1]; //last element is 0
    for (int i=0; i<(effectCount+1); i++)
        effectArray[i] = 0;
    v2 out << "                                done!" << eom;
    v2 out << "(12)creating simThread            ..." << eom;
    if (!simulationThread){
        v2 out << "(13)deleting old one          ..." << eom;
        delete[] simulationThread;
    }
    simulationThread = new simulation::sim_thread(this);
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
    if (!simulationThread){
        v1 out << "cannot run, simulationThread=0 in universe.cpp::run()" << eom;
        return;
    }

    try{
        simulationThread->unpause();
        simulationThread->run();
    }
    catch (char* errorstr){
        v0 out << "error in universe.cpp::run():" << eom;
        v0 out << "      ->" << errorstr << eom;
    }
    catch (...){
        v0 out << "unknown error in universe.cpp::run()" << eom;
    }
}

void universe::run(bdt secondsToRun){


    if (!simulationThread){
        v1 out << "cannot run, simulationThread=0 in universe.cpp::run()" << eom;
        return;
    }

    //set the time when to stop
    simulationThread->time_to_stop = settings.sim.global_time + secondsToRun;

    try{
        simulationThread->run();
    }
    catch (char* errorstr){
        v0 out << "error in universe.cpp::run():" << eom;
        v0 out << "      ->" << errorstr << eom;
    }
    catch (...){
        v0 out << "unknown error in universe.cpp::run()" << eom;
    }
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
        effectCount = 2;
        effectArray = new effect*[effectCount+1]; //last element is 0
        effectArray[0] = (simulation::effect*) new simulation::gravitation(this);
        effectArray[1] = (simulation::effect*) new simulation::inertia(this);
        effectArray[2] = 0;
        fieldCount = 1;
        fieldArray = new simulation::field*[fieldCount+1]; //last element is 0
        //fieldArray[0] = (simulation::field*) new simulation::Gfield(this);
        fieldArray[1] = 0;
        fields.G = new simulation::Gfield(this);
       break;

      case vemc2::quantumSimulation:
        setObjectType(vemc2::t_quant);
       break;

      case vemc2::feynmanSimulation:
        setObjectType(vemc2::t_quant);
       break;

      case vemc2::bodySimulation:
        setObjectType(vemc2::t_body);
        effectCount = 2;
        effectArray = new effect*[effectCount+1]; //last element is 0
        effectArray[0] = (simulation::effect*) new simulation::gravitation(this);
        effectArray[1] = (simulation::effect*) new simulation::inertia(this);
        effectArray[2] = 0;
       break;

      default:
        ///TODO: add error!
       break;

    }

    return 0;
}

int universe::insertEffect(vemc2::simulation::effect *effectToIns){


    effect** tmpEarray = effectArray;

    effectCount++;
    effectArray = new effect*[effectCount+1]; //last element is 0

    int i=0;
    int nextEffectToIns =0;

    bool inserted = false;

    for (;i<effectCount; i++){
        if (inserted || (effectToIns->getPriority() >= tmpEarray[nextEffectToIns]->getPriority())){
            effectArray[i]=tmpEarray[nextEffectToIns];
            nextEffectToIns++;
            v2 out << "inserted original at "<< i << Vesper::LoggingTypes::eom;
        }
        else{
            effectArray[i] = effectToIns;
            v2 out << "inserted new at "<< i << Vesper::LoggingTypes::eom;
            inserted = true;
        }

    }

    //delete tmpEarray;

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
        v0 out << "insertObject returned " << ret;
        v0 out << " in universe.cpp::insertQuant" << eom;
        return 2;
    }


    int pos = sTAE( (void**)quantArray);
    if (pos >= (quantCount - 1) ){
        v0 out << "quantCount exceed limits in universe.cpp::insertQuant!" << eom;
        return 1;
    }

    quantArray[pos] = toInsert;

    v1 out << "Inserted quant at position " << pos << eom;

    return 0;
}

int universe::insertField(vemc2::simulation::field *toInsert){

    int ret;

    //first insert this in the mother class array:
    ret = insertDrawable( (drawable*) toInsert);
    if (ret != 0){
        v0 out << "insertDrawable returned " << ret << " in universe.cpp::insertField" << eom;
        return 2;
    }


    int pos = sTAE( (void**)fieldArray);
    if (pos >= (fieldCount - 1) ){
        v0 out << "fieldCount exceed limits in universe.cpp::insertField!" << eom;
        return 1;
    }

    fieldArray[pos] = toInsert;

    v1 out << "Inserted field at position " << pos << eom;


    return 0;
}

int universe::insertNoobject(vemc2::simulation::noobject *toInsert){

    int ret;

    //first insert this in the mother class array:
    ret = insertDrawable( (drawable*) toInsert);
    if (ret != 0){
        v0 out << "insertDrawable returned " << ret << " in universe.cpp::insertNoobject" << eom;
        return 2;
    }


    int pos = sTAE( (void**)noobjectArray);
    if (pos >= (noobjectCount - 1) ){
        v0 out << "noobjectCount exceed limits in universe.cpp::insertNoobject!" << eom;
        return 1;
    }

    noobjectArray[pos] = toInsert;

    v1 out << "Inserted noobject at position " << pos << eom;

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
    settings.texture.under_heigh            = 0;

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
    settings.sim.global_time                = 0;
    settings.sim.quant_Simulation           = settings::Sim::quant_Simulation;
    settings.sim.DeadZone                   = 0.2;

    settings.sim.NatConst.G                 = 0.0000000000667384;
    //settings.sim.NatConst.G                 = 0.667384; //test G (aka y "gamma")

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
    v2 out << "    " << drawableCountts << " drawables" << eom;

    objectArray   = new object*[objectCountts];
    for (int i=0; i<objectCountts; i++)
        objectArray[i] = 0;
    v2 out << "    " << objectCountts << " objects" << eom;

    bodyArray     = new body*[bodyCountts];
    for (int i=0; i<bodyCountts; i++)
        bodyArray[i] = 0;
    v2 out << "    " << bodyCountts << " bodies" << eom;

    quantArray    = new quant*[quantCountts];
    for (int i=0; i<quantCountts; i++)
        quantArray[i] = 0;
    v2 out << "    " << quantCountts << " quants" << eom;

    fieldArray    = new field*[fieldCountts];
    for (int i=0; i<fieldCountts; i++)
        fieldArray[i] = 0;
    v2 out << "    " << fieldCountts << " fields" << eom;

    noobjectArray = new noobject*[noobjectCountts];
    for (int i=0; i<noobjectCountts; i++)
        noobjectArray[i] = 0;
    v2 out << "    " << noobjectCountts << " noobjects" << eom;

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
        v1 out << "    deleting old drawables ..." << eom;
        for (int i=0; i<drawableCount; i++)
            if (drawableArray[i])
                delete(drawableArray[i]);
        delete[] drawableArray;
        delete[] objectArray;
        delete[] bodyArray;
        delete[] quantArray;
        delete[] fieldArray;
        delete[] noobjectArray;
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
