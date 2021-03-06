#include "RestrictedDescriptor.h"

#include "corda-utils/include/types.h"
#include "corda-utils/include/debug.h"

#include "described-types/Choice.h"
#include "restricted-types/Restricted.h"
#include "descriptors/AMQPDescriptors.h"

#include <map>
#include <regex>
#include <sstream>
#include <amqp/src/schema/descriptors/Descriptors.h>

/******************************************************************************/

namespace {

    const std::map<std::string, std::pair<std::regex, std::string>> regexs {
            {
                "java.lang.Integer",
                std::pair { std::regex { "java.lang.Integer"}, "int"}
            },
            {
                "java.lang.Boolean",
                std::pair { std::regex { "java.lang.Boolean"}, "bool"}
            },
            {
                "java.lang.Byte",
                std::pair { std::regex { "java.lang.Byte"}, "char"}
            },
            {
                "java.lang.Short",
                std::pair { std::regex { "java.lang.Short"}, "short"}
            },
            {
                "java.lang.Character",
                std::pair { std::regex { "java.lang.Character"}, "char"}
            },
            {
                "java.lang.Float",
                std::pair { std::regex { "java.lang.Float"}, "float"}
            },
            {
                "java.lang.Long",
                std::pair { std::regex { "java.lang.Long"}, "long"}
            },
            {
                "java.lang.Double",
                std::pair { std::regex { "java.lang.Double"}, "double"}
            }
    };

}

/******************************************************************************/

namespace amqp::internal::schema::descriptors {

    std::string
    RestrictedDescriptor::makePrim (const std::string & name_) {
        std::string name { name_ };
        for (const auto & i: regexs) {
            name = std::regex_replace (name, i.second.first, i.second.second);
        }

        return name;
    }

}

/******************************************************************************/

amqp::internal::schema::descriptors::
RestrictedDescriptor::RestrictedDescriptor (
    std::string symbol_,
    int val_
) : AMQPDescriptor (std::move (symbol_)
  , val_
) {
    
}

/******************************************************************************
 *
 * Restricted types represent lists and maps
 *
 * NOTE: The Corda serialization scheme doesn't support all container classes
 * as it has the requirement that iteration order be deterministic for purposes
 * of signing over data.
 *
 *            name : String
 *           label : String?
 *        provides : List<String>
 *          source : String
 *      descriptor : Descriptor
 *         choices : List<Choice>
 *
 ******************************************************************************/

uPtr<amqp::schema::ISchemaElement>
amqp::internal::schema::descriptors::
RestrictedDescriptor::build (pn_data_t * data_) const {
    DBG ("RESTRICTED" << std::endl); // NOLINT
    validateAndNext(data_);

    proton::auto_enter ae (data_);

    auto name  = makePrim (proton::readAndNext<std::string>(data_, __FILE__, __LINE__));
    auto label = proton::readAndNext<std::string>(data_, __FILE__, __LINE__, true);

    DBG ("  name: " << name << ", label: \"" << label << "\"" << std::endl); // NOLINT

    std::vector<std::string> provides;
    {
        proton::auto_list_enter ae2 (data_);
        while (pn_data_next(data_)) {
            provides.push_back (proton::get_string (data_));

            DBG ("  provides: " << provides.back() << std::endl); // NOLINT
        }
    }

    pn_data_next (data_);

    auto source = proton::readAndNext<std::string> (data_, __FILE__, __LINE__);

    DBG ("source: " << source << std::endl); // NOLINT

    auto descriptor = descriptors::dispatchDescribed<schema::Descriptor> (data_);

    pn_data_next (data_);

    DBG ("choices: " << data_ << std::endl); // NOLINT

    std::vector<std::unique_ptr<schema::Choice>> choices;
    {
        proton::auto_list_enter ae2 (data_);
        while (pn_data_next (data_)) {
            choices.push_back (
                descriptors::dispatchDescribed<schema::Choice> (data_));

            DBG (" choice: " << choices.back()->choice() << std::endl); // NOLINT
        }
    }

    DBG (data_ << std::endl); // NOLINT

    return schema::Restricted::make (
            std::move (descriptor),
            std::move (name),
            std::move (label),
            std::move (provides),
            std::move (source),
            std::move (choices));
}

/******************************************************************************/

void
amqp::internal::schema::descriptors::
RestrictedDescriptor::readRaw (
        pn_data_t * data_,
        std::stringstream & ss_,
        const AutoIndent & ai_
) const {
    proton::attest_is_list (data_, __FILE__, __LINE__);
    proton::auto_enter ae (data_);
    AutoIndent ai { ai_ };

    ss_ << ai << "1] String: Name: "
        << proton::readAndNext<std::string> (data_, __FILE__, __LINE__)
        << std::endl;
    ss_ << ai << "2] String: Label: "
        << proton::readAndNext<std::string> (data_, __FILE__, __LINE__, true)
        << std::endl;
    ss_ << ai << "3] List: Provides: [ ";

    {
        proton::auto_list_enter ae2 (data_);
        while (pn_data_next(data_)) {
            ss_ << proton::get_string (data_) << " ";
        }
        ss_ << "]" << std::endl;
    }

    pn_data_next (data_);
    ss_ << ai << "4] String: Source: "
        << proton::readAndNext<std::string> (data_, __FILE__, __LINE__)
        << std::endl;

    ss_ << ai << "5] Descriptor:" << std::endl;

    AMQPDescriptorRegistory[pn_data_type(data_)]->readRaw (
        (pn_data_t *)proton::auto_next(data_), ss_, AutoIndent { ai });
}

/******************************************************************************/

void
amqp::internal::schema::descriptors::
RestrictedDescriptor::readAvro (
    pn_data_t * data_,
    std::stringstream & ss_,
    const AutoIndent & ai_
) const {
    /*
     * So Avro doesn't really have the concept of restricted types, so
     * we deal with them at the composite level
     */
}

/******************************************************************************/

/*
 *       name : String
 *      label : String?
 *   provides : List<String>
 *     source : String
 * descriptor : Descriptor
 *    choices : List<Choice>
 */
pn_data_t *
amqp::internal::schema::descriptors::
RestrictedDescriptor::makeProton (
    const std::string & name_,
    const std::string & source_,
    const std::string & fingerprint_
) {
    auto rtn = pn_data (0);

    pn_data_put_described (rtn);
    {
        proton::auto_enter ae (rtn);
        pn_data_put_ulong (rtn, descriptors_longs::RESTRICTED_TYPE | descriptors::DESCRIPTOR_TOP_32BITS);
        pn_data_put_list (rtn);

        {
            proton::auto_enter ae2 (rtn);

            // name
            pn_data_put_string(rtn, pn_bytes (name_.size(), name_.data()));

            // label
            pn_data_put_string (rtn, pn_bytes (0, ""));

            // provides
            pn_data_put_list(rtn);
            {
                proton::auto_enter ae3 (rtn);
                /*
                for (const auto & i : provides_) {
                    pn_data_put_string (rtn, pn_bytes (i.size(), i.data()));
                }
                 */
            }

            // source
            pn_data_put_string (rtn, pn_bytes (source_.size(), source_.data()));

            // Descriptor
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

            // Choices
            pn_data_put_list(rtn);
            {
                proton::auto_enter ae3 (rtn);
            }
        }
    }

    return rtn;
}

/******************************************************************************/
