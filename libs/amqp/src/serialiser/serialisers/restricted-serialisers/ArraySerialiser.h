#pragma once

/******************************************************************************/

#include "amqp/include/serialiser/ISerialiser.h"

#include "RestrictedSerialiser.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    template<class Reader>
    class ArraySerialiser : public RestrictedSerialiser<Reader>  {
        private :
            // How to serialiser the underlying types
            std::weak_ptr<amqp::serialiser::ISerialiser> m_serialiser;

        public :
            ArraySerialiser (
                std::string type_,
                std::weak_ptr<amqp::serialiser::ISerialiser> serialiser_
            ) : RestrictedSerialiser<Reader> (std::move (type_))
              , m_serialiser (std::move (serialiser_))
            { }

            decltype(m_serialiser) serialiser() const { return m_serialiser; }
    };

}

/******************************************************************************/
