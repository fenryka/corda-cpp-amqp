#pragma once

/******************************************************************************/


namespace amqp {

    class ModifiableAMQPBlob;

    namespace serializable {

        class Serializable;

    }

}

/******************************************************************************/

namespace amqp::assembler {

    class SerialiserFactory {
        public :
            virtual void writeComposite (
                    const amqp::serializable::Serializable &,
                    ModifiableAMQPBlob &) const = 0;

            virtual void writeInt(
                    int,
                    const std::string &,
                    const amqp::serializable::Serializable &,
                    ModifiableAMQPBlob &) const = 0;

    };

}
/******************************************************************************/
