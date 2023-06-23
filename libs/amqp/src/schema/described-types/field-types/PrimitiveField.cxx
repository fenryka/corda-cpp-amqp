#include "PrimitiveField.h"

/******************************************************************************/

amqp::internal::schema::
PrimitiveField::PrimitiveField (
    std::string name_,
    std::string type_,
    std::string default_,
    std::string label_,
    bool mandatory_,
    bool multiple_
) : Field (
    std::move (name_),
    std::move (type_),
    { }, // requires
    std::move (default_),
    std::move (label_),
    mandatory_,
    multiple_
) {
}

/******************************************************************************/

amqp::internal::schema::Field::Type
amqp::internal::schema::
PrimitiveField::AMQPType() const {
    return primitive_t;
}

/******************************************************************************/

const std::string &
amqp::internal::schema::
PrimitiveField::resolvedType() const {
    return type();
}

/******************************************************************************/
