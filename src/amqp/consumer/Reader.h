#pragma once

/******************************************************************************/

#include <any>
#include <string>

#include "amqp/schema/Schema.h"

/******************************************************************************/

struct pn_data_t;

/******************************************************************************/

namespace amqp {

    class Pair {
        private:
            std::string m_property;

        public:
            Pair(const std::string & property_)
                : m_property (property_)
            { }

            virtual ~Pair() { }
    };


    template<typename T>
        class TypedPair : public Pair {
            private:
                T m_value;

            public:
                TypedPair (const std::string & property_, const T & value_)
                    : Pair (property_)
                    , m_value (value_)
                { }

                TypedPair(TypedPair&&) = default;
        };

}


/******************************************************************************/

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

