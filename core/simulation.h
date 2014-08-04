#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "mymath/math_struct.h"

#include "effect/effect.h"
#include "effect/inertia.h"

#include "field/field.h"

#include "object/object.h"
#include "object/noobject.h"
#include "object/body.h"
#include "object/quant.h"

namespace vemc2{
    enum simulation_type{
        planetSimulation,
        quantumSimulation,
        feynmanSimulation,
        bodySimulation
    };

    /**
     * extend this enum if you want!
     */
    enum objectType{
        t_none =0,
        t_body,
        t_quant
    };
}; /* namespace vemc2 */

#endif // SIMULATION_H_INCLUDED
