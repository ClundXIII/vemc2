#ifndef DRAWS_H_INCLUDED
#define DRAWS_H_INCLUDED

#include <vemc2/core/object/body.h>
#include <vemc2/core/object/quant.h>
#include <vemc2/core/universe.h>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>


namespace vemc2{
namespace graphic{

    void draw(vemc2::universe *parentUniverse, bdt posX, bdt posY, bdt posZ, float diameter);
    void drawPoint();
    void drawDiamond(float diameter, bool colored);
    void drawSphere(float diameter);

};/* namespace graphic */
};/* namespace vemc2 */

#endif // DRAWS_H_INCLUDED
