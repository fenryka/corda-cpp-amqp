#pragma once

/******************************************************************************/

#include "RestrictedSerialiser.h"
#include "amqp/include/serialiser/ISerialiser.h"

/******************************************************************************/

namespace amqp::internal::serialiser::serialisers {

    template<class Reader, class Writer>
    class MapSerialiser : public RestrictedSerialiser<Reader, Writer> {
        private :
            // How to serialiser the underlying types
            std::vector<std::weak_ptr <amqp::serialiser::ISerialiser>> m_serialisers;

        public :
            MapSerialiser(
                std::string type_,
                std::weak_ptr <amqp::serialiser::ISerialiser> keySerialiser_,
                std::weak_ptr <amqp::serialiser::ISerialiser> valueSerialiser_
            ) : RestrictedSerialiser<Reader, Writer> (std::move (type_))
              , m_serialisers {
                    std::move (keySerialiser_), std::move (valueSerialiser_)
                }
            { }


            const std::vector<std::weak_ptr<amqp::serialiser::ISerialiser>> &
            serialisers() const override {
                return m_serialisers;
            }
    };

}

/******************************************************************************/
