#pragma once

/******************************************************************************/

#include <iosfwd>
#include <string>
#include <amqp/include/schema/ISchema.h>

/******************************************************************************/

namespace amqp::internal::schema {

    class Descriptor : public amqp::schema::ISchemaElement {
        public :
            friend std::ostream & operator << (std::ostream &, const Descriptor&);

        private :
            std::string m_name;

        public :
            explicit Descriptor (std::string);

            [[nodiscard]] const std::string & name() const;
    };

}

/******************************************************************************/

