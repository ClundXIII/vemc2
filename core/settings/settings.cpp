#include "settings.h"

#include "settingdefines.h"

#include <string.h>
#include <iostream>
#include <fstream>

using namespace vemc2::settings;

//#Yolo
char tempisdeuryfri[]="./res/underground.bmp";
char temppswiaeufro[]="./res/background.bmp";
char tempresskjefhe[]="./res/UbuntuMono-B.ttf";

bool   Texture::used = false;
char*  Texture::Name_Underground = (char*)"\0";
char*  Texture::Name_Background  = (char*)"\0";
char*  Texture::Name_Font        = (char*)"\0";
int    Texture::UndergroundNr = 0;
int    Texture::BackgroundNr = 0;
float  Texture::Underground_Heigh = -100;

bool   Grafik::useColoredObjs = true;
bool   Grafik::vLines = false;
int    Grafik::countPointsBuffer = (10*60*10*7); //10 mins, 2 Objects
int    Grafik::fps = 0;
int    Grafik::LoghLevel = 0;
double Grafik::scale = 1;
bool   Grafik::useGravPlane = true;
//vemc2::Field_Mode Grafik::fMode = vemc::fPoints_2D;
bdt    Grafik::fProbeSize = 100000000000;
bool   Grafik::useSFML2overlay = false;
bool   Grafik::useSphereForObj = true;

int    Grafik::Sphere::countX = 20;
int    Grafik::Sphere::countY = 10;
int    Grafik::Sphere::mode   =  0;

float  Sim::actIntervall = 0.3;
bool   Sim::useSimTimeToDump = false;
bool   Sim::showDebText = true;
bool   Sim::useParaProc = false;
int    Sim::countParaThreads = 4;
bool   Sim::quant_Simulation = false;

double Win::SPSreal = 1000;

int    gravPlane::countX = 200;
int    gravPlane::countY = 200;
int    gravPlane::countZ = 200;
int    gravPlane::offX   =-100;
int    gravPlane::offY   =-100;
int    gravPlane::offZ   =-100;
float  gravPlane::stretch=   1;
Field_Dir gravPlane::Ver_Richt = minusY;
int    gravPlane::MaxFieldAct = 0; //unlimeted


