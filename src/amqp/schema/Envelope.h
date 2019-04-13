#pragma once

/******************************************************************************/

#include "amqp/AMQPDescribed.h"

#include "Schema.h"

#include <iosfwd>

/******************************************************************************/

namespace amqp {
namespace internal {
namespace schema {

    class Envelope : public AMQPDescribed {
        private :
            std::unique_ptr<Schema> m_schema;

        public :
            Envelope() = default;

            Envelope (std::unique_ptr<Schema> & schema_)
                : m_schema (std::move (schema_))
            { }

            friend std::ostream & operator << (std::ostream &, const Envelope &);

            const std::unique_ptr<Schema> & schema() const;
    };

}
}
}

/******************************************************************************/

