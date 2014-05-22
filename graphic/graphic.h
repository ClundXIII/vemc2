#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include <core/universe.h>

#include <thread>

namespace vemc2{
namespace graphic{

class graphicgl : public std::thread{
    public:

        graphicgl();
        ~graphicgl();

        /**
         * Use this function to attach an universe via
         * lib-based simulation to this Visualisation.
         *
         * returns 0 if sucess!
         */
        int attachUniverse(vemc2::universe *universets);

        void run();

        void stop();

        static void static_run(vemc2::graphic::graphicgl *toRun);


    protected:

        vemc2::universe *attachedWorld;

    private:

        bool running;

};

}; /* namespace graphic */
}; /* namespace vemc2 */

#endif /* GRAPHIC_H_INCLUDED */
