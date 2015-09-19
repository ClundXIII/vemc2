#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include <core/universe.h>

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

        static bool isRunning();

        static void stop();

        static vemc2::universe *attachedWorld;

    protected:

    private:

        static int argc;
        static char **argv;

        static bool running;

};

}; /* namespace graphic */
}; /* namespace vemc2 */

#endif /* GRAPHIC_H_INCLUDED */
