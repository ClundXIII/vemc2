#ifndef RECORDER_H
#define RECORDER_H

#include "../define.h"
#include "effect.h"

#include <fstream>

namespace vemc2{

class universe;

namespace simulation{

struct recordValuePackage{
    bdt *toRecord;
    const char* label;
    const char* unit;
    bdt buffer[RECBUFFERSIZE];
};

class recorder : public effect{
    public:
        recorder(vemc2::universe *globUniversets);
        virtual ~recorder();

        void tick();

        int push_value(bdt *toRecord, const char* label, const char* unit);

        int writeToFile(const char* filename);

        bool console_output;

    protected:
    private:

        bool fileOutput;
        std::ofstream *file = 0;

        recordValuePackage* data;
        int valuePackageSize;
};

}; /* namespace simulation */
}; /* namespace vemc2 */

#endif // RECORDER_H
