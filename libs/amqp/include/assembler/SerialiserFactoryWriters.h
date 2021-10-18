#pragma once

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

/******************************************************************************/

/*
 * Since we can't partially specialise functions we need
 * to pull out the writing of single values into two functions. Use
 * basic meta-programing to switch between primitives and
 * composites
 */
template<typename T,  bool = std::is_base_of<Serializable , T>::value>
struct SingleWriter {
    static void write (T propertyValue_, ModifiableAMQPBlob & blob_, const SerialiserFactory & sf_) {
        DBG ("  SingleWriter::" << javaTypeName<T>() << " - primitive" << std::endl); // NOLINT
        dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_).writePrimitiveSingle<T>(
            propertyValue_);
    }
};

/******************************************************************************/

/*
 * Specialisation to handle the composite case, basically anything which
 * implements Serializable.
 */
template<typename T>
struct SingleWriter<T, true> {
    static void write (T propertyValue_, ModifiableAMQPBlob & blob_, const SerialiserFactory & sf_) {
        DBG ("  SingleWriter::" << javaTypeName<T>() << " - serialise" << std::endl); // NOLINT
        propertyValue_.serialise (sf_, blob_);
    }
};

/******************************************************************************/

/*
 * Similar to the above, save for properties of composites
 */
template<
    typename T,
    bool = std::is_base_of_v<Serializable , std::remove_pointer_t<T>>,
    bool = std::is_pointer_v<T>>
struct PropertyWriter {
    static void write (
        T propertyValue_,
        const std::string & propertyName_,
        const Serializable & clazz_,
        ModifiableAMQPBlob & blob_,
        const SerialiserFactory & sf_
    ) {
        auto & b = dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_);
        b.writePrimitive<T> (
            propertyValue_, propertyName_, std::remove_reference_t<decltype(b)>::key (clazz_));
    }
};

/******************************************************************************/

template<typename T>
struct NonPrimWriter {
    static void write (
        const std::string & type_,
        const std::string & propertyName_,
        const Serializable & parent_,
        internal::ModifiableAMQPBlobImpl & blob_
    ) {
        blob_.writeComposite (propertyName_, type_, parent_);
    }
};

/******************************************************************************/

template<typename A, typename B>
struct NonPrimWriter<amqp::serializable::SerializableVector<A, B>> {
    static void write (
        const std::string & type_,
        const std::string & propertyName_,
        const Serializable & parent_,
        internal::ModifiableAMQPBlobImpl & blob_
    ) {
        blob_.writeRestricted (propertyName_, type_, parent_);
    }
};

/******************************************************************************/

template<typename A, typename B, typename C, typename D>
struct NonPrimWriter<amqp::serializable::SerializableMap<A, B, C, D>> {
    static void write (
        const std::string & type_,
        const std::string & propertyName_,
        const Serializable & parent_,
        internal::ModifiableAMQPBlobImpl & blob_
    ) {
        blob_.writeRestricted (propertyName_, type_, parent_);
    }
};

/******************************************************************************/

/**
 * specialisation for non pointer composites
 */
template<typename T>
struct PropertyWriter<T, true, false> {
    static void write (
        T propertyValue_,
        const std::string & propertyName_,
        const Serializable & parent_,
        ModifiableAMQPBlob & blob_,
        const SerialiserFactory & sf_
    ) {
        auto type = javaTypeName<std::remove_reference_t<std::remove_pointer_t<T>>>();
        auto & blob = dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_);

        NonPrimWriter<T>::write (type, propertyName_, parent_, blob);

        propertyValue_.serialise (sf_, blob_);
    }
};

/******************************************************************************/

/**
 * specialisation for pointer composites
 */
template<typename T>
struct PropertyWriter<T, true, true> {
    static void write (
        T propertyValue_,
        const std::string & propertyName_,
        const Serializable & parent_,
        ModifiableAMQPBlob & blob_,
        const SerialiserFactory & sf_
    ) {
        auto type = javaTypeName<std::remove_reference_t<std::remove_pointer_t<T>>>();
        auto & blob = dynamic_cast<internal::ModifiableAMQPBlobImpl &>(blob_);

        NonPrimWriter<T>::write (type, propertyName_, parent_, blob);

        if (propertyValue_) {
            propertyValue_->serialise (sf_, blob_);
        } else {
            blob.writeNull (propertyName_, type, parent_);
        }
    }
};

/******************************************************************************/

} // namespace amqp::assembler

/******************************************************************************/
