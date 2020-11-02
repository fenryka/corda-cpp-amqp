#include "corda-utils/include/types.h"

#include <string>

/******************************************************************************/

template<>
std::string
javaTypeName<std::string> () {
    return "String";
}

/******************************************************************************/
