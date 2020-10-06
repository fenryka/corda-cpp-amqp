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
            [[nodiscard]] virtual uPtr<ModifiableAMQPBlob> blob() const = 0;

            virtual void startComposite (
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &
            ) const = 0;

            virtual void writeComposite (
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &
            ) const = 0;

            virtual void writeInt (
                int,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &
            ) const = 0;

            virtual void writeString (
                const std::string &,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &
            ) const = 0;

            virtual void writeLong (
                long,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &
            ) const = 0;

            virtual void writeBool(
                bool,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &
            ) const = 0;
    };

}
/******************************************************************************/
