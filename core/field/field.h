#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include "./../object/drawable.h"
#include "./../effect/effect.h"

using namespace vemc2::simulation;

namespace vemc2{
namespace simulation{

class field : drawable{
    public:
        field();
        ~field();

        void draw();

    protected:
    private:

};

}; /* namespace simulation */
}; /* namespace vemc2 */


#endif /* FIELD_H_INCLUDED */
