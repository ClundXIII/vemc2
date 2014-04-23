#include "settings.h"
#include "settingdefines.h"

#include <iostream>

#define StringA (String1+count1)
#define StringB (String2+count2)

#define StringEnd \000

using namespace vemc2;

bool settings::compareSetting(char* String1, const char* String2){
    int count1=0, count2=0;
    while (*(String1+count1) == ' ') count1++;
    while (*(String1+count2) == ' ') count2++;

    while ((*StringA != '\0') && (*StringB != '\0')){

        if ((*StringA == '=') && (*StringB == '=')) return true;
        if ((*StringA == ' ') && (*StringB == ' ')) return true;
        if ((*StringA == '|') && (*StringB == '|')) return true;

        if (*StringA != *StringB) return false;

        count1++;
        count2++;
    }

    return true;
}

char* settings::getRest(char* setString){
    char *retWert = new char[256];

    while ( (*setString != '=') && (*setString != ' ') && (*setString != '|') && (*setString != '\0'))
        setString++;

    if (setString == '\0') return 0;

    *setString = '\0';
    setString++;

    int i=0;
    for (;setString[i] != 0; i++)
        retWert[i] = setString[i];

    retWert[i] = '\0';

    return retWert;
}

bool settings::setBool(std::string setString){
    if (setString == "true")  return true;
    if (setString == "t")     return true;
    if (setString == "1")     return true;
    if (setString == "false") return false;
    if (setString == "f")     return false;
    if (setString == "0")     return false;
    return false;
}
