#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <iostream>
#include "../universe.h"

namespace vemc2{

class parser{
    public:
        parser(vemc2::universe *pUni);

        int execute(std::string command);

    protected:

        static void execute_static(vemc2::universe *parentUniverse, std::string command);

        vemc2::universe *parentUniverse;
};

} /* namespace vemc2 */

#endif // PARSER_H_INCLUDED
