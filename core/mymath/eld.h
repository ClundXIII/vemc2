#ifndef ELD_H
#define ELD_H

#include "./../define.h"

#include "./../myMath.h"

/**
 * This is the our super-duper special
 * datatype for very small and very big
 * numbers.
 *
 * Basically it is like you calculate in
 * physics lessons:
 * e.g. e = 1.6022 * 10 ^(-19)
 *
 * our eld would be like:
 * base = 1.6022 (float, double or long double)
 * exp = -19 (integer ... maybe we will add a long,
 *            but I don't we'll need this)
 *
 * we overloaded these operators, they return an eld:
 * operator+(eld toAdd);
 * operator-(eld toSub);
 * operator*(eld toMul);
 * operator/(eld toDiv);
 *
 * operator+(bdt toAdd);
 * operator-(bdt toSub);
 * operator*(bdt toMul);
 * operator/(bdt toDiv);
 * (could also be a float or double as parameter)
 *
 * @author Simon Michalke
 * @version 0.9
 */

namespace vemc2{
namespace simulation{

class eld{
    public:

        eld();
        eld(eld *k);
        eld(bdt basets, int expts);
        ~eld();

        //set base
        void sB(bdt basets);
        //set exponent
        void sE(int expts);
        //set both
        void sBE(bdt basets, int expts);

        //get Value as bdt
        bdt getV();
        //get Value by exponent
        bdt getVbyExp(int Exponent);

        //returns Base
        bdt gB();
        //returns Exponent
        int gE();

        //get a new eld requested with new
        //be careful: memory leaks!!!
        eld* getNewEld();

        //our operators (see above):
         void operator=(eld toSet);
         void operator=(bdt toSet);

         eld operator+(eld toAdd);
         eld operator-(eld toSub);
         eld operator*(eld toMul);
         eld operator/(eld toDiv);

         eld operator+(bdt toAdd);
         eld operator-(bdt toSub);
         eld operator*(bdt toMul);
         eld operator/(bdt toDiv);

    protected:
    private:

        //the base:
        bdt base;

        //our exponent
        int exp;

        //set:
        //  -10 < base < 10
        void optimize();

        //returns eld added/multiplicated with this
        eld Add(eld toAdd);
        eld Mul(eld toMul);
};


} /*namespace simulation */
} /*namespace vemc2 */

#endif // ELD_H
