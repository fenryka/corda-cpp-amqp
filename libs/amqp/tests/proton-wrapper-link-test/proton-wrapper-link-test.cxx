#include <iostream>

#include "proton-wrapper/include/proton_wrapper.h"

int
main() {
//    std::cout << proton::readAndNext<std::string>(nullptr, __FILE__, __LINE__) << std::endl;
    std::cout << proton::readAndNext<int32_t>(nullptr, __FILE__, __LINE__, true) << std::endl;
}