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

namespace amqp::serializable {

    class Serializable;

}

#include "amqp/src/ModifiableAMQPBlobImpl.h"

/******************************************************************************/

namespace amqp::assembler {
    using Serializable = amqp::serializable::Serializable;

    class SerialiserFactory {
        private :
            /*
             * Since we can't partially specialise functions we need
             * to pull out the writing of single values into two functions. Use
             * basic meta-programing to switch between primitives and
             * composites
             */
            template<typename T,  bool = std::is_base_of<Serializable , T>::value>
            struct SingleWriter {
                static void write (T propertyValue_, ModifiableAMQPBlob & blob_, const SerialiserFactory & sf_) {
                    dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).writePrimitiveSingle<T>(
                        propertyValue_);
                }
            };

            /*
             * Specialisation to handle the composite case, basically anything which
             * implements Serializable.
             */
            template<typename T>
            struct SingleWriter<T, true> {
                static void write (T propertyValue_, ModifiableAMQPBlob & blob_, const SerialiserFactory & sf_) {
                    propertyValue_.serialise (sf_, blob_);
                }
            };

        public :
            [[nodiscard]] virtual uPtr<ModifiableAMQPBlob> blob() const = 0;

            static void startComposite (const Serializable & clazz_, ModifiableAMQPBlob & blob_) {
                dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).startComposite (clazz_);
            }

            static void endComposite (const Serializable & clazz_, ModifiableAMQPBlob & blob_) {
                dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).endComposite (clazz_);
            }

            static void startRestricted (const Serializable & clazz_, ModifiableAMQPBlob & blob_)  {
                dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).startRestricted (clazz_);
            }

            static void endRestricted (const Serializable & clazz_, ModifiableAMQPBlob & blob_)  {
                dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).endRestricted (clazz_);
            }

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

            template<typename T>
            void write (
                T propertyValue_,
                const std::string & propertyName_,
                const Serializable & clazz_,
                ModifiableAMQPBlob & blob_
            ) const {
                dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).writePrimitive<T> (
                    propertyValue_, propertyName_, clazz_);
            }

            template<typename T>
            void writeSingle (
                T propertyValue_,
                const Serializable & clazz_,
                ModifiableAMQPBlob & blob_
            ) const {
                SingleWriter<T>::write (propertyValue_, blob_, *this);
            }
    };

}

/******************************************************************************/
