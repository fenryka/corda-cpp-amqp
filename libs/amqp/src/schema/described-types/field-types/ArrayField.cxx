#include "ArrayField.h"

#include "corda-utils/include/debug.h"

#include <iostream>

/******************************************************************************/

const std::string
amqp::internal::schema::
ArrayField::m_fieldType { // NOLINT
        "array"
};

/******************************************************************************/

amqp::internal::schema::
ArrayField::ArrayField (
    std::string name_,
    std::string type_,
    std::list<std::string> requires_,
    std::string default_,
    std::string label_,
    bool mandatory_,
    bool multiple_
) : RestrictedField (
        std::move (name_),
        std::move (type_),
        std::move (requires_),
        std::move (default_),
        std::move (label_),
        mandatory_,
        multiple_
) {
    DBG ("ArrayField::ArrayField - name: " << name() << ", type: " << type() << std::endl); // NOLINT
}

/******************************************************************************/

const std::string &
amqp::internal::schema::
ArrayField::resolvedType() const {
    return type();
}

/******************************************************************************/

amqp::internal::schema::Field::Type
amqp::internal::schema::
ArrayField::AMQPType() const {
    return array_t;
}

/******************************************************************************/
