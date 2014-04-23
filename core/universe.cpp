#include "universe.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace vemc2;
using namespace std;

universe::universe(){
    cout << "    creating new universe         ..."   << endl;
    cout << "(01)getting global settings       ..."   << endl;
    getGlobalSettings();
    cout << "                                  done!" << endl;
    cout << "(02)reserving space for drawables ..."   << endl;
    reservDrawableArraySpace(\
                                      1024, //drawableCount
                                      1024, //objectCount
                                      1024, //bodyCount
                                      1024, //quantCount
                                      128,  //fieldCount
                                      16    //noobjectCount
                                      );
    cout << "                                  done!" << endl;
    cout << "(11)creating simulation           ..."   << endl;
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
    settings.texture.used              = settings::Texture::used;
    settings.texture.Name_Underground  = new char[256];
    settings.texture.Name_Background   = new char[256];
    settings.texture.Name_Font         = new char[256];
    strcpy(settings.texture.Name_Underground, settings::Texture::Name_Underground);
    strcpy(settings.texture.Name_Background,  settings::Texture::Name_Background);
    strcpy(settings.texture.Name_Font,        settings::Texture::Name_Font);
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
    cout << "    " << quantCount << " quant" << endl;

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

