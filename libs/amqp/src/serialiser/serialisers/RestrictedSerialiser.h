
#pragma once

/******************************************************************************/

#include "Serialiser.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    template <class Reader, class Writer>
    class RestrictedSerialiser : public Serialiser<Reader, Writer> {
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

template<class Reader, class Writer>
const std::string
amqp::internal::serialiser::serialisers::RestrictedSerialiser<Reader, Writer>::m_name { // NOLINT
        "Restricted Serialiser"
};

/******************************************************************************/
