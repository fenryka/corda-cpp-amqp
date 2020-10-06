#pragma once

#include "corda-utils/include/types.h"

#include <map>

/******************************************************************************
 *
 * Forward class declarations
 *
 ******************************************************************************/

namespace amqp {

    class AMQPBlob;

}

namespace amqp::serializable {

    class Serializable;

}

/******************************************************************************
 *
 * class amqp::ModifiableAMQPBlob
 *
 ******************************************************************************/

namespace amqp {

    class ModifiableAMQPBlob {
        public :
            ModifiableAMQPBlob() = default;

            virtual ~ModifiableAMQPBlob() = default;

            [[nodiscard]] virtual uPtr<AMQPBlob> toBlob() const = 0;
    };

}

/******************************************************************************/

