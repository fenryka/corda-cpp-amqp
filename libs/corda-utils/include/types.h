#pragma once

/******************************************************************************/

#include <map>
#include <list>
#include <vector>
#include <memory>
#include <string>
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
    typedef std::remove_pointer_t<T> T2;
    typedef std::remove_pointer_t<T2> T3;

    status = 0;
    return abi::__cxa_demangle (
        typeid (T3).name(),
        nullptr,
        nullptr, &status);
}

/******************************************************************************/

template<typename T>
constexpr
char *
typeName () {
    typedef std::remove_pointer_t<T> T2;
    typedef std::remove_pointer_t<T2> T3;

    int status = 0;
    return abi::__cxa_demangle (
        typeid (T3).name(),
        nullptr,
        nullptr, &status);
}

/******************************************************************************/

template<class T>
std::string
javaTypeName () {
    const std::string find { "::" };
    const std::string replace { "." };
    std::string str { typeName<T>() };

    size_t pos { 0 };
    while ((pos = str.find(find, pos)) != std::string::npos) {
        str.replace(pos, find.length(), replace);
        pos += replace.length();
    }

    return str;
}

/******************************************************************************/
