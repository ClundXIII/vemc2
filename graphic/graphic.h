#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include <thread>

namespace vemc2{
namespace graphic{

class graphicgl : public std::thread{
    public:

        graphicgl();
        ~graphicgl();


        void run();

        void stop();

        static void static_run(vemc2::graphic::graphicgl *toRun);


    protected:

    private:

        bool running;

};

}; /* namespace graphic */
}; /* namespace vemc2 */

#endif /* GRAPHIC_H_INCLUDED */
