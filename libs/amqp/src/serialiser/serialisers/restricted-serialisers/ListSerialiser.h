#pragma once

/******************************************************************************/

#include "amqp/include/serialiser/ISerialiser.h"

#include "RestrictedSerialiser.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    template<class Reader, class Writer>
    class ListSerialiser : public RestrictedSerialiser<Reader, Writer>  {
        private :
            // How to serialiser the underlying types
            std::vector<std::weak_ptr<amqp::serialiser::ISerialiser>> m_serialiser;

        public :
            ListSerialiser (
                std::string type_,
                std::weak_ptr<amqp::serialiser::ISerialiser> serialiser_
            ) : RestrictedSerialiser<Reader, Writer> (std::move (type_))
              , m_serialiser { std::move (serialiser_) }
            { }


            const decltype (m_serialiser) & serialiser() const { return m_serialiser; }

            const std::vector<std::weak_ptr<amqp::serialiser::ISerialiser>> &
            serialisers() const override {
                return m_serialiser;
            }
    };

}

/******************************************************************************/
