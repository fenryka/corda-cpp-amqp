#pragma once

/******************************************************************************/

#include "PropertySerialiser.h"
#include "StringPropertySerialiserBase.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    template <class Reader, class Writer>
    class StringPropertySerialiser
            : public PropertySerialiser<Reader, Writer>
            , public StringPropertySerialiserBase
    {
        public :
            const std::string & name() const override {
                return m_name;
            }

            const std::string & type() const override {
                return m_type;
            }
    };

}

/******************************************************************************/

