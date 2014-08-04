#include "draws.h"

void body::draw(){

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
}
