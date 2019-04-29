#pragma once

/******************************************************************************/

#include <memory>

/******************************************************************************/

template<typename T>
using upStrMap_t = std::map<std::string, std::unique_ptr<T>>;

template<typename T>
using spStrMap_t = std::map<std::string, std::shared_ptr<T>>;

/******************************************************************************/

