#pragma once

/******************************************************************************/

#include <set>
#include <map>
#include <iosfwd>

#include "corda-utils/include/types.h"

#include "Composite.h"
#include "Descriptor.h"
#include "amqp/src/schema/OrderedTypeNotations.h"

#include "amqp/src/schema/AMQPTypeNotation.h"

#include "amqp/include/schema/ISchema.h"

/******************************************************************************/

namespace amqp::internal::schema {

    using SchemaMap = std::map<
            std::string,
            const std::reference_wrapper<const uPtr <AMQPTypeNotation>>>;
}

/******************************************************************************/

namespace amqp::internal::schema {

    class Schema final : public amqp::schema::ISchema, public amqp::schema::ISchemaElement {
        public :
            friend std::ostream & operator << (std::ostream &, const Schema &);

        private :
            OrderedTypeNotations<AMQPTypeNotation> m_types;

            SchemaMap m_descriptorToType;
            SchemaMap m_typeToDescriptor;

        public :
            explicit Schema (OrderedTypeNotations<AMQPTypeNotation>);

            [[nodiscard]] const OrderedTypeNotations<AMQPTypeNotation> & types() const;

            [[nodiscard]] const amqp::schema::ISchemaElement & fromType (const std::string &) const override;
            [[nodiscard]] const amqp::schema::ISchemaElement & fromDescriptor (const std::string &) const override;

            [[nodiscard]] decltype (m_types.begin()) begin() const { return m_types.begin(); }
            [[nodiscard]] decltype (m_types.end()) end() const { return m_types.end(); }
    };

}

/******************************************************************************/

