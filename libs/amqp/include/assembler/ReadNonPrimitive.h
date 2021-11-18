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

/******************************************************************************
 *
 * class ReadNonPrim
 *
 ******************************************************************************/

namespace amqp::assembler {

    using Serializable = amqp::serializable::SerializableBase;

    template<class T, bool = std::is_pointer_v < T>>
    struct ReadNonPrim {
        static
        T
        read(const AMQPBlob &blob_,
             const SerialiserFactory &sf_
        ) {
            DBG(__FUNCTION__ << "<" << typeName<T>()
                             << ", is_ptr " << std::is_pointer_v < T > << ">" << std::endl); // NOLINT
            const auto v = T::deserialiseImpl(sf_, blob_);

            return T{static_cast<const std::vector <std::any>>(v)};
        }
    };

    /**
     * Specialisation to read Composite pointers
     */
    template<class T>
    struct ReadNonPrim<T, true> {
        static
        T
        read(
                const AMQPBlob &blob_,
                const SerialiserFactory &sf_
        ) {
            typedef std::remove_pointer_t <T> rtn_t;
            DBG(__FUNCTION__ << "<" << typeName<T>() << ", true>" << std::endl); // NOLINT

            const auto v = rtn_t::deserialiseImpl(sf_, blob_);

            return new rtn_t{v};
        }
    };

    template<typename A, typename B>
    struct ReadNonPrim<amqp::serializable::SerializableVector<A, B>, true> {
        static
        amqp::serializable::SerializableVector<A, B>
        read(const AMQPBlob &blob_, const SerialiserFactory &sf_) {
            throw std::logic_error("ReadNonPrim HEAP no worky yet");
        }
    };

    template<typename A, typename B>
    struct ReadNonPrim<amqp::serializable::SerializableVector<A, B>, false> {
        static
        amqp::serializable::SerializableVector<A, B>
        read(const AMQPBlob &blob_, const SerialiserFactory &sf_) {
            DBG(__FUNCTION__ << std::endl);
            proton::attest_is_list(blob_.data(), __FUNCTION__, __LINE__);

            auto v = serializable::SerializableVector<A, B>::deserialiseImpl(sf_, blob_);
            return serializable::SerializableVector < A, B > {static_cast<const std::vector <std::any>>(v)};
        }
    };
}

/******************************************************************************/

