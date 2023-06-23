#include "CompositeField.h"

#include "Field.h"

#include "corda-utils/include/debug.h"

/******************************************************************************/

amqp::internal::schema::
CompositeField::CompositeField (
        std::string name_,
        std::string type_,
        std::list<std::string> requires_,
        std::string default_,
        std::string label_,
        bool mandatory_,
        bool multiple_
) : Field (
        std::move (name_),
        std::move (type_),
        std::move (requires_),
        std::move (default_),
        std::move (label_),
        mandatory_,
        multiple_)
{
    DBG ("FIELD::FIELD - name: " << name() << ", type: " << type() << std::endl); // NOLINT
}

/******************************************************************************/

amqp::internal::schema::Field::Type
amqp::internal::schema::
CompositeField::AMQPType() const {
    return composite_t;
}

/******************************************************************************/

const std::string &
amqp::internal::schema::
CompositeField::resolvedType() const  {
    return type();
}

/******************************************************************************/

