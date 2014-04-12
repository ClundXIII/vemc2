#ifndef MYMATH_H_INCLUDED
#define MYMATH_H_INCLUDED

///Headers we need for math operations
#include <math.h>
#include <time.h>
#ifdef __MACH__
    #include <mach/clock.h>
    #include <mach/mach.h>
#endif

//#define Pi 3.1415963

/**
 * Base Data Type aka "bdt":
 * the datatype we use for coordinates
 * and eld base and for all the calculating:
 *
 */
    ///If we wanna be a noob and use float ;-)
    /*#ifdef __CYGWIN__
        typedef long double bdt;
    #else
        #define bdt long double
    #endif*/
    ///use double:
    /*#ifdef __CYGWIN__
        typedef long double double;
    #else
        #define double long double
    #endif*/
    ///If we wanna use long double (standard):
    #ifdef __CYGWIN__
        typedef long double bdt;
    #else
        #define bdt long double
    #endif
///end of base datatype

///Define our constants we can use
namespace vemc2{
namespace simulation{class eld;};
namespace mymath{
    extern vemc2::simulation::eld e;
    extern vemc2::simulation::eld h;
    extern vemc2::simulation::eld angstroem;

    namespace planck{
        extern vemc2::simulation::eld m_p;
        extern vemc2::simulation::eld l_p;
        extern vemc2::simulation::eld t_p;
        extern vemc2::simulation::eld q_p;
        extern vemc2::simulation::eld T_p;
    };

    extern vemc2::simulation::eld dt;

};
}; /*namespace vemc2 */

//the function itself is in mymath/eld.cpp
vemc2::simulation::eld retEld(long double base, int exponent);



#endif // MYMATH_H_INCLUDED
