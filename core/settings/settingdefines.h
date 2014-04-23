#ifndef SETTINGDEFINES_H_INCLUDED
#define SETTINGDEFINES_H_INCLUDED

#include <string>

namespace vemc2{
namespace settings{

    bool setBool(std::string setString);
    void setString(std::string setString, std::string toSet);

}; /* namespace settings */
}; /* namespace vemc2 */

#endif // SETTINGDEFINES_H_INCLUDED
