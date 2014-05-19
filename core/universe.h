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
 * @version 0.0.01
 */

#include "simulation.h"
#include "settings/settings.h"

namespace vemc2{

class universe{

    public:

        universe();
        ~universe();

        /**
         * the update() function applies the changed
         * settings to the params of the simulation
         * thread, the effects, etcpp
         * Be careful! Do this as less as you want, it
         * is maybe not memory-resistant!
         */
        void update();

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
        struct{ // settings struct

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

            struct{ // sim_thread
                bool  useSimTimeToDump;
                bool  showDebText;
                bool  useParaProc;
                int   countParaThreads;
                int   paraLevel;/**
                                 * 0 => parallelize calculation per object
                                 * 1 => parallelize effect calculation
                                 * 2 => parallelize effect calculation per object
                                 * 3 => parallelize effect calculation per object per dimension
                                 */
            }sim_thread;

            struct{ // sim
                bdt       dt;
                bool      quant_Simulation;
                bool      body_Simulation;
                bool      use_srt;
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
                vemc2::settings::Field_Dir Ver_Richt;
                int   MaxFieldAct; //if 0, ->unlimeted
            }gravPlane;

        }settings;

        /**
         * Sets the machine to a spezified status like:
         * - planet Simulation (bodies, gravitation, no collision)
         * - quantum Simulation (Heisenberg & Co)
         * - Feynman Simulation (quantums with collision)
         * - Body Simulation (bodies with collision)
         * Be careful, this will reset the values of the
         * drawable Arrays and other stuff.
         */
        int setSimulationType(vemc2::simulation_type simTypets);
        int insertBody();
        int insertQuant();
        int insertField();
        int insertNoobject();

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

         int drawableCount;
         int objectCount;
         int bodyCount;
         int quantCount;
         int fieldCount;
         int noobjectCount;

        /**
         * Effect List contain all effects.
         * They will be called from 0 to
         * effectCount-1
         */
         effect **effectArray;
         int      effectCount;

    protected:

        /**
         * The field struct contain all fields sorted by type.
         * This struct will be used by the effects, so that
         * they find their field more easy.
         * For drawing, use the **fieldArray!
         * For own theories / fields, extend this array
         */
        struct field_struct{
            //
        }fields;

        vemc2::simulation_type simType;

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
                                      int drawableCountts,  \
                                      int objectCountts,    \
                                      int bodyCountts,      \
                                      int quantCountts,     \
                                      int fieldCountts,     \
                                      int noobjectCountts   \
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

    private:

        /**
         * Cleaning up the memory and deletes all the drawables
         * (including the fields)
         */
        void deleteAllDrawables();

        /**
         * Cleaning up the memory and deletes all the effects;
         */
        void deleteAllEffects();


};

}; /* namespace vemc2 */


#endif /* UNIVERSE_H_INCLUDED */
