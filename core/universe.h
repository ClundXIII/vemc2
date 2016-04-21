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

//#include <vesper_log/Logging.hpp>
#include <Logging.hpp>

namespace vemc2{

class parser;

class universe{

    public:

        universe();
        universe(int vLevel);
        ~universe();

        void parse(std::string command);

        /**
         * This function sets the Verbose Level for the
         * universe. Default is 0
         * Level:
         * -1 : no output at all
         *  0 : very little, just creating universe
         *      and switching simulationType, etc
         *      and errors
         *  1 : plus when and where adding an object
         *      collision etc
         *  2 : plus detailed information about 1
         *  3 : just everything
         */
        void setVerboseLevel(int l);


        /**
         * the update() function applies the changed
         * settings to the params of the simulation
         * thread, the effects, etcpp
         * Be careful! Do this as less as you want, it
         * is maybe not memory-resistant!
         */
        void update();

        /**
         * The resetArrays() function re-allocates all
         * the memory needed for the drawable and effect
         * arrays.
         * Invoke this if you changed the amount of the
         * drawables, etc
         * (--> int *count)
         */
        void resetArrays();

        /**
         * resetWorld resets the World an copies the Scene from
         * the Arrays to the simulateObjects
         */
        void resetWorld();

        /**
         * the start() function starts a new thread
         * and runs the simulation in it.
         * so this should be used if you want to do
         * something while the simulation is running
         * without worrying about threads
         */
        void start();

        /**
         * The stop function stops the simulation
         * and terminates all running threads.
         */
        void stop();

        /**
         * pause() and unpause() is used to
         * pause and resume the simulation
         *
         */
        void pause();
        void unpause();

        simulation::sim_thread *simulationThread=0;

        /**
         * This struct contains all the data while simulation.
         * It is deleted and generated new after each reset to
         * save the original scene. (If you want to try the
         * simulation with other settings, etc)
         */
        struct{
            union{
                simulation::body   **b;
                simulation::quant  **q;
            }objects;

            int objectCount;
        }simulateStruct;

        void clearSimulateStruct();

        /**
         * The run() function starts the simulation
         * in this thread. You can stop it with invoking
         * stop().
         * This should be used if you handle
         * your threads by your own.
         * the run(*) function automatically stops after
         * certain conditions you can set for your own
         */
        void run();
        void run(bdt secondsToRun);

        /**
         * These are the settings for the universe
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
                float  under_heigh;
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
                bdt       global_time;
                bool      quant_Simulation;
                bool      body_Simulation;
                bool      use_srt;
                bdt       DeadZone;
                struct{
                    double G;
                }NatConst;
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
         * Sets the machine to a pre-defined status like:
         * - planet Simulation (bodies, gravitation, no collision)
         * - quantum Simulation (Heisenberg & Co)
         * - Feynman Simulation (quantums with collision)
         * - Body Simulation (bodies with collision)
         * Be careful, this will reset the values of the
         * drawable Arrays and other stuff.
         */
        int setSimulationType(vemc2::simulation_type simTypets);

        int insertEffect(vemc2::simulation::effect *effectToIns);

        /**
         * This sets the object Type that is being used for simulating
         */
        void setObjectType(objectType typets);

        /**
         * These functions insert the different kind of
         * drawables (see object/drawable.h) into the
         * universe. They will recursively call the insert
         * function of their mother class automatically
         */
        int insertDrawable(vemc2::simulation::drawable *toInsert);
        int insertObject(vemc2::simulation::object *toInsert);
        int insertBody(vemc2::simulation::body *toInsert);
        int insertQuant(vemc2::simulation::quant *toInsert);
        int insertField(vemc2::simulation::field *toInsert);
        int insertNoobject(vemc2::simulation::noobject *toInsert);

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
         *
         * We actually got *Count-1 drawables (etc)
         * avaible! keep this in mind!
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
         * simulateObjects contains the Objects, that are being simulated.
         * The content of the Array, that is being simulated is copied to
         * simulateObject Array as soon as resetWorld is being invoked.
         */
        object   **simulateObjects;

        /**
         * This represents the type of object that is being used to simulate
         * see: simulation.h
         */
        objectType useForSimulation;
        /**
         * The number of objects in **simulateObjects
         */
        int simulateObjectCount;

        /**
         * Effect List contain all effects.
         * They will be called from 0 to
         * effectCount-1
         */
        effect **effectArray;
        int      effectCount;

        /**
         * The field struct contain all fields sorted by type.
         * This struct will be used by the effects, so that
         * they find their field more easy.
         * For drawing, use the **fieldArray!
         * For own theories / fields, extend this array
         */
        struct field_struct{
            vemc2::simulation::Gfield *G;
            //vemc2::simulation::Efield *E;
        }fields;

        Vesper::Logging out;

    protected:

        friend class parser;
        parser *command_helper;

        friend class simulation::sim_thread;

        int verboseLevel;

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
        void reserveDrawableArraySpace(\
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

        /**
         * scrollToArrayEnd() searches for the first position
         * within an 2D-Array (typical a *Array var) that
         * is 0. Useful for finding the next place to add
         * a drawable / effect.
         */
        int scrollToArrayEnd(void **a);

};

}; /* namespace vemc2 */


#endif /* UNIVERSE_H_INCLUDED */
