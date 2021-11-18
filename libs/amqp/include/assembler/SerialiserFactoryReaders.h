#pragma once

/******************************************************************************/

#include "amqp/include/AMQPBlob.h"
#include "amqp/src/ModifiableAMQPBlobImpl.h"

#include "ReadPrimitive.h"
#include "ReadNonPrimitive.h"

/******************************************************************************/

namespace amqp {

    namespace serializable {
        class SerializableBase;
        template<typename, typename, typename, typename> class SerializableMap;
    }

    namespace assembler {
        class SerialiserFactory;
    }

}

/******************************************************************************/

namespace amqp::assembler {

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

            return ReadNonPrim<T>::read (blob_, sf_);
        }
    };

} // amqp::assembler

/******************************************************************************/
