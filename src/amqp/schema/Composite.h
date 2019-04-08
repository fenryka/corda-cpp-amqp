#pragma once

/******************************************************************************/

#include <list>
#include <string>

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
    class Composite : public AMQPDescribed {
        private :
            std::string m_name;

            // could be null in the stream... not sure that information is
            // worth preserving beyond an empty string here.
            std::string m_label;

            // interfaces the class implements... again since we can't 
            // use Karen (the carpenter) to dynamically construct a class
            // we don't know about knowing the interfaces (java concept)
            // that this class mpleemnted isn't al that useful but we'll
            // at least preserve the list
            std::list<std::string> m_provides;

            std::unique_ptr<Descriptor> m_descriptor;

            std::list<std::unique_ptr<Field>> m_fields;

        public :
            Composite()
                : m_descriptor (std::make_unique<Descriptor> (nullptr))
            { }

            Composite (
                const std::string & name_,
                const std::string & label_,
                const std::list<std::string> & provides_,
                std::unique_ptr<Descriptor> descriptor_,
                std::list<std::unique_ptr<Field>> fields_
            ) : m_name (name_)
              , m_label (label_)
              , m_provides (provides_)
              , m_descriptor (std::move (descriptor_))
              , m_fields (std::move (fields_))
            { }

    };

}
}
}

/******************************************************************************/
