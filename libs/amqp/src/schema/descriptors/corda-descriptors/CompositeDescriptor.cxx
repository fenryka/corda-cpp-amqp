#include "CompositeDescriptor.h"

#include <string>

/*
 * CLion seems to think this include isn't used when it clearly is
 */
#include <sstream>
#include <iostream>
#include <amqp/src/schema/descriptors/Descriptors.h>

#include "corda-utils/include/types.h"
#include "corda-utils/include/debug.h"

#include "proton-wrapper/include/proton_wrapper.h"

#include "descriptors/AMQPDescriptors.h"

#include "described-types/field-types/Field.h"
#include "described-types/Composite.h"
#include "described-types/Descriptor.h"

/******************************************************************************
 *
 * amqp::internal::schema::descriptors::CompositeDescriptor
 *
 ******************************************************************************/

amqp::internal::schema::descriptors::
CompositeDescriptor::CompositeDescriptor (
    std::string symbol_,
    int val_
) : AMQPDescriptor (std::move (symbol_), val_) {

}

/******************************************************************************/

uPtr<amqp::schema::ISchemaElement>
amqp::internal::schema::descriptors::
CompositeDescriptor::build (pn_data_t * data_) const {
    DBG ("COMPOSITE" << std::endl); // NOLINT

    validateAndNext (data_);

    proton::auto_enter p (data_);

    /* Class Name - String */
    auto name = proton::get_string (data_);

    pn_data_next (data_);

    /* Label Name - Nullable String */
    auto label = proton::get_string (data_, true);

    pn_data_next(data_);

    /* provides: List<String> */
    std::list<std::string> provides;
    {
        proton::auto_list_enter p2 (data_);
        while (pn_data_next(data_)) {
            provides.push_back (proton::get_string (data_));
        }
    }

    pn_data_next (data_);

    /* descriptor: Descriptor */
    auto descriptor = descriptors::dispatchDescribed<schema::Descriptor>(data_);

    pn_data_next (data_);

    /* fields: List<Described> */
    std::vector<uPtr<schema::Field>> fields;
    fields.reserve (pn_data_get_list (data_));
    {
        proton::auto_list_enter p2 (data_);
        while (pn_data_next (data_)) {
            fields.emplace_back (descriptors::dispatchDescribed<schema::Field>(data_));
        }
    }

    return std::make_unique<schema::Composite> (
            schema::Composite (
                    std::move (name),
                    std::move (label),
                    std::move (provides),
                    std::move (descriptor),
                    std::move (fields)));
}

/******************************************************************************/

void
amqp::internal::schema::descriptors::
CompositeDescriptor::readRaw (
        pn_data_t * data_,
        std::stringstream & ss_,
        const AutoIndent & ai_
) const {
    proton::attest_is_list (data_, __FILE__, __LINE__);

    {
        AutoIndent ai { ai_ }; // NOLINT (performance-unnecessary-copy-initialization)
        proton::auto_enter p (data_);

        proton::attest_is_string (data_, __FILE__, __LINE__);
        ss_ << ai
            << "1] String: ClassName: "
            << proton::readAndNext<std::string>(data_)
            << std::endl;

        proton::attest_is_string (data_, __FILE__, __LINE__);
        ss_ << ai
            << "2] String: Label: \""
            << proton::readAndNext<std::string>(data_, true)
            << "\"" << std::endl;

        proton::attest_is_list (data_, __FILE__, __LINE__);

        ss_ << ai << "3] List: Provides: [ ";
        {
            proton::auto_list_enter ale (data_);
            while (pn_data_next(data_)) {
                ss_ << ai << (proton::get_string (data_)) << " ";
            }
        }
        ss_ << "]" << std::endl;

        pn_data_next (data_);
        proton::assert_described(data_);

        ss_ << ai << "4] Descriptor:" << std::endl;

        AMQPDescriptorRegistory[pn_data_type(data_)]->readRaw (
            (pn_data_t *)proton::auto_next(data_), ss_, AutoIndent { ai });

        ss_ << ai << "5] List: Fields: " << std::endl;
        {
            AutoIndent ai2 { ai }; // NOLINT (performance-unnecessary-copy-initialization)

            proton::auto_list_enter ale (data_);
            for (int i { 1 } ; pn_data_next (data_) ; ++i) {
                ss_ << ai2 << i << "/"
                    << ale.elements() << "]"
                    << std::endl;

                AMQPDescriptorRegistory[pn_data_type(data_)]->readRaw (
                        data_, ss_, AutoIndent { ai2 });
            }
        }
    }
}

