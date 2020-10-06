#include "AMQPDescriptor.h"

#include <sstream>

#include "corda-utils/include/debug.h"

#include "proton-wrapper/include/proton_wrapper.h"

#include "AMQPDescriptorRegistory.h"

/******************************************************************************/

namespace amqp::internal::schema::descriptors {

    std::ostream &
    operator<<(std::ostream &stream_, const AutoIndent &ai_) {
        stream_ << ai_.indent;
        return stream_;
    }

}

/******************************************************************************/

[[maybe_unused]]
const std::string &
amqp::internal::schema::descriptors::
AMQPDescriptor::symbol() const {
    return m_symbol;
}

/******************************************************************************/

std::unique_ptr<amqp::schema::ISchemaElement>
amqp::internal::schema::descriptors::
AMQPDescriptor::build (pn_data_t *) const {
    throw std::runtime_error ("Should never be called");
}

/******************************************************************************/

void
amqp::internal::schema::descriptors::
AMQPDescriptor::read (
        pn_data_t * data_,
        std::stringstream & ss_,
        amqp::schema::DumpTarget target_
) const {
    if (pn_data_type (data_) != PN_DESCRIBED) {
        throw std::runtime_error ("Can only dispatch described objects");
    }

    switch (target_) {
        case amqp::schema::DumpTarget::raw : {
            return readRaw (data_, ss_, AutoIndent());
        }
        case amqp::schema::DumpTarget::amqp : {
            return readAMQP (data_, ss_, AutoIndent());
        }
        case amqp::schema::DumpTarget::avro : {
            return readAvro (data_, ss_, AutoIndent());
        }
    }
}

/******************************************************************************/

void
amqp::internal::schema::descriptors::
AMQPDescriptor::readRaw (
        pn_data_t * data_,
        std::stringstream & ss_,
        const AutoIndent & ai_
) const {
    ss_ << ai_ << "DESCRIBED: " << std::endl;

    {
        AutoIndent ai { ai_ } ; // NOLINT
        proton::auto_enter p (data_);

        switch (pn_data_type (data_)) {
            case PN_ULONG : {
                auto key = proton::readAndNext<u_long> (data_);

                ss_ << ai << "key  : "
                    << key << " :: " << amqp::stripCorda (key)
                    << " -> "
                    <<  amqp::describedToString ((uint64_t)key)
                    << std::endl;

                proton::attest_is_list (data_, __FILE__, __LINE__);
                ss_ << ai << "list : entries: "
                    << pn_data_get_list(data_)
                    << std::endl;

                AMQPDescriptorRegistory[key]->readRaw (data_, ss_, ai);
                break;
            }
            case PN_SYMBOL : {
                ss_ << ai << "blob: bytes: "
                    << pn_data_get_symbol (data_).size
                    << std::endl;
                break;
            }
            default : {
                throw std::runtime_error (
                        "Described type should only contain long or blob");
            }
        }
    }
}

/******************************************************************************/

void
amqp::internal::schema::descriptors::
AMQPDescriptor::readAMQP (
    pn_data_t *,
    std::stringstream &,
    const AutoIndent &
) const {

}

/******************************************************************************/

void
amqp::internal::schema::descriptors::
AMQPDescriptor::readAvro (
    pn_data_t * data_,
    std::stringstream & ss_,
    const AutoIndent & ai_
) const {
    proton::auto_enter p (data_);

    DBG ("readAvro::Descriptor" << std::endl); // NOLINT

    switch (pn_data_type (data_)) {
        case PN_ULONG : {
            auto key = proton::readAndNext<u_long>(data_);

            // a described type really has to be describing something
            proton::attest_is_list (data_, __FILE__, __LINE__);

            AMQPDescriptorRegistory[key]->readAvro (data_, ss_, ai_);
            break;
        }
        case PN_SYMBOL : {
            ss_ << ai_ << "blob: bytes: "
                << pn_data_get_symbol (data_).size
                << std::endl;
            break;
        }
        default : {
            throw std::runtime_error ("Unexpected Type");
        }
    }

}

/******************************************************************************/
