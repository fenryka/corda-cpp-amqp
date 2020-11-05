#pragma once

#include "amqp/include/ModifiableAMQPBlob.h"

#include "corda-utils/include/types.h"
#include "corda-utils/include/debug.h"
#include "amqp/src/schema/descriptors/corda-descriptors/FieldDescriptor.h"
#include "amqp/include/serializable/Serializable.h"

#include "serialiser/Serialiser.h"
#include "serialiser/serialisers/property-serialisers/IntPropertySerialiserBase.h"
#include "serialiser/serialisers/property-serialisers/StringPropertySerialiserBase.h"
#include "serialiser/serialisers/property-serialisers/BoolPropertySerialiserBase.h"
#include "serialiser/serialisers/property-serialisers/DoublePropertySerialiserBase.h"
#include "serialiser/serialisers/property-serialisers/LongPropertySerialiserBase.h"
#include "serialiser/serialisers/property-serialisers/FloatPropertySerialiserBase.h"

#include <map>
#include <cassert>
#include <amqp/src/schema/descriptors/corda-descriptors/CompositeDescriptor.h>
#include <amqp/src/schema/descriptors/corda-descriptors/RestrictedDescriptor.h>

/******************************************************************************
 *
 * class amqp::ModifiableAMQPBlob
 *
 ******************************************************************************/

namespace amqp::internal {

    struct BaseBlob {
        virtual ~BaseBlob () = default;

        [[nodiscard]] virtual size_t size () const = 0;

        [[nodiscard]] virtual pn_data_t *make (const std::string &, const std::string &) const = 0;
    };

    struct CompositeBlob : public BaseBlob {
        std::map<std::string, pn_data_t *> m_schemas;

        decltype (m_schemas.end ()) end () {
            return m_schemas.end ();
        }

        [[nodiscard]] size_t size () const override {
            return m_schemas.size ();
        }

        [[nodiscard]] pn_data_t * make (
            const std::string &name_,
            const std::string &fingerprint
        ) const override {
            DBG (__FUNCTION__ << std::endl);
            return schema::descriptors::CompositeDescriptor::makeProton (
                name_, {}, fingerprint, m_schemas);
        }
    };

    struct ListBlob : public BaseBlob {
        const std::string m_source = "list";

        ListBlob () = default;

        [[nodiscard]] size_t size () const override {
            return 0;
        }

        [[nodiscard]] pn_data_t * make (
            const std::string &name_,
            const std::string &fingerprint_
        ) const override {
            DBG (__FUNCTION__ << std::endl);
            return schema::descriptors::RestrictedDescriptor::makeProton (
                name_,
                m_source,
                fingerprint_);
        }
    };

}

/******************************************************************************/

namespace amqp::internal {

    class ModifiableAMQPBlobImpl : public amqp::ModifiableAMQPBlob {
        private :
            pn_data_t * m_payload;

            /*
             * Maps { Name, Fingerprint } to { }
             */
            std::map<
                std::pair<std::string, std::string>,
                uPtr<BaseBlob>> m_schemas;

        public :
            ModifiableAMQPBlobImpl();

            static std::pair<std::string, std::string> key (
                const amqp::serializable::Serializable &);

            void startComposite (
                const amqp::serializable::Serializable &);

            void endComposite (
                const amqp::serializable::Serializable &);

            void startRestricted (
                const amqp::serializable::Serializable &);

            void writeComposite_ (
                const std::string &,
                const std::string &,
                const amqp::serializable::Serializable &);

            void writeRestricted_ (
                const std::string &,
                const std::string &,
                const amqp::serializable::Serializable &);

            template<typename T>
            void writePrimitive(
                T,
                const std::string &,
                const amqp::serializable::Serializable &);

            template<typename T>
            void writePrimitiveSingle(T);

            void writeNull (
                const std::string &,
                const std::string &,
                const amqp::serializable::Serializable &);

            [[nodiscard]] uPtr<AMQPBlob> toBlob() const override;

            void dump() const;
    };

}

/******************************************************************************/

/*
 * Allows us to handle primitive types that are either a pointer or
 * not
 */
template<typename T>
struct Writer {
    static void write (T propertyValue_, pn_data_t * payload_) {
        amqp::internal::serialiser::PrimToSerialiser<
            std::remove_const_t<T>
        >::put (&propertyValue_, payload_);
    }
};

template<typename T>
struct Writer<T &> {
    static void write (T & propertyValue_, pn_data_t * payload_) {
        amqp::internal::serialiser::PrimToSerialiser<
            std::remove_const_t<T>
        >::put (&propertyValue_, payload_);
    }
};

template<typename T>
struct Writer<T *> {
    static void write (T * propertyValue_, pn_data_t * payload_) {
        amqp::internal::serialiser::PrimToSerialiser<
            std::remove_const_t<T>
        >::put (propertyValue_, payload_);
    }
};

template<typename T>
void
amqp::internal::
ModifiableAMQPBlobImpl::writePrimitive (
    T propertyValue_,
    const std::string & propertyName_,
    const amqp::serializable::Serializable & clazz_)
{
    DBG (__FUNCTION__ << "::" << propertyName_ << "::"<< propertyValue_ << std::endl); // NOLINT

    auto id = key (clazz_);

    assert (m_schemas.find (id) != m_schemas.end());

    auto & blob = dynamic_cast<CompositeBlob &>(*m_schemas[id]);

    if (blob.m_schemas.find (propertyName_) == blob.m_schemas.end()) {
        blob.m_schemas[propertyName_] =
            internal::schema::descriptors::FieldDescriptor::makeProton (
                propertyName_,
                serialiser::PrimToSerialiser<
                    std::remove_const_t<
                        std::remove_reference_t<
                            std::remove_pointer_t<
                                std::remove_const_t<T>>>>>::serialiser::m_type,
                {},
                "", "",
                std::is_pointer_v<T>,
                false);
    }

    DBG ("WRITE IT" << std::endl); // NOLINT

    Writer<T>::write(propertyValue_, m_payload);
}

/******************************************************************************/

template<typename T>
void
amqp::internal::
ModifiableAMQPBlobImpl::writePrimitiveSingle (
    T propertyValue_)
{
    DBG (__FUNCTION__ << "::" << propertyValue_ << std::endl); // NOLINT

    Writer<T>::write (propertyValue_, m_payload);
}

/******************************************************************************/
