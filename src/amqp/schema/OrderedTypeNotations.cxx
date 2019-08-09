#include "OrderedTypeNotations.h"

#include "colours.h"

#include <iostream>

/******************************************************************************/

std::ostream &
amqp::internal::schema::
operator << (
        std::ostream & stream_,
        const OrderedTypeNotations & otn_
) {
    int idx1 { 0 };
    for (const auto & i : otn_.m_schemas) {
        stream_ << "level " << ++idx1 << std::endl;
        for (const auto & j : i) {
            stream_ << "    * " << j->name() << std::endl;
        }
        stream_ << std::endl;
    }

    return stream_;
}

/******************************************************************************/

void
amqp::internal::schema::
OrderedTypeNotations::insert (uPtr<schema::AMQPTypeNotation> ptr) {
    std::cout << RED << "inert: " << BLUE << " " << ptr->name() << RESET << std::endl;
    if (m_schemas.empty()) {
        std::list<uPtr<AMQPTypeNotation>> l;
        l.emplace_front (std::move (ptr));
        m_schemas.emplace_front(std::move (l));
        return;
    }

    for (auto i  = m_schemas.begin() ; i != m_schemas.end() ; ++i) {
        for (const auto & j : *i) {
            std::cout << "* compare " << j->name() << " " << ptr->name() << std::endl;
            if (j->dependsOn(ptr)) {
                std::cout << "  " << j->name() << " depends on " << ptr->name() << std::endl;
                if (i == m_schemas.begin()) {
                    std::list<uPtr<AMQPTypeNotation>> l;
                    l.emplace_front (std::move (ptr));
                    m_schemas.emplace_front(std::move(l));
                    return;
                } else {
                    (i--)->emplace_back(std::move(ptr));
                }
            }
        }
    }
}

/******************************************************************************/
