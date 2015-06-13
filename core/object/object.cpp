#include "./object.h"

#include <iostream>
#include <iomanip>
#include <vector>

using namespace vemc2::simulation;

object::object(){
    posX1 = 0;
    posX2 = 0;
    posX3 = 0;

    setDataNull();

    return;
}

object::object(object *toCopy){
    posX1 = toCopy->getX1();
    posX2 = toCopy->getX2();
    posX3 = toCopy->getX3();

    mass = toCopy->getMass();

    setDataNull();
}

object::object(bdt posX1ts, bdt posX2ts, bdt posX3ts, bdt massts){
    posX1 = posX1ts;
    posX2 = posX2ts;
    posX3 = posX3ts;

    mass = massts;

    setDataNull();
}

object::~object(){
    //dtor
}

void object::draw(){

    #ifndef VEMC2_COMPILE_NOGL

    double PDick = 0.01*((double)mass);

    /*
    if (Settings::Grafik::LoghLevel == 1){ //natürlich (sprich e)
        PDick = log(mass);
    }
    else if (Settings::Grafik::LoghLevel == 2){ //2'er
        PDick = log2(mass);
    }
    else if (Settings::Grafik::LoghLevel == 3){ //10'er
        PDick = log10(mass);
    }
    */

    glTranslatef(Settings::Grafik::scale*Pos_X, Settings::Grafik::scale*Pos_Y, Settings::Grafik::scale*Pos_Z);

    glRotatef(customRot, 0.f, 1.f, 0.f);

    if (!Settings::Grafik::useSphereForObj){
        glBegin(GL_TRIANGLES);

        /*
        glVertex3f(-PDick,  0, -PDick);
        glVertex3f(-PDick,  0,  PDick);
        glVertex3f( PDick,  0,  PDick);
        glVertex3f( PDick,  0, -PDick);

        glVertex3f( 0, -PDick,-PDick);
        glVertex3f( 0,  PDick,-PDick);
        glVertex3f( 0,  PDick, PDick);
        glVertex3f( 0, -PDick, PDick);

        glVertex3f(-PDick, -PDick,  0);
        glVertex3f(-PDick,  PDick,  0);
        glVertex3f( PDick,  PDick,  0);
        glVertex3f( PDick, -PDick,  0);
        */

        if (Settings::Grafik::useColoredObjs){
            //obere Pyramide
            glColor3f(0.f, 0.f, 1.f);
            glVertex3f( 0.5*PDick,     0,  0.5*PDick);
            glColor3f(0.f, 1.f, 0.f);
            glVertex3f( 0.5*PDick,     0, -0.5*PDick);
            glColor3f(1.f, 0.f, 0.f);
            glVertex3f(         0, 0.7*PDick,          0);

            glColor3f(0.f, 1.f, 0.f);
            glVertex3f( 0.5*PDick,     0, -0.5*PDick);
            glColor3f(1.f, 1.f, 0.f);
            glVertex3f(-0.5*PDick,     0, -0.5*PDick);
            glColor3f(1.f, 0.f, 0.f);
            glVertex3f(         0, 0.7*PDick,          0);

            glColor3f(1.f, 1.f, 0.f);
            glVertex3f(-0.5*PDick,     0, -0.5*PDick);
            glColor3f(1.f, 0.f, 1.f);
            glVertex3f(-0.5*PDick,     0,  0.5*PDick);
            glColor3f(1.f, 0.f, 0.f);
            glVertex3f(         0, 0.7*PDick,          0);

            glColor3f(1.f, 0.f, 1.f);
            glVertex3f(-0.5*PDick,     0,  0.5*PDick);
            glColor3f(0.f, 0.f, 1.f);
            glVertex3f( 0.5*PDick,     0,  0.5*PDick);
            glColor3f(1.f, 0.f, 0.f);
            glVertex3f(         0, 0.7*PDick,          0);

            //untere Pyramide
            glColor3f(0.f, 0.f, 1.f);
            glVertex3f( 0.5*PDick,     0,  0.5*PDick);
            glColor3f(0.f, 1.f, 0.f);
            glVertex3f( 0.5*PDick,     0, -0.5*PDick);
            glColor3f(1.f, 0.f, 0.5f);
            glVertex3f(         0,-0.7*PDick,          0);

            glColor3f(0.f, 1.f, 0.f);
            glVertex3f( 0.5*PDick,     0, -0.5*PDick);
            glColor3f(1.f, 1.f, 0.f);
            glVertex3f(-0.5*PDick,     0, -0.5*PDick);
            glColor3f(1.f, 0.f, 0.5f);
            glVertex3f(         0,-0.7*PDick,          0);

            glColor3f(1.f, 1.f, 0.f);
            glVertex3f(-0.5*PDick,     0, -0.5*PDick);
            glColor3f(1.f, 0.f, 1.f);
            glVertex3f(-0.5*PDick,     0,  0.5*PDick);
            glColor3f(1.f, 0.f, 0.5f);
            glVertex3f(         0,-0.7*PDick,          0);

            glColor3f(1.f, 0.f, 1.f);
            glVertex3f(-0.5*PDick,     0,  0.5*PDick);
            glColor3f(0.f, 0.f, 1.f);
            glVertex3f( 0.5*PDick,     0,  0.5*PDick);
            glColor3f(1.f, 0.f, 0.5f);
            glVertex3f(         0,-0.7*PDick,          0);
        }
        else{
            //obere Pyramide
            glColor3f(0.f, 0.f, 1.f);
            glVertex3f( 0.5*PDick,     0,  0.5*PDick);
            glVertex3f( 0.5*PDick,     0, -0.5*PDick);
            glVertex3f(         0, 0.7*PDick,          0);

            glVertex3f( 0.5*PDick,     0, -0.5*PDick);
            glVertex3f(-0.5*PDick,     0, -0.5*PDick);
            glVertex3f(         0, 0.7*PDick,          0);

            glVertex3f(-0.5*PDick,     0, -0.5*PDick);
            glVertex3f(-0.5*PDick,     0,  0.5*PDick);
            glVertex3f(         0, 0.7*PDick,          0);

            glVertex3f(-0.5*PDick,     0,  0.5*PDick);
            glVertex3f( 0.5*PDick,     0,  0.5*PDick);
            glVertex3f(         0, 0.7*PDick,          0);

            //untere Pyramide
            glVertex3f( 0.5*PDick,     0,  0.5*PDick);
            glVertex3f( 0.5*PDick,     0, -0.5*PDick);
            glVertex3f(         0,-0.7*PDick,          0);

            glVertex3f( 0.5*PDick,     0, -0.5*PDick);
            glVertex3f(-0.5*PDick,     0, -0.5*PDick);
            glVertex3f(         0,-0.7*PDick,          0);

            glVertex3f(-0.5*PDick,     0, -0.5*PDick);
            glVertex3f(-0.5*PDick,     0,  0.5*PDick);
            glVertex3f(         0,-0.7*PDick,          0);

            glVertex3f(-0.5*PDick,     0,  0.5*PDick);
            glVertex3f( 0.5*PDick,     0,  0.5*PDick);
            glVertex3f(         0,-0.7*PDick,          0);
        }
        glEnd();
    }
    else{
        GLUquadricObj *gluObj = gluNewQuadric();
        gluSphere(gluObj, 0.5*PDick, 20, 10);
    }

    if (senkrechteStriche){
    glBegin(GL_QUADS);
    //Zeichne die Senkrechten Striche
        glColor3f(1.f, 0.5f, 0.5f);

        glVertex3f( LinDicke, -Pos_Y, 0.f);
        glVertex3f(-LinDicke, -Pos_Y, 0.f);
        glVertex3f(-LinDicke,    0.f, 0.f);
        glVertex3f( LinDicke,    0.f, 0.f);

        glVertex3f(0.f, -Pos_Y,  LinDicke);
        glVertex3f(0.f, -Pos_Y, -LinDicke);
        glVertex3f(0.f,    0.f, -LinDicke);
        glVertex3f(0.f,    0.f,  LinDicke);

    glEnd();
    }

    glRotatef(-customRot, 0.f, 1.f, 0.f);

    glTranslatef(Settings::Grafik::scale*(-Pos_X), Settings::Grafik::scale*(-Pos_Y), Settings::Grafik::scale*(-Pos_Z));

    #endif
}


