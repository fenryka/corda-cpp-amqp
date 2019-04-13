
#include "Schema.h"

#include <iostream>

/******************************************************************************/

namespace {

    using CompositeMap = std::map<
        std::string,
        std::unique_ptr<amqp::internal::schema::Composite>>;

}

/******************************************************************************/

std::ostream &
amqp::internal::schema::
operator << (std::ostream & stream_, const Schema & schema_) {
    for (auto const & type : schema_.m_types) {
        stream_ << type.first << std::endl;
        stream_ << *type.second << std::endl;
    }

    return stream_;
}

/******************************************************************************/

const CompositeMap &
amqp::internal::schema::
Schema::types() const {
    return m_types;
}

/******************************************************************************/

