#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED
#include "./../define.h"
#include "./../myMath.h"

#include <fstream>

/*enum RelAnzModus{
    Normal = 0,
    Skaliert = 1,
    logarhythmisch = 2
};*/

namespace vemc2{
namespace settings{

    bool compareSetting(char* String1, const char* String2);

    char* getRest(char* setString);

    int init(std::fstream *f, int argc, char** argv);
    int printDefault(std::fstream *f);

    namespace Texture{
        extern bool   used;
        extern char*  Name_Underground;
        extern char*  Name_Background;
        extern char*  Name_Font;
        extern int    UndergroundNr;
        extern int    BackgroundNr;
        extern float  Underground_Heigh;
    };

    namespace Graphic{
        extern bool   useColoredObjs;
        extern bool   vLines;
        extern int    countPointsBuffer;
        extern int    fps; //if 0 -> vsync
        extern int    LoghLevel;
        extern double scale;
        extern bool   useGravPlane;
        //extern vemc::Field_Mode fMode;
        extern bdt    fProbeSize;
        extern bool   useSFML2overlay;
        extern bool   useSphereForObj;

        namespace Sphere{
            extern int countX;
            extern int countY;
            extern int mode;
        };

    };

    namespace Sim{
        extern float actIntervall;
        extern bool  useSimTimeToDump;
        extern bool  showDebText;
        extern bool  useParaProc;
        extern int   countParaThreads;
        extern bool  quant_Simulation;
    };

    namespace Win{
        extern double SPSreal;
    };

    enum Field_Dir{
        plusX,
        minusX,
        plusY,
        minusY,
        plusZ,
        minusZ,
        FVec
    };

    namespace gravPlane{
        extern int   countX;
        extern int   countY;
        extern int   countZ;
        extern int   offX;
        extern int   offY;
        extern int   offZ;
        extern float stretch;
        extern Field_Dir Ver_Richt;
        extern int   MaxFieldAct; //if 0, ->unlimeted
    };

}; /* namespace settings */
}; /* namespace vemc2 */

#endif /* SETTINGS_H_INCLUDED */
