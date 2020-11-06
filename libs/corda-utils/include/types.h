#pragma once

/******************************************************************************/

#include <map>
#include <list>
#include <vector>
#include <memory>
#include <string>

#include <cxxabi.h>

#include <iostream>

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

/******************************************************************************
 *
 * Forward declarations
 *
 ******************************************************************************/

template<class T>
std::string
javaTypeName ();

/******************************************************************************/

template<typename>
struct [[maybe_unused]] is_std_vector : std::false_type {
    static std::string fun() {
        throw std::runtime_error ("never call this method");
    }
};

template<typename T, typename A>
struct [[maybe_unused]] is_std_vector<std::vector<T,A>> : std::true_type {
    static std::string fun() {
        return "java.util.List<" + javaTypeName<T>() + ">";
    }
};

/******************************************************************************/

template<typename>
struct [[maybe_unused]] is_std_map : std::false_type {
    static std::string fun() {
        throw std::runtime_error ("never call this method");
    }
};

template<typename K, typename V, typename C, typename A>
struct [[maybe_unused]] is_std_map<std::map<K, V, C, A>> : std::true_type {
    static std::string fun() {
        return "java.util.Map<" + javaTypeName<K>() + "," + javaTypeName<V>() + ">";
    }
};

/******************************************************************************/

template<class T>
std::string
javaTypeName () {
    const std::string find { "::" };
    const std::string replace { "." };

    if (is_std_vector<T>::value) {
        return is_std_vector<T>::fun();
    } else if (is_std_map<T>::value) {
        return is_std_map<T>::fun();
    }

    std::string str { typeName<T>() };

    size_t pos { 0 };
    while ((pos = str.find(find, pos)) != std::string::npos) {
        str.replace(pos, find.length(), replace);
        pos += replace.length();
    }

    return str;
}

/******************************************************************************/

/*
 * We need a specialisation for string since we don't want it spitting out
 * all of the STL nonsense around allocators and char types
 */
template<>
std::string
javaTypeName<std::string> ();

/******************************************************************************/
