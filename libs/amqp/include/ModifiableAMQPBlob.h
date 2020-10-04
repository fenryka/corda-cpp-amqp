#pragma once

#include "AMQPBlob.h"

#include <map>

/******************************************************************************
 *
 * Forward class declarations
 *
 ******************************************************************************/

namespace amqp::serializable {

    class Serializable;

}

/******************************************************************************
 *
 * class amqp::ModifiableAMQPBlob
 *
 ******************************************************************************/

namespace amqp {

    class ModifiableAMQPBlob : public AMQPBlob {
        private :
            pn_data_t * m_payload;
            std::map<std::string, pn_data_t *> m_schemas;

        public :
            ModifiableAMQPBlob();

            void startComposite (const amqp::serializable::Serializable &);

            void writeInt(
                int,
                const std::string &,
                const amqp::serializable::Serializable &);
    };

}

/******************************************************************************/

