#include "universe.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace Vesper::LoggingType;
using namespace vemc2;
using namespace vemc2::simulation;
using namespace vemc2::settings;

universe::universe(){
    Vesper::Vout::init();
    out = new Vesper::Logging(Vesper::LoggingType::server);
    *out << "===============================================";
    *out << 123;
    *out << endl;
    *out << "Virtual e = m * c^2 (c) by Simon Michalke, 2014";
    *out << endl;
    *out << "vcore Library, Version 0.0.01-pre / 23042014";
    *out << endl;
    *out << "Have a lot of fun ...                ";
    *out << endl;
    *out << "    creating new universe         ...";
    *out << endl;
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

    update();
}

universe::~universe(){

    *out << "(END) delete() invoked ... cleaning up ...";
    *out << endl;

    //cleaning up
    deleteAllDrawables();
    deleteAllEffects();

    *out << "If you see this, there wasn't a single";
    *out << endl;
    *out << "SEGFAULT ... HORAAAAYYYY!!!!";
    *out << endl;
    *out << "";
    *out << endl;
    *out << "World sucessfully deleted!";
    *out << endl;
}

void universe::update(){
    *out << "(00)update() invoked!                ";
    *out << endl;
    *out << "(01)getting global settings       ...";
    *out << endl;
    getGlobalSettings();
    *out << "                                done!";
    *out << endl;
    *out << "(02)reserving space for drawables ...";
    *out << endl;
    resetArrays();
    *out << "                                done!";
    *out << endl;
    *out << "(10)creating simulation           ...";
    *out << endl;
    *out << "(11)setting up effects            ...";
    *out << endl;
    if (effectArray != 0){ //we have to delete the old effects first!
        *out << "    deleting old effects ...";
        *out << endl;
        for (int i=0; i<effectCount; i++){
            delete effectArray[i];
        }
        delete effectArray;
    }
    effectArray = new effect*[effectCount];
    for (int i=0; i<effectCount; i++)
        effectArray[i] = 0;
    *out << "                                done!";
    *out << endl;
    *out << "(12)creating simThread            ...";
    *out << endl;
    *out << "                                done!";
    *out << endl;

    *out << "  sucessfully created a new universe!";
    *out << endl;
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

void universe::start(){

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
    ///TODO: add reserve Array space invoking here

    return 0;
}

void universe::setObjectType(objectType typets){
    useForSimulation = typets;
}

/**
 * just a quick define to get a nicer code within
 * the *insert() functions ;-)
 */
#define sTAE(a) scrollToArrayEnd(a)

int universe::insertDrawable(vemc2::simulation::drawable *toInsert){

    int pos = sTAE( (void**)drawableArray);
    if (pos >= (drawableCount - 1) ){
        *out << "drawableCount exceed limits in universe.cpp::insertDrawable!";
        *out << endl;
        return 1;
    }

    drawableArray[pos] = toInsert;

    *out << "Inserted drawable at position ";
    *out << pos;
    *out << endl;

    return 0;
}

int universe::insertObject(vemc2::simulation::object *toInsert){

    int ret;

    //first insert this in the mother class array:
    ret = insertDrawable( (drawable*) toInsert);
    if (ret != 0){
        *out << "insertDrawable returned ";
        *out << ret;
        *out << " in universe.cpp::insertObject";
        *out << endl;
        return 2;
    }


    int pos = sTAE( (void**)objectArray);
    if (pos >= (objectCount - 1) ){
        *out << "objectCount exceed limits in universe.cpp::insertObject!";
        *out << endl;
        return 1;
    }

    objectArray[pos] = toInsert;

    *out << "Inserted object at position ";
    *out << pos;
    *out << endl;

    return 0;
}

int universe::insertBody(vemc2::simulation::body *toInsert){

    int ret;

    //first insert this in the mother class array:
    ret = insertObject( (object*) toInsert);
    if (ret != 0){
        *out << "insertObject returned ";
        *out << ret;
        *out << " in universe.cpp::insertBody";
        *out << endl;
        return 2;
    }


    int pos = sTAE( (void**)bodyArray);
    if (pos >= (bodyCount - 1) ){
        *out << "bodyCount exceed limits in universe.cpp::insertBody!";
        *out << endl;
        return 1;
    }

    bodyArray[pos] = toInsert;

    *out << "Inserted body at position ";
    *out << pos;
    *out << endl;

    return 0;
}

int universe::insertQuant(vemc2::simulation::quant *toInsert){

    int ret;

    //first insert this in the mother class array:
    ret = insertObject( (object*) toInsert);
    if (ret != 0){
        *out << "insertObject returned ";
        *out << ret;
        *out << " in universe.cpp::insertQuant";
        *out << endl;
        return 2;
    }


    int pos = sTAE( (void**)quantArray);
    if (pos >= (quantCount - 1) ){
        *out << "quantCount exceed limits in universe.cpp::insertQuant!";
        *out << endl;
        return 1;
    }

    quantArray[pos] = toInsert;

    *out << "Inserted quant at position ";
    *out << pos;
    *out << endl;

    return 0;
}

int universe::insertField(vemc2::simulation::field *toInsert){

    int ret;

    //first insert this in the mother class array:
    ret = insertDrawable( (drawable*) toInsert);
    if (ret != 0){
        *out << "insertDrawable returned ";
        *out << ret;
        *out << " in universe.cpp::insertField";
        *out << endl;
        return 2;
    }


    int pos = sTAE( (void**)fieldArray);
    if (pos >= (fieldCount - 1) ){
        *out << "fieldCount exceed limits in universe.cpp::insertField!";
        *out << endl;
        return 1;
    }

    fieldArray[pos] = toInsert;

    *out << "Inserted field at position ";
    *out << pos;
    *out << endl;


    return 0;
}

int universe::insertNoobject(vemc2::simulation::noobject *toInsert){

    int ret;

    //first insert this in the mother class array:
    ret = insertDrawable( (drawable*) toInsert);
    if (ret != 0){
        *out << "insertDrawable returned ";
        *out << ret;
        *out << " in universe.cpp::insertNoobject";
        *out << endl;
        return 2;
    }


    int pos = sTAE( (void**)noobjectArray);
    if (pos >= (noobjectCount - 1) ){
        *out << "noobjectCount exceed limits in universe.cpp::insertNoobject!";
        *out << endl;
        return 1;
    }

    noobjectArray[pos] = toInsert;

    *out << "Inserted noobject at position ";
    *out << pos;
    *out << endl;

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
    *out << "    ";
    *out << drawableCountts;
    *out << " drawables";
    *out << endl;

    objectArray   = new object*[objectCountts];
    for (int i=0; i<objectCountts; i++)
        objectArray[i] = 0;
    *out << "    ";
    *out << objectCountts;
    *out << " objects";
    *out << endl;

    bodyArray     = new body*[bodyCountts];
    for (int i=0; i<bodyCountts; i++)
        bodyArray[i] = 0;
    *out << "    ";
    *out << bodyCountts;
    *out << " bodies";
    *out << endl;

    quantArray    = new quant*[quantCountts];
    for (int i=0; i<quantCountts; i++)
        quantArray[i] = 0;
    *out << "    ";
    *out << quantCountts;
    *out << " quants";
    *out << endl;

    fieldArray    = new field*[fieldCountts];
    for (int i=0; i<fieldCountts; i++)
        fieldArray[i] = 0;
    *out << "    ";
    *out << fieldCountts;
    *out << " fields";
    *out << endl;

    noobjectArray = new noobject*[noobjectCountts];
    for (int i=0; i<noobjectCountts; i++)
        noobjectArray[i] = 0;
    *out << "    ";
    *out << noobjectCountts;
    *out << " noobjects";
    *out << endl;

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
        *out << "    deleting old drawables ...";
        *out << endl;
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
