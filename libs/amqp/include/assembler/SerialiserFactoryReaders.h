#pragma once

/******************************************************************************/

#include "amqp/include/AMQPBlob.h"
#include "amqp/src/ModifiableAMQPBlobImpl.h"

/******************************************************************************/

namespace amqp {

    namespace serializable {
        class Serializable;
        class RestrictedSerializable;

        template<typename, typename> class SerializableVector;
        template<typename, typename, typename, typename> class SerializableMap;
    }

    namespace assembler {
        class SerialiserFactory;
    }

}

/******************************************************************************/

namespace amqp::assembler {

    using Serializable = amqp::serializable::Serializable;
    using RestrictedSerializable = amqp::serializable::RestrictedSerializable;

    template<class T, bool = std::is_pointer_v<T>>
    struct ReadPrimitive {
        static
        T
        read (const AMQPBlob &blob_) {
            T v;
            amqp::internal::serialiser::PrimToSerialiser<
                std::remove_const_t<T>
            >::get (&v, blob_.data ());

            return v;
        }
    };

    template<class T, bool = std::is_pointer_v<T>>
    struct ReadComposite {
        static
        T
        read (const AMQPBlob &blob_,
              const SerialiserFactory &sf_
        ) {
            DBG (__FUNCTION__ << "<" << typeName<T> ()
                              << ", is_ptr " << std::is_pointer_v<T> << ">" << std::endl); // NOLINT
            const auto v = T::deserialiseImpl (sf_, blob_);

            return T {static_cast<const std::vector<std::any>>(v)};
        }
    };

    /**
     * Specialisation to read Composite pointers
     */
    template<class T>
    struct ReadComposite<T, true> {
        static
        T
        read (
            const AMQPBlob &blob_,
            const SerialiserFactory &sf_
        ) {
            typedef std::remove_pointer_t<T> rtn_t;
            DBG (__FUNCTION__ << "<" << typeName<T> () << ", true>" << std::endl); // NOLINT

            const auto v = rtn_t::deserialiseImpl (sf_, blob_);

            return new rtn_t {v};
        }
    };


    template<
        typename T,
        bool = std::is_base_of_v<Serializable, std::remove_pointer_t<T>>>
    struct PropertyReader {
        static T read (const AMQPBlob &blob_, const SerialiserFactory &sf_) {

            struct AutoPrim {
                const AMQPBlob &m_data;

                explicit AutoPrim (const AMQPBlob &data_) : m_data (data_) {
                    DBG (__FUNCTION__ << std::endl); // NOLINT
                    m_data.startPrim ();
                }

                ~AutoPrim () {
                    DBG (__FUNCTION__ << std::endl); // NOLINT
                    m_data.endPrim ();
                }
            };

            DBG (__FUNCTION__ << "::Primitive::" << typeName<T> () << std::endl); // NOLINT

            AutoPrim ap (blob_);
            return ReadPrimitive<T>::read (blob_);
        }
    };

    template<typename T>
    struct PropertyReader<T, true> {
        static T read (
            const AMQPBlob &blob_,
            const SerialiserFactory &sf_
        ) {
            DBG (__FUNCTION__ << "::Composite::" << typeName<T> () << std::endl); // NOLINT

            struct AutoComposite {
                const AMQPBlob &m_data;

                explicit AutoComposite (const AMQPBlob &data_) : m_data (data_) {
                    DBG (__FUNCTION__ << std::endl); // NOLINT
                    m_data.startComposite ();
                }

                ~AutoComposite () {
                    DBG (__FUNCTION__ << std::endl); // NOLINT
                    m_data.endComposite ();
                }
            };

            AutoComposite ac (blob_);

            return ReadComposite<T>::read (blob_, sf_);
        }
    };


    template<class T>
    struct ReadPrimitive<T, true> {
        static
        T
        read (const AMQPBlob &blob_) {
            T v = new std::remove_pointer_t<T> {};
            amqp::internal::serialiser::PrimToSerialiser<
                std::remove_pointer_t<std::remove_const_t<T>>
            >::get (v, blob_.data ());

            return v;
        }
    };

}