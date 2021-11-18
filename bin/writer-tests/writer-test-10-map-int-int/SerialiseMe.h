#pragma once

/******************************************************************************/

#include <utility>

#include "include/serializable/SerializableMap.h"

#include "amqp/include/AMQPBlob.h"
#include "amqp/include/assembler/SerialiserFactory.h"

/******************************************************************************/

class MapIntInt : public amqp::serializable::Serializable<MapIntInt> {
    private :
        amqp::serializable::SerializableMap<int, int> m_map;

        /**
         * Overriding this lets us actually specify how to serialise
         * this class
         */
        void serialiseImpl(
            const amqp::assembler::SerialiserFactory &,
            amqp::ModifiableAMQPBlob &) const override;

    public :
        explicit MapIntInt (
            amqp::serializable::SerializableMap<int, int> map_
        ) : Serializable<MapIntInt> (javaTypeName<decltype(this)>())
          , m_map (std::move (map_))
        {
        }

        virtual ~MapIntInt() = default;
};

/******************************************************************************/

