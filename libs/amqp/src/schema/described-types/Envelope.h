#pragma once

/******************************************************************************/

#include "Schema.h"

#include <iosfwd>

/******************************************************************************/

namespace amqp::internal::schema {

    class Envelope : public amqp::schema::ISchemaElement {
        public :
            friend std::ostream & operator << (std::ostream &, const Envelope &);

        private :
            std::unique_ptr<Schema> m_schema;
            std::string m_descriptor;

        public :
            Envelope() = delete;

            Envelope (
                std::unique_ptr<Schema> & schema_,
                std::string descriptor_);

            const amqp::schema::ISchema & schema() const;

            const std::string & descriptor() const;
    };

}

/******************************************************************************/

