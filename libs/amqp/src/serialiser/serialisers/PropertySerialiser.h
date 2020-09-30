#pragma once

/******************************************************************************/

#include "Serialiser.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    template <class Reader, class Writer>
    class PropertySerialiser : public Serialiser<Reader, Writer> {
        public :
            [[nodiscard]] const std::string & name() const override = 0;

            [[nodiscard]] const std::string & type() const override = 0;
    };

}

/******************************************************************************/
