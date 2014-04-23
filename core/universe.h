#ifndef UNIVERSE_H_INCLUDED
#define UNIVERSE_H_INCLUDED

/**
 * This is the instance to create a new universe/simulation/etc.
 * In order to start a new simulation, just create
 * a new universe via "new" or inheritance this class
 * into your own class.
 * All of the former global vars are now inside of this
 * "universe" class //todo: make this sure :/
 *
 * @author Simon Michalke
 * @version 0.9
 */

#include "object/object.h"
#include "object/noobject.h"
#include "object/body.h"
#include "object/quant.h"
#include "field/field.h"
#include "settings/settings.h"

using namespace vemc2;
using namespace vemc2::simulation;
using namespace vemc2::settings;


namespace vemc2{

class universe{

    public:

        universe();
        ~universe();

        /**
         * the start() function starts a new thread
         * and runs the simulation in it.
         * so this should be used if you want to do
         * something while the simulation is running
         * without worrying about threads
         */
        void start();


        /**
         * The run() function starts the simulation
         * in this thread. You can stop it with invoking
         * stop().
         * This should be used if you handle
         * your threads by your own.
         * the runt(*) function automatically stops after
         * certain conditions you can set for your own
         */
        void run();
        void run(double secondsToRun);

        /**
         * These are the settings for the universum
         *
         *
         *
         */
        struct{ // settings

            struct{ // texture struct
                bool   used;
                char*  Name_Underground;
                char*  Name_Background;
                char*  Name_Font;
                int    UndergroundNr;
                int    BackgroundNr;
                float  Underground_Heigh;
            }texture;

            struct{ // graphic
                bool   useColoredObjs;
                bool   vLines;
                int    countPointsBuffer;
                int    fps; //if 0 -> vsync
                int    LoghLevel;
                double scale;
                bool   useGravPlane;
                //vemc::Field_Mode fMode;
                bdt    fProbeSize;
                bool   useSFML2overlay;
                bool   useSphereForObj;

                struct{ //sphere
                    int countX;
                    int countY;
                    int mode;
                }sphere;

            }graphic;

            struct{ // sim
                float actIntervall;
                bool  useSimTimeToDump;
                bool  showDebText;
                bool  useParaProc;
                int   countParaThreads;
                bool  quant_Simulation;
            }sim;

            struct{ //win
                double SPSreal;
            }win;

            struct{ // gravPlane
                int   countX;
                int   countY;
                int   countZ;
                int   offX;
                int   offY;
                int   offZ;
                float stretch;
                Field_Dir Ver_Richt;
                int   MaxFieldAct; //if 0, ->unlimeted
            }gravPlane;

        }settings;

    protected:

        /**
         * This function copies the global settings from the
         * vemc2::settings namespace into the protected
         * settings struct.
         */
        void getGlobalSettings();

        /**
         * This fuction reserves the space for our drawable
         * arrays. It is being invoked in the contructor.
         * maybe we need long instead of int ...
         */
        void reservDrawableArraySpace(\
                                      int drawableCount,  \
                                      int objectCount,    \
                                      int bodyCount,      \
                                      int quantCount,     \
                                      int fieldCount,     \
                                      int noobjectCount   \
                                      );

        /**
         * The following three functions
         * will be used to be overwritten
         * when this class is being inherited
         * by a custom universe class.
         * So don't add any content ;-)
         */
        void invokeBeforeSim();
        void invokeMiddleSim();
        void invokeAfterSim();

        /**
         * List of objects that are being used
         * Every object is in his own array AND
         * in the array of the mother class and
         * of the grandmother class, etc.
         * --> Some Objects are in more than one
         * array. Every Object is at least in the
         * drawable Array.
         *
         * The arrays are being used by the
         * Effects and Fields, ...
         *
         * Maybe we have to set them as public
         */
         drawable **drawableArray;
         object   **objectArray;
         body     **bodyArray;
         quant    **quantArray;
         field    **fieldArray;
         noobject **noobjectArray;

    private:


};

}; /* namespace vemc2 */


#endif /* UNIVERSE_H_INCLUDED */
