#pragma once

/******************************************************************************/

#include <set>
#include <map>
#include <iosfwd>

#include "corda-utils/include/types.h"

#include "Composite.h"
#include "Descriptor.h"
#include "OrderedTypeNotations.h"

#include "AMQPTypeNotation.h"

#include "schema/ISchema.h"

/******************************************************************************/

namespace amqp::internal::schema {

    using SchemaMap = std::map<
            std::string,
            const std::reference_wrapper<const uPtr <AMQPTypeNotation>>>;
}

/******************************************************************************/

namespace amqp::internal::schema {

    class Schema : public amqp::schema::ISchema, public amqp::schema::ISchemaElement {
        public :
            friend std::ostream & operator << (std::ostream &, const Schema &);

        private :
            OrderedTypeNotations<AMQPTypeNotation> m_types;

            SchemaMap m_descriptorToType;
            SchemaMap m_typeToDescriptor;

        public :
            explicit Schema (OrderedTypeNotations<AMQPTypeNotation>);

            const OrderedTypeNotations<AMQPTypeNotation> & types() const;

            const amqp::schema::ISchemaElement & fromType (const std::string &) const override;
            const amqp::schema::ISchemaElement & fromDescriptor (const std::string &) const override;

            decltype (m_types.begin()) begin() const { return m_types.begin(); }
            decltype (m_types.end()) end() const { return m_types.end(); }
    };

}

/******************************************************************************/

