#include "FieldDescriptor.h"

#include "corda-utils/include/debug.h"
#include "corda-utils/include/types.h"

#include "proton-wrapper/include/proton_wrapper.h"

#include "field-types/Field.h"

#include <sstream>
#include "SchemaUtils.h"

/******************************************************************************
 *
 * amqp::internal::schema::descriptors::FieldDescriptor
 *
 ******************************************************************************/

amqp::internal::schema::descriptors::
FieldDescriptor::FieldDescriptor (
    std::string symbol_,
    int val_
) : AMQPDescriptor (std::move (symbol_), val_) {

}

/******************************************************************************/

uPtr<amqp::schema::ISchemaElement>
amqp::internal::schema::descriptors::
FieldDescriptor::build (pn_data_t * data_) const {
    DBG ("FIELD" << std::endl); // NOLINT

    validateAndNext (data_);

    proton::auto_enter ae (data_);

    /* name: String */
    auto name = proton::get_string (data_);

    DBG ("FIELD::name: \"" << name << "\"" << std::endl); // NOLINT

    pn_data_next (data_);

    /* type: String */
    auto type = proton::get_string (data_);

    DBG ("FIELD::type: \"" << type << "\"" << std::endl); // NOLINT

    pn_data_next (data_);

    /* requires: List<String> */
    std::list<std::string> requires;
    {
        proton::auto_list_enter ale (data_);
        while (pn_data_next(data_)) {
            requires.push_back (proton::get_string(data_));
        }
    }

    pn_data_next (data_);

    /* default: String? */
    auto def = proton::get_string (data_, true);

    pn_data_next (data_);

    /* label: String? */
    auto label = proton::get_string (data_, true);

    pn_data_next (data_);

    /* mandatory: Boolean - copes with the Kotlin concept of nullability.
       If something is mandatory then it cannot be null */
    auto mandatory = proton::get_boolean (data_);

    pn_data_next (data_);

    /* multiple: Boolean */
    auto multiple = proton::get_boolean(data_);

    return schema::Field::make (
            name, type, requires, def, label, mandatory, multiple);
}

/******************************************************************************/

void
amqp::internal::schema::descriptors::
FieldDescriptor::readRaw (
        pn_data_t * data_,
        std::stringstream & ss_,
        const AutoIndent & ai_
) const  {
    proton::is_list (data_, __FILE__, __LINE__);

    proton::auto_list_enter ale (data_, true);
    AutoIndent ai { ai_ };

    ss_ << ai << "1/7] String: Name: "
        << proton::get_string ((pn_data_t *)proton::auto_next (data_))
        << std::endl;
    ss_ << ai << "2/7] String: Type: "
        << proton::get_string ((pn_data_t *)proton::auto_next (data_))
        << std::endl;

    {
        proton::auto_list_enter ale2 (data_);

        ss_ << ai << "3/7] List: Requires: elements " << ale2.elements()
            << std::endl;

        AutoIndent ai2 { ai };

        while (pn_data_next(data_)) {
            ss_ << ai2 << proton::get_string (data_) << std::endl;
        }
    }

    pn_data_next (data_);

    proton::is_string (data_, true);

    ss_ << ai << "4/7] String: Default: "
        << proton::get_string ((pn_data_t *)proton::auto_next (data_), true)
        << std::endl;
    ss_ << ai << "5/7] String: Label: "
        << proton::get_string ((pn_data_t *)proton::auto_next (data_), true)
        << std::endl;
    ss_ << ai << "6/7] Boolean: Mandatory: "
        << proton::get_boolean ((pn_data_t *)proton::auto_next (data_))
        << std::endl;
    ss_ << ai << "7/7] Boolean: Multiple: "
        << proton::get_boolean ((pn_data_t *)proton::auto_next (data_))
        << std::endl;
}

/******************************************************************************/

namespace {

    using namespace amqp::internal::schema::types;
    using namespace amqp::internal::schema::descriptors;

    /**
     * This is an imperfect transform method where we're attempting to
     * infer the fields type from our encoded Java which isn't always
     * going to work because the information isn't always encoded
     * here in the field.
     *
     * An actual transform can't be done as we're parsing the stream
     * so this is just a best effort method for looking at what a
     * schema might look like.
     */
    void
    inferType (
            std::string & type_,
            const std::string & requires_,
            std::stringstream & ss_,
            const amqp::internal::schema::descriptors::AutoIndent & ai_
    ) {
        if (type_ == "*") {
            type_ = requires_;
        }

        // when C++20 is done we can use .endswith, until then we have to do a reverse search
        if (isArray (type_)) {
            ss_ << ai_ << R"("type" : "array",)" << std::endl;

            auto type { type_.substr (0, type_.find_last_of ('[')) };

            if (isContainer (type)) {
                ss_ << ai_ << R"("items" : { )" << std::endl;

                inferType (type, requires_, ss_, AutoIndent { ai_ });

                ss_ << ai_ << "}" << std::endl;

            } else {
                ss_ << ai_ << R"("items" : )" << type << std::endl;
            }
        } else if (type_.find ("java.util.List") == 0) {
            ss_ << ai_ << R"("type" : "array",)" << std::endl;

            auto type { amqp::internal::schema::types::listType (type_) };

            if (isContainer (type.second)) {
                ss_ << ai_ << R"("items" : {)";
                inferType (type.second, requires_, ss_, amqp::internal::schema::descriptors::AutoIndent { ai_ });
                ss_ << ai_ << "}";

            } else {
                ss_ << ai_ << R"("items" : )" << type.second << std::endl;
            }
        } else if (type_.find ("java.util.Map") == 0) {
            ss_ << ai_ << R"("type" : "map,)" << std::endl;

            auto type = std::get<2>(amqp::internal::schema::types::mapType (type_));

            if (isContainer (type)) {
                ss_ << ai_ << R"("values" : {)";
                inferType (type, requires_, ss_, amqp::internal::schema::descriptors::AutoIndent { ai_ });
                ss_ << ai_ << "}";

            } else {
                ss_ << ai_ << R"("values: )" << type << std::endl;
            }

        } else {
            ss_ << ai_ << R"("type" : ")" << type_ << R"(")" << std::endl;
        }
    }

    void
    inferType (
            pn_data_t * data_,
            std::stringstream & ss_,
            const amqp::internal::schema::descriptors::AutoIndent & ai_
    ) {
        auto type = proton::get_string ((pn_data_t *) proton::auto_next (data_));

        proton::auto_list_enter ale (data_, true);
        if (ale.elements() > 0) {
            inferType (type, proton::get_string( (data_)), ss_, ai_);
        }
        else {
            inferType (type, "", ss_, ai_);
        }
    }
}

/******************************************************************************/

void
amqp::internal::schema::descriptors::
FieldDescriptor::readAvro (
        pn_data_t * data_,
        std::stringstream & ss_,
        const AutoIndent & ai_
) const  {
    proton::is_list (data_, __FILE__, __LINE__);

    proton::auto_list_enter ale (data_, true);
    ss_ << ai_ << "{" << std::endl;
    {
        AutoIndent ai (ai_);

        ss_ << ai << R"("name" : ")"
            << proton::get_string ((pn_data_t *) proton::auto_next (data_))
            << R"(", )" << std::endl;

        inferType (data_, ss_, ai);

    }
    ss_ << ai_ << "}";
}

/******************************************************************************/
