#pragma once

/******************************************************************************/

#include "amqp/src/serialiser/Serialiser.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    template <class Reader>
    class PropertySerialiser : public Serialiser<Reader> {
        public :
            const std::string & name() const override = 0;
            const std::string & type() const override = 0;
    };

}

/******************************************************************************/
