#ifndef OBJEKT_H
#define OBJEKT_H

#include "drawable.h"

#include "./../define.h"
#include "./../myMath.h"
#include "./../mymath/vec3bdt.h"

#include <vector>

using namespace vemc2::simulation;

namespace vemc2{
namespace simulation{

struct soa_object;

class object : drawable {
    public:
        object();
        object(object *toCopy);
        object(bdt posX1ts, bdt posX2ts, bdt posX3ts, bdt massts);
        virtual ~object();

        virtual void draw();
        virtual void drawField();

        virtual bdt getMass();
        virtual vemc2::mymath::vec3bdt getX();
        virtual bdt getX1();
        virtual bdt getX2();
        virtual bdt getX3();

        virtual void setMass(bdt massts);
        virtual void setX1(bdt X1ts);
        virtual void setX2(bdt X2ts);
        virtual void setX3(bdt X3ts);

        virtual void setDataNull();

        struct effect_data{ //data
            struct{ //F
                bdt X1;
                bdt X2;
                bdt X3;
            }F;
            struct{ //a
                bdt X1;
                bdt X2;
                bdt X3;
            }a;
            struct{ //v
                bdt X1;
                bdt X2;
                bdt X3;
            }v;
        }data;


        void addF(std::vector<bdt> Fta);
        void addA(std::vector<bdt> Ata);
        void addV(std::vector<bdt> Vta);

        /**
         * struct of array functions:
         */

        /**
         * generates a struct of arrays for the object
         */
        static soa_object* soa_generate(object **objs, int count); //=0;

    protected:

        bdt posX1, posX2, posX3;
        bdt mass;

};


struct soa_object{
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

#endif // OBJEKT_H
