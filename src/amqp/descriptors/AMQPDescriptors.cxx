#include "AMQPDescriptors.h"

#include <string>
#include <iostream>
#include <proton/types.h>
#include <proton/codec.h>

#include "Field.h"
#include "Envelope.h"
#include "Composite.h"

#include "proton/proton_wrapper.h"
#include "AMQPDescriptorRegistory.h"

/******************************************************************************
 *
 *
 *
 ******************************************************************************/

namespace {

    /**
     * Look up a described type by its ID in the AMQPDescriptorRegistory and
     * return the coresponding schema type. Specialised below to avoid
     * the cast and re-owning of the unigue pointer when we're happy
     * with a simple std::unique_ptr<AMQPDescribed>
     */
    template<class T = amqp::internal::AMQPDescribed>
    std::unique_ptr<T>
    dispatchDescribed (pn_data_t * data_) {
        proton::is_described(data_);
        proton::auto_enter p (data_);
        proton::is_ulong(data_);

        auto id = pn_data_get_ulong(data_);

        return std::unique_ptr<T> (
              static_cast<T *>(amqp::AMQPDescriptorRegistory[id]->build(data_).release()));

    }

    template<>
    std::unique_ptr<amqp::internal::AMQPDescribed>
    dispatchDescribed (pn_data_t * data_) {
        proton::is_described(data_);
        proton::auto_enter p (data_);
        proton::is_ulong(data_);

        auto id = pn_data_get_ulong(data_);

        return amqp::AMQPDescriptorRegistory[id]->build(data_);
    }
}

/******************************************************************************/

void
amqp::internal::
AMQPDescriptor::validateAndNext (pn_data_t * const data_) const {
    if (pn_data_type(data_) != PN_ULONG) {
        throw std::runtime_error ("Bad type for a descriptor");
    }

    if (pn_data_get_ulong(data_) != (m_val | amqp::internal::DESCRIPTOR_TOP_32BITS)) {
        throw std::runtime_error ("Invalud Type");
    }

    pn_data_next(data_);
/*
    if (pn_data_type(data_) != PN_LIST) {
        throw std::runtime_error ("Envelope should be list");
    }
    */
}

/******************************************************************************
 *
 * amqp::internal::EnvelopeDescriptor
 *
 ******************************************************************************/

std::unique_ptr<amqp::internal::AMQPDescribed>
amqp::internal::
EnvelopeDescriptor::build(pn_data_t * data_) const {
    validateAndNext(data_);

    std::cout << "ENVELOPE: " << data_ << std::endl;

    {
        proton::auto_enter p (data_);

        /*
         * The actual blob
         */
        std::cout << "    " << data_ << std::endl;
        proton::is_described(data_);

        {
            // the type descriptor
            proton::auto_enter p (data_);
            std::cout << "    " << data_ << std::endl;

            // list of values
            pn_data_next(data_);
            std::cout << "    " << data_ << std::endl;
            {
                proton::auto_list_enter p (data_);
                while (pn_data_next(data_)) {
                    std::cout << "      data: " << data_ << std::endl;
                }
            }
        }

        pn_data_next(data_);

        /*
         * The scehama
         */
        std::cout << "----------------------" << std::endl;
        dispatchDescribed (data_);
        std::cout << "----------------------" << std::endl;

        pn_data_next(data_);

        /*
         * The transforms schema
         */
        dispatchDescribed (data_);
    }


    return std::unique_ptr<amqp::internal::schema::Envelope>(nullptr);
}

/******************************************************************************/

std::unique_ptr<amqp::internal::AMQPDescribed>
amqp::internal::
SchemaDescriptor::build(pn_data_t * data_) const {
    validateAndNext(data_);

    std::cout << "SCHEMA: " << data_ << std::endl;


    /*
     * The Schema is stored as a list of listf of described objects
     */
    {
        proton::auto_list_enter p (data_);

        for (int i (0) ; pn_data_next(data_) ; ++i) {
            proton::auto_list_enter p (data_);
            for (int j (0) ; pn_data_next(data_) ; ++j) {
                std::cout << "      : " << i << ":" << j << std::endl;
                dispatchDescribed(data_);
            }
        }
    }

    return std::unique_ptr<amqp::internal::AMQPDescribed> (nullptr);
}

/******************************************************************************
 *
 * amqp::internal::ObjectDescriptor
 *
 ******************************************************************************/

/**
 * 
 */
std::unique_ptr<amqp::internal::AMQPDescribed>
amqp::internal::
ObjectDescriptor::build(pn_data_t * data_) const {
    validateAndNext(data_);

    {
        proton::auto_enter p (data_);

        auto symbol = proton::get_symbol (data_);

        return std::make_unique<schema::Descriptor> (
                schema::Descriptor (std::string (symbol.start, symbol.size)));
    }
}

/******************************************************************************
 *
 * amqp::internal::FieldDescriptor
 *
 ******************************************************************************/

