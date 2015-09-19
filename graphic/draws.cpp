
#include "draws.h"
#include "graphic.h"

using namespace vemc2;
using namespace vemc2::simulation;

void simulation::body::draw(){
    graphic::draw(graphic::graphicgl::attachedWorld, getX1(),getX2(),getX3(),mass);
}

void graphic::draw(universe *parentUniverse, bdt posX, bdt posY, bdt posZ, float diameter){

/*
    if (Settings::Grafik::LoghLevel == 1){ //natürlich (sprich e)
        diameter = log(mass);
    }
    else if (Settings::Grafik::LoghLevel == 2){ //2'er
        diameter = log2(mass);
    }
    else if (Settings::Grafik::LoghLevel == 3){ //10'er
        diameter = log10(mass);
    }*/


    glTranslatef(posX, posY, posZ);

    if (!parentUniverse->settings.graphic.useSphereForObj){

        graphic::drawDiamond(diameter, parentUniverse->settings.graphic.useColoredObjs);
    }
    else{
        graphic::drawSphere(diameter);
    }

    if (parentUniverse->settings.graphic.vLines){
    glBegin(GL_QUADS);
    //Zeichne die Senkrechten Striche
        glColor3f(1.f, 0.5f, 0.5f);
/*
        glVertex3f( LinDicke, -posY, 0.f);
        glVertex3f(-LinDicke, -posY, 0.f);
        glVertex3f(-LinDicke,    0.f, 0.f);
        glVertex3f( LinDicke,    0.f, 0.f);

        glVertex3f(0.f, -posY,  LinDicke);
        glVertex3f(0.f, -posY, -LinDicke);
        glVertex3f(0.f,    0.f, -LinDicke);
        glVertex3f(0.f,    0.f,  LinDicke);
*/
    glEnd();
    }

    glTranslatef(-posX, -posY, -posZ);

}

void graphic::drawPoint(){
}

void graphic::drawDiamond(float diameter, bool colored){

    diameter /= 2;

    glBegin(GL_TRIANGLES);

    if (colored){
        //obere Pyramide
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f( diameter,     0,  diameter);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f( diameter,     0, -diameter);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(         0, 1.4*diameter,          0);

        glColor3f(0.f, 1.f, 0.f);
        glVertex3f( diameter,     0, -diameter);
        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(-diameter,     0, -diameter);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(         0, 1.4*diameter,          0);

        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(-diameter,     0, -diameter);
        glColor3f(1.f, 0.f, 1.f);
        glVertex3f(-diameter,     0,  diameter);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(         0, 1.4*diameter,          0);

        glColor3f(1.f, 0.f, 1.f);
        glVertex3f(-diameter,     0,  diameter);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f( diameter,     0,  diameter);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(         0, 1.4*diameter,          0);

        //untere Pyramide
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f( diameter,     0,  diameter);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f( diameter,     0, -diameter);
        glColor3f(1.f, 0.f, 0.5f);
        glVertex3f(         0,-0.7*diameter,          0);

        glColor3f(0.f, 1.f, 0.f);
        glVertex3f( diameter,     0, -diameter);
        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(-diameter,     0, -diameter);
        glColor3f(1.f, 0.f, 0.5f);
        glVertex3f(         0,-1.4*diameter,          0);

        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(-diameter,     0, -diameter);
        glColor3f(1.f, 0.f, 1.f);
        glVertex3f(-diameter,     0,  diameter);
        glColor3f(1.f, 0.f, 0.5f);
        glVertex3f(         0,-1.4*diameter,          0);

        glColor3f(1.f, 0.f, 1.f);
        glVertex3f(-diameter,     0,  diameter);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f( diameter,     0,  diameter);
        glColor3f(1.f, 0.f, 0.5f);
        glVertex3f(         0,-1.4*diameter,          0);
    }
    else{
        //obere Pyramide
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f( diameter,     0,  diameter);
        glVertex3f( diameter,     0, -diameter);
        glVertex3f(         0, 1.4*diameter,          0);

        glVertex3f( diameter,     0, -diameter);
        glVertex3f(-diameter,     0, -diameter);
        glVertex3f(         0, 1.4*diameter,          0);

        glVertex3f(-diameter,     0, -diameter);
        glVertex3f(-diameter,     0,  diameter);
        glVertex3f(         0, 1.4*diameter,          0);

        glVertex3f(-diameter,     0,  diameter);
        glVertex3f( diameter,     0,  diameter);
        glVertex3f(         0, 1.4*diameter,          0);

        //untere Pyramide
        glVertex3f( diameter,     0,  diameter);
        glVertex3f( diameter,     0, -diameter);
        glVertex3f(         0,-1.4*diameter,          0);

        glVertex3f( diameter,     0, -diameter);
        glVertex3f(-diameter,     0, -diameter);
        glVertex3f(         0,-1.4*diameter,          0);

        glVertex3f(-diameter,     0, -diameter);
        glVertex3f(-diameter,     0,  diameter);
        glVertex3f(         0,-1.4*diameter,          0);

        glVertex3f(-diameter,     0,  diameter);
        glVertex3f( diameter,     0,  diameter);
        glVertex3f(         0,-1.4*diameter,          0);
    }
    glEnd();
}

void graphic::drawSphere(float diameter){
        GLUquadricObj *gluObj = gluNewQuadric();
        gluSphere(gluObj, 0.5*diameter, 20, 10);
}