int vemc2::settings::init(std::fstream *f, int argc, char** argv){

    ///init:
    Texture::used = true;//true;
    Texture::Name_Underground = tempisdeuryfri;
    Texture::Name_Background  = temppswiaeufro;
    Texture::Name_Font        = tempresskjefhe;
    Texture::Underground_Heigh = -100;

    Grafik::useColoredObjs = true;
    Grafik::vLines = false;
    Grafik::countPointsBuffer = (10*60*10*3); //10 mins, 3 Objects
    Grafik::fps = 15;
    Grafik::LoghLevel = 3;// 0 => no logarhythmic visualisation
    Grafik::scale = 1;
    Grafik::useGravPlane = true;
    //Grafik::fMode = vemc::fLines_3D;
    Grafik::fProbeSize = 6000000000;
    //Grafik::fProbeSize = 50000000000;
    Grafik::useSFML2overlay = true;
    Grafik::useSphereForObj = false;

    Grafik::Sphere::countX = 20;
    Grafik::Sphere::countY = 10;
    Grafik::Sphere::mode   =  0;

    Sim::actIntervall = 0.3;
    Sim::useSimTimeToDump = false;
    Sim::showDebText = true;
    Sim::useParaProc = false;
    Sim::countParaThreads = 4;
    Sim::quant_Simulation = false;

    Win::SPSreal = 1000;


    /*gravPlane::countX =  50;
    gravPlane::countY =   1;
    gravPlane::countZ =  50;
    gravPlane::offX   =-125; //offset without stretch
    gravPlane::offY   =   0;
    gravPlane::offZ   =-125;
    gravPlane::stretch=   5;*/

    gravPlane::countX =  5;
    gravPlane::countY =  5;
    gravPlane::countZ =  5;
    gravPlane::offX   =-10; //offset without stretch
    gravPlane::offY   =-10;
    gravPlane::offZ   =-10;
    gravPlane::stretch=  5;
    gravPlane::Ver_Richt= FVec;
    gravPlane::MaxFieldAct = 12;

    char  InputS[256];
    char *tempString = new char[256];

    std::string tempSa;
    std::string tempSb;

    if (!f->good()) return 1;

    int Line=0;

    while (true){
        Line++;
        f->getline(InputS, sizeof(InputS));
        if (f->eof()) break;
        if (!f->good()){
            std::cout << "!f.good()" << std::endl;
            f->clear();
            break;
        }

        if  (InputS[0] ==  0 )  continue; //empty Line
        if  (InputS[0] == '#')  continue; //comment
        if ((InputS[0] == '/') &&         //C-like comment
            (InputS[1] == '/')) continue; //--> double '/'

        //delete(tempString); //activate this to avoid memory lecks
        tempString = getRest(InputS);

             if (compareSetting(InputS, "Texture::used"))              {Texture::used            = setBool(tempString);}
        else if (compareSetting(InputS, "Texture::Name_Underground"))  {/*setString(tempString, Texture::Name_Underground);*/}
        else if (compareSetting(InputS, "Texture::Name_Background"))   {}
        else if (compareSetting(InputS, "Texture::Name_Font"))         {}
        else if (compareSetting(InputS, "Texture::UndergroundNr"))     {}
        else if (compareSetting(InputS, "Texture::BackgroundNr"))      {}
        else if (compareSetting(InputS, "Texture::Underground_Heigh")) {}

        else if (compareSetting(InputS, "Grafik::useColoredObjs"))     {Grafik::useColoredObjs   = setBool(tempString);}
        else if (compareSetting(InputS, "Grafik::vLines"))             {Grafik::vLines           = setBool(tempString);}
        else if (compareSetting(InputS, "Grafik::countPointsBuffer"))  {}
        else if (compareSetting(InputS, "Grafik::fps"))                {}
        else if (compareSetting(InputS, "Grafik::LoghLevel"))          {}
        else if (compareSetting(InputS, "Grafik::scale"))              {}
        else if (compareSetting(InputS, "Grafik::useGravPlane"))       {Grafik::useGravPlane     = setBool(tempString);}
        else if (compareSetting(InputS, "Grafik::fMode"))              {}
        else if (compareSetting(InputS, "Grafik::fProbeSize"))         {}
        else if (compareSetting(InputS, "Grafik::useSFML2overlay"))    {Grafik::useSFML2overlay  = setBool(tempString);}
        else if (compareSetting(InputS, "Grafik::useSphereForObj"))    {Grafik::useSphereForObj  = setBool(tempString);}

        else if (compareSetting(InputS, "Grafik::Sphere::countX"))     {}
        else if (compareSetting(InputS, "Grafik::Sphere::countY"))     {}
        else if (compareSetting(InputS, "Grafik::Sphere::mode"))       {}

        else if (compareSetting(InputS, "Sim::actIntervall"))          {}
        else if (compareSetting(InputS, "Sim::useSimTimeToDump"))      {Sim::useSimTimeToDump    = setBool(tempString);}
        else if (compareSetting(InputS, "Sim::showDebText"))           {Sim::showDebText         = setBool(tempString);}
        else if (compareSetting(InputS, "Sim::useParaProc"))           {Sim::useParaProc         = setBool(tempString);}
        else if (compareSetting(InputS, "Sim::countParaThreads"))      {}
        else if (compareSetting(InputS, "Sim::quant_Simulation"))      {Sim::quant_Simulation    = setBool(tempString);}

        else if (compareSetting(InputS, "Win::SPSreal"))               {}

        else if (compareSetting(InputS, "gravPlane::countX"))          {}
        else if (compareSetting(InputS, "gravPlane::countY"))          {}
        else if (compareSetting(InputS, "gravPlane::countZ"))          {}
        else if (compareSetting(InputS, "gravPlane::offX"))            {}
        else if (compareSetting(InputS, "gravPlane::offY"))            {}
        else if (compareSetting(InputS, "gravPlane::offZ"))            {}
        else if (compareSetting(InputS, "gravPlane::stretch"))         {}
        else if (compareSetting(InputS, "gravPlane::Ver_Richt"))       {}
        else if (compareSetting(InputS, "gravPlane::MaxFieldAct"))     {}

        else     std::cout << "Cant recognize Setting in settings.cpp::init(): " << InputS << " in Line " << Line << std::endl;
    }

    ///TODO activate the following:
    //if (!f->good()) return 2;
    f->close();


    //Parameter detection:
    if (argc > 1){
        for (int i=1; i<argc; i++){
            if (argv[i][0] == '-' && (argv[i][0] != '-')){//we got a single '-' started parameter --> the simplelst one
                if (argv[i][2] != '\0') std::cout << "error in settings.cpp::init()" << std::endl;
                else{
                    std::fstream g;
                    switch (argv[i][1]){
                        case 'p': //print settings
                            if ( (argv[i+1][0] == '\0') || (argv[i+1][0] == '-') ){
                                g.open("config.ini", std::ios::out | std::ios::trunc);
                                settings::printDefault(&g);
                            }
                            else{ //we got a specific filename
                                g.open(argv[i+1], std::ios::out | std::ios::trunc);
                                settings::printDefault(&g);
                                i++;
                            }
                          break;
                        default:
                            std::cout << "couldn't recognize the argument!" << std::endl;
                    }
                }
            }
        }
    }
    else
        std::cout << "no armguments given --> continue" << std::endl;

    return 0;
}


