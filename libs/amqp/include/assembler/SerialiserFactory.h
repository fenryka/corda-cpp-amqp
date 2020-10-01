#pragma once

/******************************************************************************/

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/serializable/Serializable.h"
#include "amqp/include/serialiser/ISerialiser.h"

/******************************************************************************/

namespace amqp::assembler {

    class SerialiserFactory {
        private :

            std::map<std::string, uPtr<serialiser::ISerialiser>> m_serialisers;

        public :
            [[nodiscard]] uPtr<amqp::AMQPBlob> serialize (
                    const amqp::serializable::Serializable &) const;

    };

}
/******************************************************************************/
