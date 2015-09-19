#include "graphic.h"

#include "draws.h"

#include <chrono>
#include <iostream>

using namespace vemc2::graphic;

graphicgl::graphicgl(int argcTs, char **argvTs){
    attachedWorld = 0;
    if (running)
        throw (char*) "Only one Window supported at the moment";
    running = true;
    argc = argcTs;
    argv = argvTs;
}

graphicgl::~graphicgl(){
    running = false;
}

void graphicgl::draw_function(){

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
    glLoadIdentity();  // Load the Identity Matrix to reset our drawing locations

    for (int i=0; attachedWorld->drawableArray[i] != 0; i++){
        vemc2::simulation::body b = attachedWorld->bodyArray[i];
        b.draw();
        std::cout << "."; std::cout.flush();
    }


    glFlush(); // Flush the OpenGL buffers to the window

}

void  graphicgl::reshape_function(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
    glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
    glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}

bool graphicgl::isRunning(){
    return running;
}

void graphicgl::stop(){
    running = false;
}

void graphicgl::attachUniverse(vemc2::universe *universets){
    attachedWorld = universets;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Your first OpenGL Window");

    glutIdleFunc(graphicgl::draw_function);
    //glutDisplayFunc(graphicgl::draw_function);
    glutReshapeFunc(graphicgl::reshape_function);

    std::cout << "starting loop ..." << std::endl;

    glutMainLoop();
}

bool graphicgl::running = false;

vemc2::universe *graphicgl::attachedWorld;

int graphicgl::argc;
char **graphicgl::argv;
