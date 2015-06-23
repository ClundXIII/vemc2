#ifndef BODY_H
#define BODY_H

#include "object.h"

#include "./../define.h"

using namespace vemc2::simulation;

namespace vemc2{
namespace simulation{

class body : public object {
    public:
        body();
        body(body *toCopy);
        body(bdt posX1ts, bdt posX2ts, bdt posX3ts, bdt massts);
        virtual ~body();

        void draw();
        void drawField();
        void newValues();
        void tick();

        bdt getMass();
        vemc2::mymath::vec3bdt getX();
        bdt getX1();
        bdt getX2();
        bdt getX3();

        void setMass(bdt massts);
        void setX1(bdt X1ts);
        void setX2(bdt X2ts);
        void setX3(bdt X3ts);

    protected:

        /**
         * Thanks to Gisela Anton for this idea!
         */
        bdt rotX1;
        bdt rotX2;
        bdt rotX3;

};

} /*namespace simulation */
} /*namespace vemc2 */

#endif // BODY_H
