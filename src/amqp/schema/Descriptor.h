#pragma once

/******************************************************************************/

#include <iosfwd>
#include <string>

#include "amqp/AMQPDescribed.h"

/******************************************************************************/

namespace amqp {
namespace internal {
namespace schema {

    class Descriptor : public AMQPDescribed {
        private :
            std::string m_name;

        public :
            Descriptor() = default;

            Descriptor (const std::string &);

            const std::string & name() const;

            friend std::ostream & operator << (std::ostream &, const Descriptor&);
    };

}
}
}

/******************************************************************************/

