#include "AMQPDescriptor.h"

#include <string>
#include <iostream>
#include <proton/types.h>
#include <proton/codec.h>

#include "Envelope.h"
#include "proton_wrapper.h"
#include "AMQPDescriptorRegistory.h"

/******************************************************************************/

void
amqp::
AMQPDescriptor::validateAndNext (pn_data_t * const data_) const {
    if (pn_data_type(data_) != PN_ULONG) {
        throw std::runtime_error ("Bad type for a descriptor");
    }

    if (pn_data_get_ulong(data_) != (m_val | amqp::internal::DESCRIPTOR_TOP_32BITS)) {
        throw std::runtime_error ("Invalud Type");
    }

    pn_data_next(data_);

    if (pn_data_type(data_) != PN_LIST) {
        throw std::runtime_error ("Envelope should be list");
    }
}

/******************************************************************************/

std::unique_ptr<amqp::AMQPDescribed>
amqp::
AMQPDescriptor::dispatchDescribed (pn_data_t * data_) const {
    proton::is_described(data_);
    proton::auto_enter p (data_);
    proton::is_ulong(data_);

    auto id = pn_data_get_ulong(data_);

    return amqp::AMQPDescriptorRegistory[id]->build(data_);
}

/******************************************************************************/

std::unique_ptr<amqp::AMQPDescribed>
amqp::
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
        dispatchDescribed (data_);


        pn_data_next(data_);

        /*
         * The transforms schema
         */
        dispatchDescribed (data_);
    }


    return std::unique_ptr<amqp::Envelope>(nullptr);
}

/******************************************************************************/

std::unique_ptr<amqp::AMQPDescribed>
amqp::
SchemaDescriptor::build(pn_data_t * data_) const {
    validateAndNext(data_);

    std::cout << "SCHEMA: " << data_ << std::endl;


    /*
     * The Schema is stored as a list of listf of described objects
     */
    {
        proton::auto_list_enter p (data_);

        while (pn_data_next(data_)) {
            proton::auto_list_enter p (data_);
            while (pn_data_next(data_)) {
                dispatchDescribed(data_);
            }
        }
    }

    return std::unique_ptr<amqp::AMQPDescribed> (nullptr);
}

/******************************************************************************/

std::unique_ptr<amqp::AMQPDescribed>
amqp::
ObjectDescriptor::build(pn_data_t * data_) const {
    validateAndNext(data_);

    std::cout << "OBJECT " << data_ << std::endl;

     {
        proton::auto_list_enter p (data_);

        while (pn_data_next(data_)) {
            std::cout << "       " << data_ << std::endl;
        }
    }


    return std::unique_ptr<amqp::AMQPDescribed> (nullptr);
}

/******************************************************************************/

std::unique_ptr<amqp::AMQPDescribed>
amqp::
FieldDescriptor::build(pn_data_t * data_) const {
    validateAndNext(data_);

    std::cout << "FIELD: " << data_ << std::endl;

    {
        proton::auto_enter p (data_);

        /* name: String */
        {
            std::cout << "    name: " << data_ << std::endl;
        }

        pn_data_next(data_);

        /* type: String */
        {
            std::cout << "    type: " << data_ << std::endl;
        }

        pn_data_next(data_);

        /* requires: List<String> */
        {
            std::cout << "    requires: " << data_ << std::endl;
            proton::auto_list_enter p (data_);
            while (pn_data_next(data_)) {
                std::cout << "        " << data_ << std::endl;
            }
        }

        pn_data_next(data_);

        /* default: String? */
        {
            std::cout << "    default: " << data_ << std::endl;
        }

        pn_data_next(data_);

        /* label: String? */
        {
            std::cout << "    label: " << data_ << std::endl;
        }

        pn_data_next(data_);

        /* mandatory: Boolean - copes with the Kotlin concept of nullability.
           If something is mandatory then it cannot be null */
        {
            std::cout << "    mandatory: " << data_ << std::endl;
        }

        pn_data_next(data_);

        /* multiple: Boolean */
        {
            std::cout << "    multiple: " << data_ << std::endl;
        }

    }


    return std::unique_ptr<amqp::AMQPDescribed> (nullptr);
}

/******************************************************************************/

std::unique_ptr<amqp::AMQPDescribed>
amqp::
CompositeDescriptor::build(pn_data_t * data_) const {
    validateAndNext(data_);

    std::cout << "COMPOSITE " << data_ << std::endl;
    {
        proton::auto_enter p (data_);

        /* Class Name - String */
        {
            std::cout << "    " << data_ << std::endl;
        }

        pn_data_next(data_);

        /* Label Name - Nullable String */
        {
            std::cout << "    " << data_ << std::endl;
        }

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
        {
            dispatchDescribed(data_);
        }

        pn_data_next(data_);

        /* fields: List<Described>*/
        {
            std::cout << "    FIELDS: " << data_ << std::endl;

            proton::auto_list_enter p (data_);
            while (pn_data_next(data_)) {
                dispatchDescribed(data_);
            }
        }
    }

    return std::unique_ptr<amqp::AMQPDescribed> (nullptr);
}

/******************************************************************************/

std::unique_ptr<amqp::AMQPDescribed>
amqp::
RestrictedDescriptor::build(pn_data_t * data_) const {
    std::cout << "RESTRICTED " << data_ << std::endl;

    return std::unique_ptr<amqp::AMQPDescribed> (nullptr);
}

/******************************************************************************/
