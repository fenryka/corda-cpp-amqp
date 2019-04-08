#pragma once

/******************************************************************************/

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

            Descriptor (const std::string & name_)
                : m_name (name_)
            { }

            const std::string & name() const {
                return m_name;
            }
    };

}
}
}

/******************************************************************************/

