#pragma once

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

    template<class T, bool = std::is_pointer_v<T>>
    struct ReadPrimitive {
        static
        T
        read(const AMQPBlob &blob_) {
            T v;
            amqp::internal::serialiser::PrimToSerialiser<
                    std::remove_const_t<T>
            >::get(&v, blob_.data());

            return v;
        }
    };

}

/******************************************************************************/

namespace amqp::assembler {

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

/******************************************************************************/
