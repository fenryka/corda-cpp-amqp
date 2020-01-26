
#pragma once

/******************************************************************************/

#include "amqp/src/serialiser/Serialiser.h"

/******************************************************************************/

namespace amqp::internal::serialiser {

    template <class Reader>
    class RestrictedSerialiser : public Serialiser<Reader> {
        private :
            static const std::string m_name;
            std::string m_type;

        public :
            explicit RestrictedSerialiser (std::string type_) : m_type (std::move (type_)) {}

            const std::string & name() const override  {
                return m_name;
            }

            const std::string & type() const override {
                return m_type;
            }
    };

}

/******************************************************************************/

template<typename Reader>
const std::string
        amqp::internal::serialiser::RestrictedSerialiser<Reader>::m_name { // NOLINT
        "Restricted Serialiser"
};

/******************************************************************************/
