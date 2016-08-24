#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include <vemc2/core/universe.h>

#include <thread>

namespace vemc2{
namespace graphic{

class graphicgl{
    public:

        graphicgl(int argc, char **argv);
        ~graphicgl();

        /**
         * Use this function to attach an universe via
         * lib-based simulation to this Visualisation.
         *
         * returns 0 if sucess!
         */
        static void attachUniverse(vemc2::universe *universets);

        static void draw_function(void);

        static void reshape_function(int width, int height);

        static void move_function();

        static void keyPressed_function(unsigned char key, int x, int y);

        static void keyUp_function(unsigned char key, int x, int y);

        static void mouseMove_function(int width, int height);
        static void mouse_function(int button, int state,int x, int y);

        static bool isRunning();

        static void stop();

        static vemc2::universe *attachedWorld;

    protected:

        static struct posdata{
            bool followObject;
            int objNumber;

            float distance;
            float west;
            float north;

            float posX;
            float posY;
            float posZ;

        }position_data;


        static bool* keyStates;
        static bool* mouseStates;
        static int   mouseXpreviousState;
        static int   mouseYpreviousState;

    private:

        static int argc;
        static char **argv;

        static bool running;

};

}; /* namespace graphic */
}; /* namespace vemc2 */

#endif /* GRAPHIC_H_INCLUDED */
