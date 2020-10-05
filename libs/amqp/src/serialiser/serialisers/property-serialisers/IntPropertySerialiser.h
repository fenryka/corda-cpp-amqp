#pragma once

/******************************************************************************/

#include "amqp/src/serialiser/serialisers/PropertySerialiser.h"

#include "IntPropertySerialiserBase.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    template <class Reader, class Writer>
    class IntPropertySerialiser
            : public PropertySerialiser<Reader, Writer>
            , public IntPropertySerialiserBase
    {
        public :
            [[nodiscard]] const std::string & name() const override { return m_name; }
            [[nodiscard]] const std::string & type() const override { return m_type; }
    };

}

/******************************************************************************/