int vemc2::settings::printDefault(std::fstream *f){
    if (!f->good()) return 1;

    *f << "#Settings file for vemc2" << std::endl;
    *f << "#standard settings (automatic generated)" << std::endl;
    *f << "#Generator v 0.0.01 date: 22012014" << std::endl;
    *f << "" << std::endl;
    *f << "#start with namespace Textures:" << std::endl;
    *f << "Texture::used=true" << std::endl;
    *f << "Texture::Name_Underground=\"./res/underground.bmp\"" << std::endl;
    *f << "Texture::Name_Background=\"./res/background.bmp\"" << std::endl;
    *f << "Texture::Name_Font=\"./res/UbuntuMono-B.ttf\"" << std::endl;
    *f << "Texture::Underground_Heigh=-100" << std::endl;
    *f << "" << std::endl;
    *f << "#go on with namespace Grafik:" << std::endl;
    *f << "Grafik::useColoredObjs=true" << std::endl;
    *f << "Grafik::vLines=false" << std::endl;
    *f << "Grafik::countPointsBuffer=18000" << std::endl;
    *f << "Grafik::fps=15" << std::endl;
    *f << "Grafik::LoghLevel=3" << std::endl;
    *f << "Grafik::scale=1" << std::endl;
    *f << "Grafik::useGravPlane=true" << std::endl;
    *f << "Grafik::fMode=vemc::fLines_3D" << std::endl;
    *f << "Grafik::fProbeSize=6000000000" << std::endl;
    *f << "Grafik::useSFML2overlay=true" << std::endl;
    *f << "Grafik::useSphereForObj=true" << std::endl;
    *f << "Grafik::Sphere::countX=20" << std::endl;
    *f << "Grafik::Sphere::countY=10" << std::endl;
    *f << "Grafik::Sphere::mode=0" << std::endl;
    *f << "" << std::endl;
    *f << "#go on with namespace Sim:" << std::endl;
    *f << "Sim::actIntervall=0.3" << std::endl;
    *f << "Sim::useSimTimeToDump=false" << std::endl;
    *f << "Sim::showDebText=true" << std::endl;
    *f << "Sim::useParaProc=false" << std::endl;
    *f << "Sim::countParaThreads=4" << std::endl;
    *f << "Sim::quant_Simulation=false" << std::endl;
    *f << "" << std::endl;
    *f << "#one lonely Win Settings:" << std::endl;
    *f << "Win::SPSreal=1000" << std::endl;
    *f << "" << std::endl;
    *f << "#last but not least: the gravitation plane:" << std::endl;
    *f << "gravPlane::countX=5" << std::endl;
    *f << "gravPlane::countY=5" << std::endl;
    *f << "gravPlane::countZ=5" << std::endl;
    *f << "gravPlane::offX=-10" << std::endl;
    *f << "gravPlane::offY=-10" << std::endl;
    *f << "gravPlane::offZ=-10" << std::endl;
    *f << "gravPlane::stretch=5" << std::endl;
    *f << "gravPlane::Ver_Richt=FVec" << std::endl;
    *f << "gravPlane::MaxFieldAct=12" << std::endl;
    *f << "" << std::endl;

    return 0;
}