/******************************************************************************/

void
amqp::internal::schema::descriptors::
CompositeDescriptor::readAvro (
        pn_data_t * data_,
        std::stringstream & ss_,
        const AutoIndent & ai_
) const {
    DBG ("readAvro::Composite" << std::endl); // NOLINT

    ss_ << "{" << std::endl;

    proton::attest_is_list (data_, __FILE__, __LINE__);

    {
        AutoIndent ai { ai_ }; // NOLINT (performance-unnecessary-copy-initialization)
        proton::auto_enter p (data_);

        proton::attest_is_string (data_, __FILE__, __LINE__);


        ss_ << ai << R"("type" : "record",)" << std::endl;
        auto name = proton::readAndNext<std::string>(data_);
        std::size_t found = name.find_last_of('.');

        ss_ << ai << R"("name" : ")" << name.substr (found + 1) << R"(",)" << std::endl;
        ss_ << ai << R"("namespace" : ")" << name.substr (0, found) << R"(",)" << std::endl;


        // skip the label
        proton::attest_is_string (data_, __FILE__, __LINE__, true);
        pn_data_next (data_);

        // skip provides
        proton::attest_is_list (data_, __FILE__, __LINE__);
        pn_data_next (data_);

        // make the fingerprint an alias
        proton::assert_described(data_);
        AMQPDescriptorRegistory[pn_data_type(data_)]->readAvro (
                (pn_data_t *)proton::auto_next (data_), ss_, ai);

        ss_ << ai << R"("fields" : [)" << std::endl;
        {
            AutoIndent ai2 { ai }; // NOLINT (performance-unnecessary-copy-initialization)

            proton::auto_list_enter ale (data_);
            for (int i { 1 } ; pn_data_next (data_) ; ++i) {
                AMQPDescriptorRegistory[pn_data_type (data_)]->readAvro (
                        data_, ss_, ai2);

                if (i < ale.elements()) {
                    ss_ << "," << std::endl;
                } else {
                    ss_ << std::endl;
                }
            }
        }
        ss_ << ai << R"(])" << std::endl;
    }

    ss_ << "}";
}

/******************************************************************************/

/*
 * Class Name - String
 * Label Name - Nullable String
 * provides: List<String>
 * descriptor: Descriptor
 * fields: List<Described>
 */
pn_data_t *
amqp::internal::schema::descriptors::
CompositeDescriptor::makeProton (
    const std::string & name_,
    const std::vector<std::string> & provides_,
    const std::string & fingerprint_,
    const std::map<std::string, pn_data_t *> & fields_,
    const std::string & label_
) {
    DBG (__FUNCTION__ << " - " << name_ << " fields: #" << fields_.size() << std::endl);

    auto rtn = pn_data (0);

    pn_data_put_described (rtn);
    {
        proton::auto_enter ae (rtn);
        pn_data_put_ulong (rtn, descriptors_longs::COMPOSITE_TYPE | descriptors::DESCRIPTOR_TOP_32BITS);
        pn_data_put_list (rtn);

        {
            proton::auto_enter ae2 (rtn);

            // name
            pn_data_put_string(rtn, pn_bytes (name_.size(), name_.data()));

            // label
            pn_data_put_string (rtn, pn_bytes (label_.size(), label_.data()));

            // provides
            pn_data_put_list(rtn);
            {
                proton::auto_enter ae3 (rtn);
                for (const auto & i : provides_) {
                    pn_data_put_string (rtn, pn_bytes (i.size(), i.data()));
                }
            }

            pn_data_put_described (rtn);
            {
                proton::auto_enter ae3 (rtn);
                pn_data_put_ulong (rtn, descriptors_longs::OBJECT | descriptors::DESCRIPTOR_TOP_32BITS);
                pn_data_put_list(rtn);
                {
                    proton::auto_enter ae4 (rtn);
                    pn_data_put_symbol (rtn, pn_bytes (fingerprint_.size(), fingerprint_.data()));
                    pn_data_put_null(rtn);
                }
            }

            pn_data_put_list (rtn);
            {
                proton::auto_enter ae3 (rtn);
                for (const auto & i : fields_) {
                    pn_data_append (rtn, i.second);
                }
            }
        }
    }

    return rtn;
}
