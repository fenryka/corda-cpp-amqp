#include "AMQPTypeNotation.h"

#include "Composite.h"
#include "Restricted.h"

/******************************************************************************
 *
 *
 *
 ******************************************************************************/

namespace amqp::internal::schema {

std::ostream &
operator << (std::ostream & stream_, const AMQPTypeNotation & clazz_) {
    switch (clazz_.type()) {
        case AMQPTypeNotation::Type::Composite : {
            stream_ << dynamic_cast<const Composite &>(clazz_);
            break;
        }
        case AMQPTypeNotation::Type::Restricted : {
            stream_ << dynamic_cast<const Restricted &>(clazz_);
            break;
        }
    }
    return stream_;
}

}

/******************************************************************************
 *
 * amqp::internal::schema::AMQPTypeNotation
 *
 ******************************************************************************/

const std::string &
amqp::internal::schema::
AMQPTypeNotation::descriptor() const {
    return m_descriptor->name();
}

/******************************************************************************/

const std::string &
amqp::internal::schema::
AMQPTypeNotation::name() const {
    return m_name;
}

/******************************************************************************/
