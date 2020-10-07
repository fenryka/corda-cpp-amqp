#pragma once

/******************************************************************************/

#include <map>
#include <list>
#include <vector>
#include <memory>
#include <cxxabi.h>

/******************************************************************************/

template<typename T>
using uPtr = std::unique_ptr<T>;

template<typename T>
using sPtr = std::shared_ptr<T>;

template<typename T>
using sVec = std::vector<T>;

template<typename T>
using sList = std::list<T>;

template<typename T>
using upStrMap_t [[maybe_unused]] = std::map<std::string, uPtr<T>>;

template<typename T>
using spStrMap_t = std::map<std::string, sPtr<T>>;

template<typename T>
constexpr
char *
typeName (int & status) {
    status = 0;
    return abi::__cxa_demangle (
        typeid (std::remove_pointer_t<T>).name (),
        nullptr,
        nullptr, &status);
}

/******************************************************************************/

