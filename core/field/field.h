#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include "./../object/drawable.h"
#include "./../effect/effect.h"

using namespace vemc2::simulation;

namespace vemc2{
namespace simulation{

class field : drawable{
    public:

        /**
         * We don't declare any contructors / destructors so the
         * compiler doesn't search for them ;-)
         */
        field(vemc2::universe *globUniversets);
        virtual ~field();

        virtual void draw();

    protected:

        /**
         * This is a pointer to the universe the field belongs to.
         */
        vemc2::universe *globUniverse;

    private:

};

}; /* namespace simulation */
}; /* namespace vemc2 */


#endif /* FIELD_H_INCLUDED */
