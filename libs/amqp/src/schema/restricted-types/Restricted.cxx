#include "Restricted.h"

#include "Map.h"
#include "List.h"
#include "Enum.h"
#include "Array.h"
#include "SchemaUtils.h"

#include <string>
#include <vector>
#include <iostream>

/******************************************************************************
 *
 * ostream overloads
 *
 ******************************************************************************/

namespace amqp::internal::schema {

    std::ostream &
    operator << (
        std::ostream & stream_,
        const amqp::internal::schema::Restricted & clazz_)
    {
        stream_
            << "name       : " << clazz_.name() << std::endl
            << "label      : " << clazz_.m_label << std::endl
            << "descriptor : " << clazz_.descriptor() << std::endl
            << "source     : " << clazz_.m_source << std::endl
            << "provides   : [" << std::endl;

        for (auto & provides : clazz_.m_provides) {
            stream_ << "              " << provides << std::endl;
        }
        stream_<< "             ]" << std::endl;

        return stream_;
    }

}

/******************************************************************************/

namespace amqp::internal::schema {

    std::ostream &
    operator << (
            std::ostream & stream_,
            const amqp::internal::schema::Restricted::RestrictedTypes & type_)
    {
        switch (type_) {
            case Restricted::RestrictedTypes::list_t : {
                stream_ << "list";
                break;
            }
            case Restricted::RestrictedTypes::map_t : {
                stream_ << "map";
                break;
            }
            case Restricted::RestrictedTypes::enum_t : {
                stream_ << "enum";
                break;
            }
            case Restricted::RestrictedTypes::array_t : {
                stream_ << "array";
                break;
            }
        }

        return stream_;
    }

}

/******************************************************************************
 *
 * amqp::internal::schema::Restricted
 *
 ******************************************************************************/

/**
 * Named constructor
 *
 * @param descriptor_
 * @param name_
 * @param label_
 * @param provides_
 * @param source_
 * @return
 */
uPtr<amqp::internal::schema::Restricted>
amqp::internal::schema::
Restricted::make(
        uPtr<Descriptor> descriptor_,
        std::string name_,
        std::string label_,
        std::vector<std::string> provides_,
        std::string source_,
        std::vector<uPtr<Choice>> choices_)
{
    DBG ("RESTRICTED::MAKE - " << name_ << std::endl);
    /*
     * AMQP Lists represent actual lists, arrays, and enumerations.
     *
     * Enumerations are  serialised as lists that have a set of Choices
     * Arrays are serialized as lists of types. Because java cares about the difference between
     * boxed and un-boxed primitives an unboxed array ends with [p] whilst an array of classes
     * ends with []
     */
    if (source_ == "list") {
        if (choices_.empty()) {
            const std::string array { "[]" };
            const std::string primArray { "[p]" };

            // when C++20 is done we can use .endswith, until then we have to do a reverse search
            if (types::isArray (name_)) {
                return std::make_unique<Array>(
                        std::move (descriptor_),
                        std::move (name_),
                        std::move (label_),
                        std::move (provides_),
                        std::move (source_));
            } else {
                return std::make_unique<List>(
                        std::move (descriptor_),
                        std::move (name_),
                        std::move (label_),
                        std::move (provides_),
                        std::move (source_));
            }
        } else {
            return std::make_unique<Enum>(
                    std::move (descriptor_),
                    std::move (name_),
                    std::move (label_),
                    std::move (provides_),
                    std::move (source_),
                    std::move (choices_));
        }
    } else if (source_ == "map") {
        return std::make_unique<Map> (
                std::move (descriptor_),
                std::move (name_),
                std::move (label_),
                std::move (provides_),
                std::move (source_));
    } else {
        throw std::runtime_error ("Unknown restricted type");
    }
}

/******************************************************************************/

amqp::internal::schema::
Restricted::Restricted (
    uPtr<Descriptor> descriptor_,
    std::string name_,
    std::string label_,
    std::vector<std::string> provides_,
    amqp::internal::schema::Restricted::RestrictedTypes source_
) : AMQPTypeNotation (
        std::move (name_),
        std::move (descriptor_))
  , m_label { std::move (label_) }
  , m_provides { std::move (provides_) }
  , m_source { source_ }
{
}

/******************************************************************************/

amqp::internal::schema::AMQPTypeNotation::Type
amqp::internal::schema::
Restricted::type() const {
    return AMQPTypeNotation::Type::restricted_t;
}

/******************************************************************************/

amqp::internal::schema::Restricted::RestrictedTypes
amqp::internal::schema::
Restricted::restrictedType() const {
    return m_source;
}

/******************************************************************************/

int
amqp::internal::schema::
Restricted::dependsOn (const OrderedTypeNotation & rhs_) const {
    DBG ("Restricted::dependsOn" << std::endl);
    return dynamic_cast<const AMQPTypeNotation &>(rhs_).dependsOnRHS (*this);
}

/*********************************************************o*********************/

int
amqp::internal::schema::
Restricted::dependsOnRHS (const Restricted & lhs_) const  {
    DBG ("Restricted::dependsOnRHS - " << lhs_.restrictedType() << std::endl);
    switch (lhs_.restrictedType()) {
        case Restricted::RestrictedTypes::map_t :
            return dependsOnMap (
                static_cast<const amqp::internal::schema::Map &>(lhs_)); // NOLINT
        case Restricted::RestrictedTypes::list_t :
            return dependsOnList (
                static_cast<const amqp::internal::schema::List &>(lhs_)); // NOLINT
        case Restricted::RestrictedTypes::enum_t :
            return dependsOnEnum (
                static_cast<const amqp::internal::schema::Enum &>(lhs_)); // NOLINT
        case Restricted::RestrictedTypes::array_t :
            return dependsOnArray (
                    static_cast<const amqp::internal::schema::Array &>(lhs_)); // NOLINT
    }
}

/*********************************************************o*********************/
