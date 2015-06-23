#ifndef INERTIA_H_INCLUDED
#define INERTIA_H_INCLUDED

#include "effect.h"

namespace vemc2{
namespace simulation{

class inertia : effect{

    public:

        inertia(vemc2::universe *globUniversets);
        ~inertia();

        virtual void tick();

        virtual void upValues();

    protected:

    private:

};

}; /* namespace simulation */
}; /* namespace vemc2 */



#endif /* INERTIA_H_INCLUDED */
