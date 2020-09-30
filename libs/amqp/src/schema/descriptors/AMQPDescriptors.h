#pragma once

/******************************************************************************/

#include <set>
#include <map>
#include <string>
#include <memory>
#include <iostream>

#include "corda-utils/include/types.h"

#include "proton-wrapper/include/proton_wrapper.h"

#include "AMQPDescriptor.h"
#include "described-types/Descriptor.h"
#include "AMQPDescriptorRegistory.h"

/******************************************************************************/

struct pn_data_t;

/******************************************************************************/

namespace amqp::internal::schema::descriptors {

    /**
     * Look up a described type by its ID in the AMQPDescriptorRegistry and
     * return the corresponding schema type. Specialised below to avoid
     * the cast and re-owning of the unique pointer when we're happy
     * with a simple uPtr<AMQPDescribed>
     */
    template<class T>
    uPtr <T>
    dispatchDescribed (pn_data_t *data_) {
        proton::assert_described(data_);
        proton::auto_enter p (data_);
        proton::is_ulong (data_);

        auto id = pn_data_get_ulong (data_);

        return uPtr<T> (
            static_cast<T *> (
                AMQPDescriptorRegistory[id]->build (data_).release()));
    }
}

/******************************************************************************/

namespace amqp::internal::schema::descriptors {

    class ReferencedObjectDescriptor final : public AMQPDescriptor {
        public :
            ReferencedObjectDescriptor() : AMQPDescriptor() { }

            ReferencedObjectDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            ~ReferencedObjectDescriptor() final = default;

            std::unique_ptr<amqp::schema::ISchemaElement> build (pn_data_t *) const override;
    };

}

/******************************************************************************/

namespace amqp::internal::schema::descriptors {

    class TransformSchemaDescriptor final : public AMQPDescriptor {
        public :
            TransformSchemaDescriptor() : AMQPDescriptor() { }

            TransformSchemaDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            ~TransformSchemaDescriptor() final = default;

            std::unique_ptr<amqp::schema::ISchemaElement> build (pn_data_t *) const override;
    };

}

/******************************************************************************/

namespace amqp::internal::schema::descriptors {

    class TransformElementDescriptor final : public AMQPDescriptor {
        public :
            TransformElementDescriptor() : AMQPDescriptor() { }

            TransformElementDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            ~TransformElementDescriptor() final = default;

            std::unique_ptr<amqp::schema::ISchemaElement> build (pn_data_t *) const override;
    };

}

/******************************************************************************/

namespace amqp::internal::schema::descriptors {

    class TransformElementKeyDescriptor final : public AMQPDescriptor {
        public :
            TransformElementKeyDescriptor() : AMQPDescriptor() { }

            TransformElementKeyDescriptor(const std::string & symbol_, int val_)
                : AMQPDescriptor(symbol_, val_)
            { }

            ~TransformElementKeyDescriptor() final = default;

            std::unique_ptr<amqp::schema::ISchemaElement> build (pn_data_t *) const override;
    };

}

/******************************************************************************/
