#pragma once

/******************************************************************************/

#include "PropertySerialiser.h"

/******************************************************************************/

namespace amqp::internal::serialiser {

    template <class Reader>
    class LongPropertySerialiser : public PropertySerialiser<Reader> {
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
        amqp::internal::serialiser::LongPropertySerialiser<Reader>::m_name { // NOLINT
        "Long Serialiser"
};

template<typename Reader>
const std::string
        amqp::internal::serialiser::LongPropertySerialiser<Reader>::m_type { // NOLINT
        "long"
};

/******************************************************************************/
