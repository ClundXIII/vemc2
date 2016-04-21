#include "recorder.h"
#include "../universe.h"

using namespace vemc2::simulation;

recorder::recorder(vemc2::universe *globUniversets):
    effect(globUniversets)
    {
    setPriority(99);
    data = new recordValuePackage[256];
    valuePackageSize =0;
}

recorder::~recorder(){
    delete[] data;
}

int recCount;
int buffer_pos=0;
void recorder::tick(){

    if (buffer_pos >= RECBUFFERSIZE){
        buffer_pos = 0;
        globUniverse->out << "recorder buffer overflow" << Vesper::LoggingTypes::eom;
    }

    for (int i=0; i<valuePackageSize; i++){
        data[i].buffer[buffer_pos] = *(data[i].toRecord);
    }

    buffer_pos++;

    if (recCount>1000){
        for (int i=0; i<valuePackageSize; i++){
            globUniverse->out << data[i].label << ": " << *(data[i].toRecord) << data[i].unit << Vesper::LoggingTypes::eom;
        }
        recCount = 0;
    }
    else {
        recCount++;
    }
}

int recorder::push_value(bdt *toRecord, const char* label, const char* unit){
    if (valuePackageSize >= 256)
        return 1;
    data[valuePackageSize].toRecord = toRecord;
    data[valuePackageSize].label    = label;
    data[valuePackageSize].unit     = unit;
    valuePackageSize++;

    return 0;
}

int recorder::writeToFile(const char* filename){
}
