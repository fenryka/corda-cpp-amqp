#pragma once

/******************************************************************************/

#include "RestrictedSerialiser.h"
#include "amqp/include/serialiser/ISerialiser.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    template<class Reader>
    class MapSerialiser : public RestrictedSerialiser<Reader> {
        private :
            // How to serialiser the underlying types
            std::weak_ptr <amqp::serialiser::ISerialiser> m_keySerialiser;
            std::weak_ptr <amqp::serialiser::ISerialiser> m_valueSerialiser;

        public :
            MapSerialiser(
                std::string type_,
                std::weak_ptr <amqp::serialiser::ISerialiser> keySerialiser_,
                std::weak_ptr <amqp::serialiser::ISerialiser> valueSerialiser_
            ) : RestrictedSerialiser<Reader> (std::move (type_))
              , m_keySerialiser (std::move (keySerialiser_))
              , m_valueSerialiser (std::move (valueSerialiser_))
            { }


            const decltype (m_keySerialiser) & keySerialiser() const { return m_keySerialiser; }
            const decltype (m_valueSerialiser) & valueSerialiser() const { return m_valueSerialiser; }
    };

}

/******************************************************************************/
