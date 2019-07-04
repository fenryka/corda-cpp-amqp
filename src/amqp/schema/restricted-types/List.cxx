#include <iostream>
#include "List.h"

#include "schema/Composite.h"

/******************************************************************************/

namespace {

    std::pair<std::string, std::string>
    listType (const std::string & list_) {
        auto pos = list_.find ('<');

        return std::make_pair (
                std::string { list_.substr (0, pos) },
                std::string { list_.substr(pos + 1, list_.size() - pos - 2) }
        );
    }
}

/******************************************************************************/

amqp::internal::schema::
List::List (
    uPtr<Descriptor> & descriptor_,
    const std::string & name_,
    const std::string & label_,
    const std::vector<std::string> & provides_,
    const std::string & source_
) : Restricted (
        descriptor_,
        name_,
        label_,
        provides_,
        amqp::internal::schema::Restricted::RestrictedTypes::List),
    m_listOf (listType(name_).second)
{

}

/******************************************************************************/

std::vector<std::string>::const_iterator
amqp::internal::schema::
List::containedTypes() const {

}

/******************************************************************************/

const std::string &
amqp::internal::schema::
List::listOf() const {
    return m_listOf;
}

/******************************************************************************/

bool
amqp::internal::schema::
List::gte (const amqp::internal::schema::Restricted & lhs_) const {
    std::cout << "Restricted::List gte rest" << std::endl;

    return true;
}

/*********************************************************o*********************/

bool
amqp::internal::schema::
List::gte (const amqp::internal::schema::Composite & lhs_) const {
    std::cout << "Restricted::List gte composite " << m_listOf << std::endl;

    /* if this is an explicit list of the type, then this list must be
       processed after the type it's a list of */
    if (m_listOf == lhs_.name()) {
        std::cout << "  list: " << m_listOf << " == " << lhs_.name() << std::endl;
        return true;
    }

    /* otherwise, lets make sure any of the constituent elements of the
       class are a list of this type */
    for (auto & i : lhs_) {
        std::cout << "  " << (*i).name() << " - " << (*i).type() << std::endl;
    }

    return true;

}

/*********************************************************o*********************/
