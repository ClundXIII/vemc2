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

        /**
         * generates a struct of arrays for the object
         */
        //static soa_object* soa_generate(object **objs);

    protected:

        /**
         * Thanks to Gisela Anton for this idea!
         */
        bdt rotX1;
        bdt rotX2;
        bdt rotX3;

};

struct soa_body : soa_object{
    int element_count;

    bdt posX1[], posX2[], posX3[];

    struct { //data
            struct{ //F
                bdt X1[];
                bdt X2[];
                bdt X3[];
            }F;
            struct{ //a
                bdt X1[];
                bdt X2[];
                bdt X3[];
            }a;
            struct{ //v
                bdt X1[];
                bdt X2[];
                bdt X3[];
            }v;
        }data;
};

} /*namespace simulation */
} /*namespace vemc2 */

#endif // BODY_H
