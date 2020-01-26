#pragma once

/******************************************************************************/

#include "amqp/src/serialiser/Serialiser.h"

/******************************************************************************/

namespace amqp::internal::serialiser {

    template <class Reader>
    class CompositeSerialiser : public Serialiser<Reader> {
        private :
            static const std::string m_name;
            std::string m_type;

            std::vector<std::weak_ptr<amqp::serialiser::ISerialiser>> m_serialisers;

        public :
            CompositeSerialiser (
                std::string type_,
                std::vector<std::weak_ptr<amqp::serialiser::ISerialiser>> serialisers_
            ) : m_type { std::move (type_) }
              , m_serialisers { std::move (serialisers_) }
            { }

            const std::string & name() const override  {
                return m_name;
            }

            const std::string & type() const  override {
                return m_type;
            }

            const decltype (m_serialisers) & serialisers() const { return m_serialisers; }
    };

}

/******************************************************************************/

template<typename Reader>
const std::string
        amqp::internal::serialiser::CompositeSerialiser<Reader>::m_name { // NOLINT
        "Composite Serialiser"
};

/******************************************************************************/
