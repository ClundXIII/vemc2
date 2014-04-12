#ifndef OBJEKT_H
#define OBJEKT_H

#include "drawable.h"

#include "./../define.h"

using namespace vemc2::simulation;

namespace vemc2{
namespace simulation{

class object : drawable {
    public:
        Objekt();
        Objekt(object *toCopy);
        Objekt(ld PosX, ld PosY, ld PosZ, ld Massts);
        ~Objekt();

        void draw();
        void drawField()
        void newValues();
        void tick();

        ld getMass();
        ld getX();
        ld getY();
        ld getZ();

        void setMass(ld massts);
        void setX(ld Xts);
        void setY(ld Yts);
        void setZ(ld Zts);

    protected:

        ld Pos_X, Pos_Y, Pos_Z;
        ld mass;

};

} /*namespace simulation */
} /*namespace vemc2 */

#endif // OBJEKT_H
