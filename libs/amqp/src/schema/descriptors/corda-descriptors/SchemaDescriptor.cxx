#include "SchemaDescriptor.h"

#include "corda-utils/include/types.h"
#include "corda-utils/include/debug.h"

#include "amqp/src/schema/descriptors/AMQPDescriptor.h"

#include "proton-wrapper/include/proton_wrapper.h"

#include "proton/codec.h"

#include "descriptors/AMQPDescriptors.h"
#include "described-types/Schema.h"
#include "OrderedTypeNotations.h"
#include "AMQPTypeNotation.h"

#include <sstream>
#include <cassert>
#include <amqp/src/schema/descriptors/Descriptors.h>

/******************************************************************************/

amqp::internal::schema::descriptors::
SchemaDescriptor::SchemaDescriptor (
    std::string symbol_,
    int val_
) : AMQPDescriptor (std::move (symbol_), val_) {
}

/******************************************************************************/

uPtr<amqp::schema::ISchemaElement>
amqp::internal::schema::descriptors::
SchemaDescriptor::build (pn_data_t * data_) const {
    DBG ("SCHEMA" << std::endl); // NOLINT

    validateAndNext(data_);

    schema::OrderedTypeNotations<schema::AMQPTypeNotation> schemas;

    /*
     * The Schema is stored as a list of lists of described objects
     */
    {
        proton::auto_list_enter ale (data_);

        for (size_t i { 1 } ; pn_data_next(data_) ; ++i) {
            DBG ("  " << i << "/" << ale.elements() << std::endl); // NOLINT
            proton::auto_list_enter ale2 (data_);
            while (pn_data_next(data_)) {
                schemas.insert (
                    descriptors::dispatchDescribed<schema::AMQPTypeNotation> (
                        data_));

                DBG("=======" << std::endl << schemas << "======" << std::endl); // NOLINT
            }
        }
    }

    return std::make_unique<amqp::internal::schema::Schema> (std::move (schemas));
}

/******************************************************************************/

void
amqp::internal::schema::descriptors::
SchemaDescriptor::readRaw (
        pn_data_t * data_,
        std::stringstream & ss_,
        const AutoIndent & ai_
) const {
    proton::attest_is_list (data_, __FILE__, __LINE__);

    {
        AutoIndent ai { ai_ };
        proton::auto_list_enter ale (data_);

        for (int i { 1 } ; pn_data_next (data_) ; ++i) {
            proton::attest_is_list (data_, __FILE__, __LINE__);
            ss_ << ai << i << "/" << ale.elements() <<"]";

            AutoIndent ai2 { ai };

            proton::auto_list_enter ale2 (data_);
            ss_ << " list: entries: " << ale2.elements() << std::endl;

            for (int j { 1 } ; pn_data_next (data_) ; ++j) {
                ss_ << ai2 << i << ":" << j << "/" << ale2.elements()
                        << "] " << std::endl;

                AMQPDescriptorRegistory[pn_data_type(data_)]->readRaw (
                        data_, ss_,
                        AutoIndent { ai2 });
            }
        }
    }
}

/******************************************************************************/

void
amqp::internal::schema::descriptors::
SchemaDescriptor::readAvro (
        pn_data_t * data_,
        std::stringstream & ss_,
        const AutoIndent & ai_
) const {
    DBG ("readAvro::Schema" << std::endl); // NOLINT

    proton::attest_is_list (data_, __FILE__, __LINE__);

    {
        // schema wrapper, this list should always be 1, also move onto the
        // first element
        proton::auto_list_enter ale (data_, true);
        assert (ale.elements() == 1);

        // contents of the scema should also be a list, this time one
        // for each schema elmenet

        {
            proton::auto_list_enter ale2 (data_);

            for (size_t j { 1 }; pn_data_next (data_); ++j) {
                ss_.seekg (0, std::stringstream::end);
                auto pos = ss_.tellg();

                AMQPDescriptorRegistory[pn_data_type(data_)]->readAvro (
                        data_, ss_,
                        ai_);

                ss_.seekg (0, std::stringstream::end);

                // Slightly non obvious bit here but its possible we don't actually add a type
                // to the Avro schema. This is normally where we find a restricted type we've
                // already embedded elsewhere
                if (pos != ss_.tellg()) {
                    if (j < ale2.elements()) {
                        ss_ << ",";
                    }
                    ss_ << std::endl;
                }
            }
        }
    }
}

/******************************************************************************/

pn_data_t *
amqp::internal::schema::descriptors::
SchemaDescriptor::makeProton (
    const std::vector<pn_data_t *> & schemaElements_
) {
    auto rtn = pn_data (0);

    pn_data_put_described (rtn);
    {
        proton::auto_enter ae (rtn);
        pn_data_put_ulong (rtn, descriptors_longs::SCHEMA | DESCRIPTOR_TOP_32BITS);
        pn_data_put_list (rtn);
        {
            proton::auto_enter ae2 (rtn);
            pn_data_put_list (rtn);
            {
                proton::auto_enter ae3 (rtn);
                for (const auto & e : schemaElements_) {
                    pn_data_append (rtn, e);
                }
            }
        }
    }

    return rtn;
}

/******************************************************************************/
