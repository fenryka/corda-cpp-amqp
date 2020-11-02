#pragma once

/******************************************************************************
 *
 * These need to exist since we cannot rely on __type__ not being null
 *
 ******************************************************************************/

#define writeComposite(__type__, __name__, __parent__, __blob__) \
    writeComposite_ ( \
        javaTypeName<decltype (__type__)>(), &__type__, __name__, *this, __blob__);

#define writeRestricted(__type__, __name__, __parent__, __blob__) \
    writeRestricted_ (                                            \
        javaTypeName<                                             \
            std::remove_reference_t<                              \
                std::remove_pointer_t<decltype (__type__)>>       \
        >(), &__type__, __name__, *this, __blob__);

/******************************************************************************/

namespace amqp {

    class ModifiableAMQPBlob;

}

namespace amqp::serializable {

    class Serializable;

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

            virtual void startRestricted (
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &
            ) const = 0;

            virtual void startList (
                const std::string &,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &
            ) const = 0;

            virtual void writeComposite_ (
                const std::string &,
                const amqp::serializable::Serializable *,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &
            ) const = 0;

            virtual void writeRestricted_ (
                const std::string &,
                const amqp::serializable::Serializable *,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &
            ) const = 0;

            virtual void writeInt (
                int,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &
            ) const = 0;

            virtual void writeIntPtr (
                int *,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &
            ) const = 0;

            virtual void writeStringPair (
                const std::string &,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &
            ) const = 0;

            virtual void writeStringSingle (
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &
            ) const = 0;

            virtual void writeStringPtr (
                std::string *,
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

            virtual void writeBool (
                bool,
                const std::string &,
                const amqp::serializable::Serializable &,
                ModifiableAMQPBlob &
            ) const = 0;
    };

}
/******************************************************************************/
