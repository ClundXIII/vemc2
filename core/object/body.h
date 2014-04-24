#ifndef BODY_H
#define BODY_H

#include "object.h"

#include "./../define.h"

using namespace vemc2::simulation;

namespace vemc2{
namespace simulation{

class body : object {
    public:
        body();
        body(object *toCopy);
        body(bdt posX1ts, bdt posX2ts, bdt posX3ts, bdt massts);
        ~body();

        void draw();
        void drawField();
        void newValues();
        void tick();

        bdt getMass();
        bdt getX();
        bdt getY();
        bdt getZ();

        void setMass(bdt massts);
        void setX(bdt Xts);
        void setY(bdt Yts);
        void setZ(bdt Zts);

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