void object::drawField(){

}


bdt object::getMass(){return mass;}
vemc2::mymath::vec3bdt object::getX(){
    vemc2::mymath::vec3bdt retVec;
    retVec[0] = getX1();
    retVec[1] = getX2();
    retVec[2] = getX3();
    return retVec;
}
bdt object::getX1()  {return posX1;}
bdt object::getX2()  {return posX2;}
bdt object::getX3()  {return posX3;}

void object::setMass(bdt massts){mass  = massts;}
void object::setX1(bdt X1ts)    {posX1 = X1ts;}
void object::setX2(bdt X2ts)    {posX2 = X2ts;}
void object::setX3(bdt X3ts)    {posX3 = X3ts;}

void object::setDataNull(){
    data.F.X1 = 0;
    data.F.X2 = 0;
    data.F.X3 = 0;

    data.a.X1 = 0;
    data.a.X2 = 0;
    data.a.X3 = 0;

    data.v.X1 = 0;
    data.v.X2 = 0;
    data.v.X3 = 0;
}

void object::addF(std::vector<bdt> Fta){
    data.F.X1 += Fta[0];
    data.F.X2 += Fta[1];
    data.F.X3 += Fta[2];
}

void object::addA(std::vector<bdt> Ata){
    data.a.X1 += Ata[0];
    data.a.X2 += Ata[1];
    data.a.X3 += Ata[2];
}

void object::addV(std::vector<bdt> Vta){
    data.v.X1 += Vta[0];
    data.v.X2 += Vta[1];
    data.v.X3 += Vta[2];
}

soa_object* object::soa_generate(object **objs, int count){
    soa_object *newSOA = new soa_object;

    newSOA->element_count = count;

    newSOA->posX1 = new bdt[count];
    newSOA->posX2 = new bdt[count];
    newSOA->posX3 = new bdt[count];

    for (int i=0; i<count; i++){

    }

    return newSOA;
}
