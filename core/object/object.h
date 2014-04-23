#ifndef OBJEKT_H
#define OBJEKT_H

#include "drawable.h"

#include "./../define.h"
#include "./../myMath.h"

using namespace vemc2::simulation;

namespace vemc2{
namespace simulation{

class object : drawable {
    public:
        object();
        object(object *toCopy);
        object(bdt posX1ts, bdt posX2ts, bdt posX3ts, bdt massts);
        ~object();

        void draw();
        void drawField();
        void newValues();
        void tick();

        bdt getMass();
        bdt getX1();
        bdt getX2();
        bdt getX3();

        void setMass(bdt massts);
        void setX(bdt Xts);
        void setY(bdt Yts);
        void setZ(bdt Zts);

    protected:

        bdt posX1, posX2, posX3;
        bdt mass;

};

} /*namespace simulation */
} /*namespace vemc2 */

#endif // OBJEKT_H
