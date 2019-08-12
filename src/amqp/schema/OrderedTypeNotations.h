#pragma once

#include <list>
#include <ostream>
#include <iostream>

#include "types.h"
#include "colours.h"

/******************************************************************************
 *
 * Forward declarations
 *
 ******************************************************************************/

namespace amqp::internal::schema {
    template<class T>
    class OrderedTypeNotations;
}

template<class T>
std::ostream & operator << (
        std::ostream &,
        const amqp::internal::schema::OrderedTypeNotations<T> &);

/******************************************************************************/

namespace amqp::internal::schema {

    class OrderedTypeNotation {
        public :
            virtual ~OrderedTypeNotation() = default;

            virtual bool dependsOn(const OrderedTypeNotation &) const = 0;
    };

}

/******************************************************************************/

namespace amqp::internal::schema {

    template<class T>
    class OrderedTypeNotations {
        private:
            std::list<std::list<uPtr<T>>> m_schemas;

            void insert(
                    uPtr<T> && ptr,
                    decltype(m_schemas.begin()));

            void insertNewList (uPtr<T> && ptr);

        public :
            void insert(uPtr<T> && ptr);

            friend std::ostream & ::operator << <> (
                    std::ostream &,
                    const amqp::internal::schema::OrderedTypeNotations<T> &);
    };

}

/******************************************************************************/

template<class T>
std::ostream &
operator<<(
        std::ostream &stream_,
        const amqp::internal::schema::OrderedTypeNotations<T> &otn_
) {
    int idx1{0};
    for (const auto &i : otn_.m_schemas) {
        stream_ << "level " << ++idx1 << std::endl;
        for (const auto &j : i) {
            stream_ << "    * " << j->name() << std::endl;
        }
        stream_ << std::endl;
    }

    return stream_;
}

/******************************************************************************/

template<class T>
void
amqp::internal::schema::
OrderedTypeNotations<T>::insertNewList(uPtr<T> && ptr) {
    std::list<uPtr<T>> l;
    l.emplace_back (std::move (ptr));
    m_schemas.emplace_back(std::move (l));
}

/******************************************************************************/

template<class T>
void
amqp::internal::schema::
OrderedTypeNotations<T>::insert (uPtr<T> && ptr) {
    return insert (std::move (ptr), m_schemas.begin());
}

/******************************************************************************/

template<class T>
void
amqp::internal::schema::
OrderedTypeNotations<T>::insert (
        uPtr<T> && ptr,
        decltype(m_schemas.begin()) l_
) {
    std::cout << RED << "insert: " << BLUE << " " << ptr->name() << RESET << std::endl;

    for (auto i  = l_ ; i != m_schemas.end() ; ++i) {
        auto okToInsert { true };
        for (auto j = i->begin() ; j != i->end() ; ) {
            std::cout << "* compare " << (*j)->name() << " to " << ptr->name() << std::endl;
            if ((*j)->dependsOn (*ptr)) {
                okToInsert = false;
                ++j;
            } else if (ptr->dependsOn(**j)) {
                std::cout << "  * " << ptr->name() << " depends on " << (*j)->name() << std::endl;
                uPtr<T> tmpPtr { std::move (*j) };
                auto toErase = j++;
                i->erase(toErase);

                // shuffle that element down the stack;
                insert (std::move (tmpPtr), std::next (i));
            } else {
                ++j;
            }
        }

        if (okToInsert) {
            i->emplace_back (std::move (ptr));
            return;
        }
    }

    insertNewList (std::move (ptr));
}

/******************************************************************************/