std::unique_ptr<amqp::internal::AMQPDescribed>
amqp::internal::
FieldDescriptor::build(pn_data_t * data_) const {
    validateAndNext(data_);

    proton::auto_enter p (data_);

    /* name: String */
    auto name = proton::get_string(data_);

    pn_data_next(data_);

    /* type: String */
    auto type = proton::get_string(data_);

    pn_data_next(data_);

    /* requires: List<String> */
    std::list<std::string> requires;
    {
        proton::auto_list_enter p (data_);
        while (pn_data_next(data_)) {
            requires.push_back (proton::get_string(data_));
        }
    }

    pn_data_next(data_);

    /* default: String? */
    auto def = proton::get_string(data_, true);

    pn_data_next(data_);

    /* label: String? */
    auto label = proton::get_string(data_, true);

    pn_data_next(data_);

    /* mandatory: Boolean - copes with the Kotlin concept of nullability.
       If something is mandatory then it cannot be null */
    auto mandatory = proton::get_boolean(data_);

    pn_data_next(data_);

    /* multiple: Boolean */
    auto multiple = proton::get_boolean(data_);

    return std::make_unique<schema::Field> (name, type, requires,
            def, label, mandatory, multiple);
}

/******************************************************************************
 *
 * amqp::internal::CompositeDescriptor
 *
 ******************************************************************************/

std::unique_ptr<amqp::internal::AMQPDescribed>
amqp::internal::
CompositeDescriptor::build(pn_data_t * data_) const {
    validateAndNext(data_);

    std::cout << "COMPOSITE " << data_ << std::endl;
    {
        proton::auto_enter p (data_);

        /* Class Name - String */
        auto name = proton::get_string(data_);
        std::cout << "    name: " << name << std::endl;

        pn_data_next(data_);

        /* Label Name - Nullable String */
        auto label = proton::get_string(data_, true);
        std::cout << "    label: \"" << label << "\"" << std::endl;

        pn_data_next(data_);

        /* provides: List<String> */
        {
            std::cout << "    provides: " << data_ << std::endl;
            proton::auto_list_enter p (data_);
            while (pn_data_next(data_)) {
                std::cout << "        " << data_ << std::endl;
            }
        }

        pn_data_next(data_);

        /* descriptor: Descriptor */
        auto descriptor = dispatchDescribed<schema::Descriptor>(data_);

        std::cout << "    descirption = " << descriptor->name() << std::endl;

        pn_data_next(data_);

        /* fields: List<Described>*/
        std::list<std::unique_ptr<schema::Field>> fields;
        {
            proton::auto_list_enter p (data_);
            while (pn_data_next(data_)) {
                fields.push_back (dispatchDescribed<schema::Field>(data_));
            }
        }
    }

    return std::unique_ptr<amqp::internal::schema::Composite> (nullptr);
}

/******************************************************************************/

std::unique_ptr<amqp::internal::AMQPDescribed>
amqp::internal::
RestrictedDescriptor::build(pn_data_t * data_) const {
    validateAndNext(data_);

    std::cout << "RESTRICTED " << data_ << std::endl;

    return std::unique_ptr<amqp::internal::AMQPDescribed> (nullptr);
}

/******************************************************************************/

std::unique_ptr<amqp::internal::AMQPDescribed>
amqp::internal::
ChoiceDescriptor::build(pn_data_t * data_) const {
    validateAndNext(data_);

    std::cout << "CHOICE " << data_ << std::endl;

    return std::unique_ptr<amqp::internal::AMQPDescribed> (nullptr);
}

/******************************************************************************/

std::unique_ptr<amqp::internal::AMQPDescribed>
amqp::internal::
ReferencedObjectDescriptor::build(pn_data_t * data_) const {
    validateAndNext(data_);

    std::cout << "REFERENCED OBJECT " << data_ << std::endl;

    return std::unique_ptr<amqp::internal::AMQPDescribed> (nullptr);
}

/******************************************************************************/

std::unique_ptr<amqp::internal::AMQPDescribed>
amqp::internal::
TransformSchemaDescriptor::build(pn_data_t * data_) const {
    validateAndNext(data_);

    std::cout << "TRANSFORM SCHEMA " << data_ << std::endl;

    return std::unique_ptr<amqp::internal::AMQPDescribed> (nullptr);
}

/******************************************************************************/

std::unique_ptr<amqp::internal::AMQPDescribed>
amqp::internal::
TransformElementDescriptor::build(pn_data_t * data_) const {
    validateAndNext(data_);

    std::cout << "TRANFORM ELEMENT " << data_ << std::endl;

    return std::unique_ptr<amqp::internal::AMQPDescribed> (nullptr);
}

/******************************************************************************/

std::unique_ptr<amqp::internal::AMQPDescribed>
amqp::internal::
TransformElementKeyDescriptor::build(pn_data_t * data_) const {
    validateAndNext(data_);

    std::cout << "TRANSFORM ELEMENT KEY" << data_ << std::endl;

    return std::unique_ptr<amqp::internal::AMQPDescribed> (nullptr);
}

/******************************************************************************/
