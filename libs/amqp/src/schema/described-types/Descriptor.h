#pragma once

/******************************************************************************/

#include <iosfwd>
#include <string>

#include "amqp/src/schema/AMQPDescribed.h"

/******************************************************************************/

namespace amqp::internal::schema {

    class Descriptor : public AMQPDescribed {
        public :
            friend std::ostream & operator << (std::ostream &, const Descriptor&);

        private :
            std::string m_name;

        public :
            explicit Descriptor (std::string);

            const std::string & name() const;
    };

}

/******************************************************************************/

