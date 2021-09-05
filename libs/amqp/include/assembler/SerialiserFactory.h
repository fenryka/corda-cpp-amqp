#pragma once

/******************************************************************************/

#include "amqp/include/AMQPBlob.h"

#include "amqp/src/ModifiableAMQPBlobImpl.h"

#include "SerialiserFactoryWriters.h"
#include "SerialiserFactoryReaders.h"

/******************************************************************************
 *
 * Forward class declarations
 *
 ******************************************************************************/

namespace amqp::serializable {

    class Serializable;
    class RestrictedSerializable;

    template<typename, typename> class SerializableVector;
    template<typename, typename, typename, typename> class SerializableMap;

}

/******************************************************************************
 *
 * amqp::assembler::SerialiserFactory
 *
 ******************************************************************************/

namespace amqp::assembler {

    using Serializable = amqp::serializable::Serializable;
    using RestrictedSerializable = amqp::serializable::RestrictedSerializable;

    class SerialiserFactory {
        public :
            [[nodiscard]] virtual uPtr<ModifiableAMQPBlob> blob() const = 0;

            static void startComposite (
                const Serializable & clazz_,
                ModifiableAMQPBlob & blob_
            ) {
                dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).startComposite (clazz_);
            }

            static void endComposite (
                const Serializable & clazz_,
                ModifiableAMQPBlob & blob_
            ) {
                dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).endComposite (clazz_);
            }

            static void startRestricted (
                const RestrictedSerializable & clazz_,
                ModifiableAMQPBlob & blob_
            )  {
                dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).startRestricted (clazz_);
            }

            static void endRestricted (
                const RestrictedSerializable & clazz_,
                ModifiableAMQPBlob & blob_
            )  {
                dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).endRestricted (clazz_);
            }

            template<typename T>
            void write (
                T propertyValue_,
                const std::string & propertyName_,
                const Serializable & clazz_,
                ModifiableAMQPBlob & blob_
            ) const {
                PropertyWriter<T>::write (propertyValue_, propertyName_, clazz_, blob_, *this);
            }

            template<typename T>
            void writeSingle (
                T propertyValue_,
                const Serializable & clazz_,
                ModifiableAMQPBlob & blob_
            ) const {
                SingleWriter<T>::write (propertyValue_, blob_, *this);
            }

            template<typename T>
            T
            read (
                const AMQPBlob & blob_
            ) const {
                DBG (__FUNCTION__ << " - " << typeName<T>() << std::endl); // NOLINT
                return PropertyReader<T>::read (blob_, *this);
            }

            template<typename T>
            T
            readSingle (
                const AMQPBlob & blob_
            ) const {
                DBG (__FUNCTION__ << " - " << typeName<T>() << std::endl); // NOLINT
                return PropertyReader<T>::read (blob_, *this);
            }

            template<typename T>
            T
            deserialise (const AMQPBlob & blob_) {
                DBG (__FUNCTION__ << ":-:" << typeName<T>() << std::endl); // NOLINT
                blob_.readyPayload ();

                return PropertyReader<T>::read (blob_, *this);
            }
    };
}

/******************************************************************************/
