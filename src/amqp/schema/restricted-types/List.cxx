#include <iostream>
#include "List.h"

#include "colours.h"

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
    m_listOf { listType(name_).second }
{

}

/******************************************************************************/

std::vector<std::string>::const_iterator
amqp::internal::schema::
List::begin() const {
    return m_listOf.begin();
}

/******************************************************************************/

std::vector<std::string>::const_iterator
amqp::internal::schema::
List::end() const {
    return m_listOf.end();
}

/******************************************************************************/

const std::string &
amqp::internal::schema::
List::listOf() const {
    return m_listOf[0];
}

/******************************************************************************/

bool
amqp::internal::schema::
List::dependsOn (const amqp::internal::schema::Restricted & lhs_) const {
    std::cout << "Restricted::List gte rest" << std::endl;

    // For example, if *this* is a list of lists and lhs_ is the list type
    // we are a list of, then we depend on lhs_
    for (auto i { lhs_.begin() } ; i != lhs_.end() ; ++i) {
        std::cout << "  " << *i << " " << listOf() << std::endl;
        if (listOf() == *i) return true;
    }

    return false;
}

/*********************************************************o*********************/

bool
amqp::internal::schema::
List::dependsOn (const amqp::internal::schema::Composite & lhs_) const {

    for (const auto & f : lhs_.fields()) {
        if (f->type() == "*") {
            if (f->requires().front() == name()) {
                return true;
            }
        } else if (f->type() == name()) {
            return true;
        }
    }

    return false;
}

/*********************************************************o*********************/
