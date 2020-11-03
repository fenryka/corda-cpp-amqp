#pragma once

/******************************************************************************/

#include "amqp/src/serialiser/serialisers/PropertySerialiser.h"
#include "FloatPropertySerialiserBase.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    template <class Reader, class Writer>
    class FloatPropertySerialiser final
            : public PropertySerialiser<Reader, Writer>
            , public FloatPropertySerialiserBase
    {
        public :
            [[nodiscard]] const std::string & name() const override { return m_name; }
            [[nodiscard]] const std::string & type() const override { return m_type; }
    };

}

/******************************************************************************/

