#include "./object.h"

#include <iostream>
#include <iomanip>

using namespace vemc2::simulation;

object **GLOBALOBJECTS;

object::object(){
    return;
}

object::object(object *toCopy){
    posX1 = toCopy->getX1();
    posX2 = toCopy->getX2();
    posX3 = toCopy->getX3();

    mass = toCopy->getMass();
}

object::object(bdt posX1ts, bdt posX2ts, bdt posX3ts, bdt massts){
    posX1 = posX1;
    posX2 = posX1;
    posX3 = posX3;

    mass = massts;
}

/*object::object(bdt PosX, bdt PosY, bdt PosZ, bdt Massts, vector *Speedts){
    Pos_X = PosX;
    Pos_Y = PosY;
    Pos_Z = PosZ;

    mass = Massts;

    actSpeed.X = Speedts->X;
    actSpeed.Y = Speedts->Y;
    actSpeed.Z = Speedts->Z;
}*/

object::~object(){
    //dtor
}

void object::drawField(){

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

/*void object::tick(){

    /// TODO: fix this!!

    VectorHelper tempVektor;

    postToAdd.X = 0;
    postToAdd.Y = 0;
    postToAdd.Z = 0;

    SpedToAdd.X = 0;
    SpedToAdd.Y = 0;
    SpedToAdd.Z = 0;

    #ifdef debug
    //  std::cout << "meine Params: " << Pos_X << " " << Pos_Y << " " << Pos_Z << " " << mass << " " << actSpeed.Wert << std::endl;
    #endif
    MassHelper->getF(Pos_X, Pos_Y, Pos_Z, mass, &tempVektor);
    tempVektor.X *= ZeitIntervall / mass;
    tempVektor.Y *= ZeitIntervall / mass;
    tempVektor.Z *= ZeitIntervall / mass;

    SpedToAdd.X -= tempVektor.X;
    SpedToAdd.Y -= tempVektor.Y;
    SpedToAdd.Z -= tempVektor.Z;

}*/

void object::newValues(){
    /*
    Pos_X += actSpeed.X * ZeitIntervall;
    Pos_Y += actSpeed.Y * ZeitIntervall;
    Pos_Z += actSpeed.Z * ZeitIntervall;

    actSpeed.X += SpedToAdd.X;
    actSpeed.Y += SpedToAdd.Y;
    actSpeed.Z += SpedToAdd.Z;
    */
}

bdt object::getMass() {return mass;}
bdt object::getX1()   {return posX1;}
bdt object::getX2()   {return posX2;}
bdt object::getX3()   {return posX3;}


///TODO: fill in
/*VectorHelper *object::getV(){
    VectorHelper *temp;
    temp = new VectorHelper;
    temp->X = actSpeed.X;
    temp->Y = actSpeed.Y;
    temp->Z = actSpeed.Z;
    temp->convertXYZToRotWert();
    return temp;
}*/
