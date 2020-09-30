#pragma once

/******************************************************************************/

#include "amqp/src/serialiser/serialisers/PropertySerialiser.h"

#include "LongPropertySerialiserBase.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    template <class Reader, class Writer>
    class LongPropertySerialiser
            : public PropertySerialiser<Reader, Writer>
            , public LongPropertySerialiserBase
    {
        public :
            const std::string & name() const override { return m_name; }
            const std::string & type() const override { return m_type; }
    };

}

/******************************************************************************/

