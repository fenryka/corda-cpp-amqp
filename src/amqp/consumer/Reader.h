#pragma once

/******************************************************************************/

#include <any>
#include <string>
#include <strstream>

#include "amqp/schema/Schema.h"

/******************************************************************************/

struct pn_data_t;

/******************************************************************************/

namespace amqp {

    class Pair {
        protected :
            std::string m_property;

        public:
            Pair(const std::string & property_)
                : m_property (property_)
            { }

            virtual ~Pair() { }

            Pair (Pair && pair_)
                : m_property (pair_.m_property)
            { }

            virtual std::string dump() const = 0;

    };


    template<typename T>
    class TypedPair : public Pair {
        private:
            T m_value;

        public:
            TypedPair (const std::string & property_, T & value_)
                : Pair (property_)
                , m_value (value_)
            { }

            TypedPair (const std::string & property_, T && value_)
                : Pair (property_)
                , m_value (std::move (value_))
            { }

            const T & value() const {
                return m_value;
            }

            std::string dump() const override;
    };

}

/******************************************************************************/

template<typename T>
inline std::string
amqp::TypedPair<T>::dump() const {
    return m_property + " : " + std::to_string (m_value);
}

template<>
inline std::string
amqp::TypedPair<std::string>::dump() const {
    return m_property + " : " + m_value;
}

template<>
std::string
amqp::TypedPair<std::vector<std::unique_ptr<amqp::Pair>>>::dump() const;

/******************************************************************************
 *
 *
 *
 *
 ******************************************************************************/

namespace amqp {

    class Reader {
        public :
            virtual ~Reader() = default;
            virtual std::any read(pn_data_t *) const = 0;
            virtual std::string readString(pn_data_t *) const = 0;
            virtual std::unique_ptr<Pair> dump(
                const std::string &,
                pn_data_t *,
                const std::unique_ptr<internal::schema::Schema> &) const = 0;
            virtual const std::string & name() const = 0;
    };

}

/******************************************************************************/

