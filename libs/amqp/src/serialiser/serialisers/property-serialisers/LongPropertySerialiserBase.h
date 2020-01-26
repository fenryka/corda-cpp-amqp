#pragma once

/******************************************************************************/

#include <string>

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    /**
     * Allows us to define our static consts outside a header file since
     * [LongPropertySerialiser] is a templated class
     */
    class LongPropertySerialiserBase {
        protected:
            static const std::string m_name;
            static const std::string m_type;
    };

}

/******************************************************************************/
