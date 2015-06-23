#ifndef GRAVITATION_H_INCLUDED
#define GRAVITATION_H_INCLUDED

#include "effect.h"

namespace vemc2{
namespace simulation{

class gravitation : effect {
    public:

        gravitation(vemc2::universe *globUniversets);
        ~gravitation();


        virtual void tick();

        virtual void upValues();

    protected:
    private:

};

}; /* namespace simulation */
}; /* namespace vemc2 */



#endif /* GRAVITATION_H_INCLUDED */
