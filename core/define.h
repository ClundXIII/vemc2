#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#ifdef __CYGWIN__
    typedef long double ld;
#else
    #define ld long double
#endif

#define DEBUG //we are now debugging

//extended long double: Datatype
//ten or e (Euleric Number)
#define ELD_MODE_TEN
//#define ELD_MODE_EULER

#endif // DEFINE_H_INCLUDED
