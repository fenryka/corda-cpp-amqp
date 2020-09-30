#pragma once

/******************************************************************************/

#include "amqp/src/serialiser/serialisers/PropertySerialiser.h"
#include "BoolPropertySerialiserBase.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    template <class Reader, class Writer>
    class BoolPropertySerialiser final
            : public PropertySerialiser<Reader, Writer>
            , public BoolPropertySerialiserBase
    {
        public :
            [[nodiscard]] const std::string & name() const override { return m_name; }
            [[nodiscard]] const std::string & type() const override { return m_type; }
    };

}

/******************************************************************************/

