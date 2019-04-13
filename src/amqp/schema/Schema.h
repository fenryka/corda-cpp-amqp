#pragma once

/******************************************************************************/

#include <map>
#include <iosfwd>

#include "Composite.h"
#include "Descriptor.h"

#include "amqp/AMQPDescribed.h"

/******************************************************************************/

namespace amqp {
namespace internal {
namespace schema {

    /*
     * A Corda AMQP Scehma Composite type has:
     *
     * val name: String,
     * val label: String?,
     * val provides: List<String>,
     * val descriptor: Descriptor,
     * val fields: List<Field>
     */
    class Schema : public AMQPDescribed {
        public :
            friend std::ostream & operator << (std::ostream &, const Schema &);

        private :
            std::map<std::string, std::unique_ptr<Composite>> m_types;

        public :
            Schema (std::map<std::string, std::unique_ptr<Composite>> & types_)
                : m_types (std::move (types_))
            { }

            const std::map<std::string, std::unique_ptr<Composite>> & types() const;
    };

}
}
}

/******************************************************************************/

