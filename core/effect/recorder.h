#ifndef RECORDER_H
#define RECORDER_H

#include "effect.h"

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

        recordValuePackage* data;
        int valuePackageSize;
};

}; /* namespace simulation */
}; /* namespace vemc2 */

#endif // RECORDER_H
