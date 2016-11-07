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

    position_data.followObject = false;
    position_data.objNumber = 0;

    position_data.distance = 75;
    position_data.west=0;
    position_data.north= 0;

    position_data.posX = 0;
    position_data.posY = 0;
    position_data.posZ = 0;
}

graphicgl::~graphicgl(){
    running = false;
}

void graphicgl::draw_function(){

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
    glLoadIdentity();  // Load the Identity Matrix to reset our drawing locations

    glTranslatef(0.f, 0.f, -position_data.distance);

    glRotatef(position_data.north, 1.f, 0, 0);
    glRotatef(position_data.west, 0, 1.f, 0);

    glTranslatef(-position_data.posX, -position_data.posY, -position_data.posZ);
    //Koordinate System
    glBegin(GL_LINES);

    glVertex3f(-100.f, 0.f, 0.f);
    glVertex3f( 100.f, 0.f, 0.f);

    glVertex3f( 0.f,-100.f, 0.f);
    glVertex3f( 0.f, 100.f, 0.f);

    glVertex3f( 0.f, 0.f,-100.f);
    glVertex3f( 0.f, 0.f, 100.f);

    glEnd();

    for (int i=0; attachedWorld->drawableArray[i] != 0; i++){
        vemc2::simulation::body *b = attachedWorld->bodyArray[i];
        if (b) b->draw();
        attachedWorld->drawableArray[i]->draw();
    }


    glFlush(); // Flush the OpenGL buffers to the window
    glutPostRedisplay();
}

void  graphicgl::reshape_function(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
    glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
    glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}

void graphicgl::move_function(){
}

void graphicgl::keyPressed_function(unsigned char key, int x, int y) {
    keyStates[key] = true;
}

void graphicgl::keyUp_function(unsigned char key, int x, int y) {
    keyStates[key] = false;
    if (key == 'w'){
        position_data.distance -= 10;
    }
    if (key == 's'){
        position_data.distance += 10;
    }
}

void graphicgl::mouseMove_function(int width, int height){

    if (mouseStates[0]){
        position_data.west -= (mouseXpreviousState - width)/5;
        position_data.north -= (mouseYpreviousState - height)/5;
        mouseXpreviousState = width;
        mouseYpreviousState = height;
    }
    else if (mouseStates[2]){
        position_data.west -= (mouseXpreviousState - width)/5;
        position_data.distance -= (mouseYpreviousState - height)/5;

        mouseXpreviousState = width;
        mouseYpreviousState = height;
    }
    else{
        mouseXpreviousState = width;
        mouseYpreviousState = height;
    }

    if (position_data.north > 85)
        position_data.north = 85;

    if (position_data.north < -85)
        position_data.north = -85;

    if (position_data.west > 360)
        position_data.west -= 360;

    if (position_data.west < -360)
        position_data.west += 360;

}

void graphicgl::mouse_function(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON){
        if (state == GLUT_DOWN)
            mouseStates[0] = true;
        else
            mouseStates[0] = false;
    }
    else if (button == GLUT_MIDDLE_BUTTON){
        if (state == GLUT_DOWN)
            mouseStates[1] = true;
        else
            mouseStates[1] = false;
    }
    else if (button == GLUT_RIGHT_BUTTON){
        if (state == GLUT_DOWN)
            mouseStates[2] = true;
        else
            mouseStates[2] = false;
    }
    else if (button == 3){
        position_data.distance -= 5;
    }
    else if (button == 4){
        position_data.distance += 5;
    }
}


bool graphicgl::isRunning(){
    return running;
}

void graphicgl::stop(){
    running = false;
}

using namespace std::chrono;

high_resolution_clock::time_point last_timestamp = high_resolution_clock::now();

void control_fps(){

    high_resolution_clock::time_point thist = high_resolution_clock::now();

    long millis_to_wait = 330/((long) (duration_cast<milliseconds>( thist - last_timestamp ).count())+0.0001);

    last_timestamp = high_resolution_clock::now();

    std::chrono::milliseconds timespan(millis_to_wait);

    std::this_thread::sleep_for(timespan);
}

void graphicgl::attachUniverse(vemc2::universe *universets){
    attachedWorld = universets;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Vemc2 graphic Window");

    glutIdleFunc(control_fps);
    glutDisplayFunc(graphicgl::draw_function);
    glutReshapeFunc(graphicgl::reshape_function);
    glutMouseFunc(graphicgl::mouse_function);
    glutMotionFunc(graphicgl::mouseMove_function);
    glutPassiveMotionFunc(graphicgl::mouseMove_function);
    glutKeyboardUpFunc(graphicgl::keyUp_function);

    std::cout << "starting loop ..." << std::endl;

    glutMainLoop();
}

bool graphicgl::running = false;

vemc2::universe *graphicgl::attachedWorld;

graphicgl::posdata graphicgl::position_data;

bool* graphicgl::keyStates = new bool[256];
bool* graphicgl::mouseStates = new bool[3];

int   graphicgl::mouseXpreviousState;
int   graphicgl::mouseYpreviousState;

int graphicgl::argc;
char **graphicgl::argv;
