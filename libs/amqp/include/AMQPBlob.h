#pragma once

/******************************************************************************/

#include <string>
#include "corda-utils/include/debug.h"
#include "corda-utils/include/types.h"

#include "schema/SchemaDumpTargets.h"

#include "amqp/src/serialiser/PrimToSerializer.h"

/******************************************************************************/

struct pn_data_t;

namespace amqp {

    class CordaBytes;
    class CompositeFactory;

}

namespace amqp::serializable {

    class Serializable;
    class RestrictedSerializable;

}

/******************************************************************************/

namespace amqp {

    class AMQPBlob {
        private :
           mutable pn_data_t * m_data;

        protected :
            /*
             * Want [[ModifiableAMQPBlob]] to be able to construct
             * empty instances but in general don't want that functionality
             * exposed
             */
            AMQPBlob();

        public :
            explicit AMQPBlob (CordaBytes &);
            explicit AMQPBlob (pn_data_t *);

            [[nodiscard]] std::string dumpContents (amqp::CompositeFactory &) const;
            [[nodiscard]] std::string dumpSchema (schema::DumpTarget) const;
            [[nodiscard]] std::string dumpData () const;

            [[nodiscard]] pn_data_t * data() const;

            void readyPayload() const;

            void startComposite () const;
            void endComposite () const;

            void startRestricted (const amqp::serializable::RestrictedSerializable &);
            void endRestricted (const amqp::serializable::RestrictedSerializable &);

    };

}

/******************************************************************************/

