#pragma once

#include <string>

namespace amqp::internal::schema::types {

    std::string unbox (const std::string &);

    std::pair<std::string, std::string> listType (const std::string &);

    bool isContainer (const std::string &);
    bool isArray (const std::string &);

}
