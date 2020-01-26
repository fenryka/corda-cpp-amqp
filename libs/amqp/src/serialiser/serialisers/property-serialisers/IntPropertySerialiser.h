#pragma once

/******************************************************************************/

#include "PropertySerialiser.h"

#include "amqp/include/serialiser/reader/IReader.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    template <class Reader>
    class IntPropertySerialiser : public PropertySerialiser<Reader> {
        private :
            static const std::string m_name;
            static const std::string m_type;

        public :
            const std::string & name() const override { return m_name; }
            const std::string & type() const override { return m_type; }
    };

}

/******************************************************************************/

template<typename Reader>
const std::string
amqp::internal::serialiser::serialisers::IntPropertySerialiser<Reader>::m_name { // NOLINT
        "Integer Serialiser"
};

template<typename Reader>
const std::string
amqp::internal::serialiser::serialisers::IntPropertySerialiser<Reader>::m_type { // NOLINT
        "int"
};

/******************************************************************************/
