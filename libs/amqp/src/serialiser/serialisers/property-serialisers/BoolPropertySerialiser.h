#pragma once

/******************************************************************************/

#include "PropertySerialiser.h"
#include "BoolPropertySerialiserBase.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    template <class Reader, class Writer>
    class BoolPropertySerialiser
            : public PropertySerialiser<Reader, Writer>
            , public BoolPropertySerialiserBase
    {
        public :
            const std::string & name() const override { return m_name; }
            const std::string & type() const override { return m_type; }
    };

}

/******************************************************************************/

